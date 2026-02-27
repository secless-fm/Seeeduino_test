#include <arduino.h>
#include <Adafruit_BNO055.h>
#include "ir.hpp"

float normalizeAngle(float deg)
{
    while (deg > 180) deg -= 360;
    while (deg < -180) deg += 360;
    return deg;
}

void setup()
{
    Serial.begin(115200);
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

    // C-style用に角度を最大1023にする。
    float ___ = ballAngle * 1023 / 360;

    Serial.print(___);

    delay(10);
}