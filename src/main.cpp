#include <arduino.h>
#include "IR.hpp"
#include "BNO055.hpp"

const int IR_pin = 0;
const int gyro_pin = 1;

void setup()
{
    Serial.begin(115200);
    ir_init();
    BNO_init();
}

void loop()
{
    ir_run();
    if(ballFound) {
        analogWrite(IR_pin, ballAngle); // IR_pinに値を送る。
    }else{
        Serial.print("ボールが見つかりません笑");
    }

    BNO_run();
    if (BNO_start){
        analogWrite(gyro_pin, robotAngle); // gyro_pinに値を送る。
    }else{
        Serial.print("BNOが起動してないのかもです!（妹）");
    }
    
    delay(10);
}