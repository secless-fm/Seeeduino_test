#include "function.hpp"

#include "BNO055.hpp"
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

static float val = 0;

const int Button_pin = 1;
bool BNO_start = false;

void BNO_init()
{
    pinMode(Button_pin, INPUT_PULLDOWN);
    Serial_start;

    if (!bno.begin())
    {
    Serial.println("BNO not detected");
    BNO_start = false;
    while (1)
    ;
    }

    delay(1000);

    BNO_start = true;
    bno.setExtCrystalUse(true);
    Serial.print("bno ready");
}

void BNO_run()
{
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    float yaw   = euler.x();
    bool nowButton = digitalRead(Button_pin);
    static bool prevButton = LOW;

    if(prevButton == LOW && nowButton == HIGH)
    {
    Serial.println(" Reset ");
    val = yaw; // 現在の角度(Yaw)を保存
    }
    Serial.print(" ");
    prevButton = nowButton;

    /* リセット時の角度を基準としたbnoの角度=(bno本体の角度-リセット時の角度+360)を360で割った余り */
    yaw = fmod((yaw - val + 360.0),360.0);


    float pitch = euler.y();
    float roll  = euler.z();

    float robotAngle = (yaw / 360.0) * 100;

//  Serial.print(" reset val : ");
//  Serial.print(val);

//  Serial.print(" Yaw : ");
//  Serial.print(normalizeangle(yaw));

//  Serial.print(" Pitch : ");
//  Serial.print(normalizeangle(pitch));

//  Serial.print(" Roll : ");
//  Serial.println(normalizeangle(roll));
    
    delay(10);
}