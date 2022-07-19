#include <Arduino.h>
#include <unity.h>
#include "sensorlist.h"
Sensorlist sl;

void testAddlist()
{

    Serial.printf("\nSize data %ld\n", sizeof(Data));
    uint32_t f1, f2, f3, f4;
    f1 = ESP.getFreeHeap();
    f2 = ESP.getHeapSize();
    // Serial.printf("Free %ld/%ld", ESP.getFreeHeap(), ESP.getHeapSize());
    for (int i = 0; i < 200; i++)
        sl.add(10.0, 1.01, 1000, i, "2222");

    Data d;
    d.h = 99.00;
    d.t = 99.20;
    d.sensorid = 99;
    d.valuetime = 1202103;
    sl.add(d);
    // sl.list();
    Serial.printf("Size :%d ", sl.getSize());
    int d1 = ESP.getFreeHeap();
    int d2 = ESP.getHeapSize();

    sl.list();
    sl.clear();
    f3 = ESP.getFreeHeap();
    f4 = ESP.getHeapSize();
    Serial.printf("\nMem before clear %ld/%ld \n", d1, d2);
    Serial.printf("\nMem use %ld/%ld -> %ld/%ld\n", f1, f2, f3, f4);

    // for (int i = 0; i < 200; i++)
    //     sl.add(10.0, 1.01, 1000, i, "2222");

    // f3 = ESP.getFreeHeap();
    // f4 = ESP.getHeapSize();
    // Serial.printf("\nMem use %ld/%ld -> %ld/%ld\n", f1, f2, f3, f4);

    // sl.clear();
    // f3 = ESP.getFreeHeap();
    // f4 = ESP.getHeapSize();
    // Serial.printf("\nMem use %ld/%ld -> %ld/%ld\n", f1, f2, f3, f4);
    // Serial.printf("Free %ld/%ld\n", ESP.getFreeHeap(), ESP.getHeapSize());
}
void testFindbyid()
{

    for (int i = 0; i < 20; i++)
        sl.add(10.0, 1.01, 1000, i, "2222");

    Data *f = sl.getByid(11);
    Serial.printf("***** Found id :%ld \n", f->sensorid);
    TEST_ASSERT_NOT_NULL(f);
}
void testGetId()
{
    for (int i = 0; i < 20; i++)
        sl.add(10.0, 1.01, 1000, i, "2222");

    Data *f = sl.get(13);
    Serial.printf("***** Found id :%ld \n", f->sensorid);
    TEST_ASSERT_TRUE(f->sensorid == 13);
}
void testToJson()
{
    for (int i = 0; i < 20; i++)
        sl.add(10.0, 1.01, 1000, i, "2222");

    // sl.list();
    Serial.println(sl.toJson());
}
void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    Sensorlist sl;
    UNITY_BEGIN();
    // RUN_TEST(testAddlist);
    // RUN_TEST(testFindbyid);
    // RUN_TEST(testGetId);
    RUN_TEST(testToJson);

    UNITY_END();
}

void loop()
{
    digitalWrite(2, HIGH);
    delay(200);
    digitalWrite(2, LOW);
    delay(200);
}