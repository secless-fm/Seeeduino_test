#include <Arduino.h>
#include <math.h>
#include "IR.h"

// =====定数=====
static const int IR_FIRST_PIN = 3;
static const int IR_LAST_PIN = 10;
static const int IR_COUNT = 8;
static const int NOT_FOUND_THRESHOLD = 900;

// =====内部状態（外から触れない）=====
static int irValue[11];
static bool ballFound = false;
static float ballAngle = 0.0;

// =====内部関数=====
static float deg_radian(int index){
    static const float Deg[IR_COUNT] = {
        0.0, 45.0, 90.0, 135.0,
        180.0, 225.0, 270.0, 315.0
    };
    return Deg[index] * M_PI / 180.0;
} /* deg_radian(x) と入力すると、 Deg[x] * π / 180.0 が返される */

// ============================
// 初期化
// ============================
void IR_init()
{
    
}

// =============================
// 更新処理（毎ループ）
// =============================
void IR_update()
{
    int minVal = 3000;

    // 全IR読み取り
    for (int pin = IR_FIRST_PIN; pin <= IR_LAST_PIN; pin++)
    {
        int val = analogRead(pin);
        irValue[pin] = val;
        if (val < minVal)
            minVal = val;
    }

    // ボールなし判定
    if (minVal > NOT_FOUND_THRESHOLD)
    {
        ballFound = false;
        return;
    }

    // =====ベクトル合成=====
    float vx = 0.0, vy = 0.0;

    for (int pin = IR_FIRST_PIN; pin <= IR_LAST_PIN; pin++)
    {
        float w = 1.0 / (irValue[pin] + 1);
        float ang = deg_radian(pin - IR_FIRST_PIN);
        vx += w * cos(ang);
        vy += w * sin(ang);
    }

    //角度計算
    float theta = atan2(vy,vx) * M_PI / 180.0;
    if (theta < 0.0) theta += 360.0;

    ballAngle = theta;
    ballFound = true;
}

// =============================
// 外部API
// =============================
bool IR_ballFound()
{
    return ballFound;
}

float IR_getAngle()
{
    return ballAngle;
}