#ifndef SENSORLIST_H
#define SENSORLIST_H
#define Sensornamesize 50
#include <Arduino.h>

struct Data
{
    long id;
    float t;
    float h;
    char sensorname[Sensornamesize];
    long valuetime;
    long sensorid;
    Data *next;
    Data *pre;
};

class Sensorlist
{
private:
    Data *first;
    Data *tail;
    Data *index;
    int size = 0;

public:
    Sensorlist(/* args */);
    ~Sensorlist();
    float getT(void);
    float getH(void);
    void add(long id,/*t*/ float t, /*h*/ float h, long valuetime, long sensorid, char sensorname[Sensornamesize]);
    void add(Data d);
    void list(void);
    void clear(void);
    Data *getByid(long id);
    Data *get(int index);
    Data *next(void);
    void firstIndex(void);
    String toJson(void);

    int getSize();
};
Sensorlist::Sensorlist()
{
    first = index = tail = NULL;
}
int Sensorlist::getSize()
{
    return size;
}
/**
 * @brief 
 * 
 * ID ต้องใส่มาตลอด
 * @return String 
 */
String Sensorlist::toJson()
{
    firstIndex();
    Data *p = next();
    String buf = "[";
    boolean have = false;
    while (p != NULL)
    {
        if (have)
            buf += ",";
        else
            have = true;

        buf += "{";
        buf += "\"t\":\"" + String(p->t) + "\",";
        buf += "\"id\":\"" + String(p->id) + "\",";
        buf += "\"h\":\"" + String(p->h) + "\",";
        buf += "\"sensorid\":\"" + String(p->sensorid) + "\",";
        buf += "\"valuetime\":\"" + String(p->valuetime) + "\",";
        buf += "\"sensorname\":\"" + String(p->sensorname) + "\"";
        buf += "}";

        p = next();
    }
    buf += "]";
    return buf;
}
Sensorlist::~Sensorlist()
{
}

Data *Sensorlist::getByid(long id)
{
    Data *find = first;

    while (find != NULL)
    {
        if (find != NULL && find->sensorid == id)
            return find;
        if (find->next == NULL)
            return NULL;
        find = find->next;
    }
}
void Sensorlist::add(long id,float t, float h, long valuetime, long sensorid, char sensorname[Sensornamesize])
{

    if (index == NULL)
    {
        first = (Data *)malloc(sizeof(Data));
        // first = new Data;
        index = first;
        index->next = NULL;
        index->pre = NULL;
    }
    else
    {
        tail = (Data *)malloc(sizeof(Data));
        // tail = new Data;
        tail->next = NULL;
        tail->pre = NULL;
        index->next = tail;
        tail->pre = index;
        index = tail;
    }
    index->id = id;
    index->h = h;
    index->t = t;
    index->valuetime = valuetime;
    index->sensorid = sensorid;
    memcpy(index->sensorname, sensorname, Sensornamesize);
    size++;
}
Data *Sensorlist::get(int index)
{
    if (index == 0 && first != NULL)
        return first;
    Data *p = first;
    for (int i = 0; i < index; i++)
    {
        if (p->next == NULL)
            return NULL;
        p = p->next;
    }
    return p;
}
void Sensorlist::add(Data d)
{

    if (index == NULL)
    {
        first = (Data *)malloc(sizeof(Data));
        // first = new Data;
        index = first;
        index->next = NULL;
        index->pre = NULL;
    }
    else
    {
        tail = (Data *)malloc(sizeof(Data));
        // tail = new Data;
        tail->next = NULL;
        tail->pre = NULL;
        index->next = tail;
        tail->pre = index;
        index = tail;
    }

    index->h = d.h;
    index->t = d.t;
    index->valuetime = d.valuetime;
    index->sensorid = d.sensorid;
    memcpy(index->sensorname, d.sensorname, Sensornamesize);

    size++;
}
void Sensorlist::clear(void)
{
    firstIndex();
    Data *p = next();
    while (p != NULL)
    {
        size--;
        free(p);
        p = next();
    }
}
/**
 * @brief
 *
 *
 */
void Sensorlist::firstIndex(void)
{
    index = first;
}
Data *Sensorlist::next()
{
    if (index->next == NULL)
    {
        return NULL;
    }
    Data *re = index;
    index = index->next;
    return re;
}
void Sensorlist::list()
{
    firstIndex();
    Data *p = next();

    while (p != NULL)
    {
        Serial.printf("**id:%d ** T:%.2f\n", p->sensorid, p->t);
        p = p->next;
    }
}

#endif
