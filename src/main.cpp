#include <arduino.h>
#include <Adafruit_BNO055.h>
#include "ir.h"

float normalizeAngle(float deg)
{
    while (deg > 180) deg -= 360;
    while (deg < -180) deg += 360;
    return deg;
}

void setup()
{
    Serial.begin(9600);
    IR_init();
}

void loop()
{
    IR_update();

    if (!IR_ballFound) /* !は否定演算子 「falseだったら」と考える */
    {
        Serial.println("ボールが見つかりません");
        delay(10);
        return;
    }

    float ballAngle = IR_getAngle();
    Serial.println("ボールの角度は" + String(ballAngle) + "°");

    delay(10);
}