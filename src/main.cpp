#include <arduino.h>
#include "ir.h"

double normalizeAngle(double deg)
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

    double ballAngle = IR_getAngle();
    Serial.println("ボールの角度は" + String(ballAngle) + "°");

    delay(10);
}