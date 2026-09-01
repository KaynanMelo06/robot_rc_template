#include "motor_handler.hpp"
#include <Arduino.h>

// PWM: resolucao 10 bits (0-1023), frequencia 20 kHz (boa para motores DC)
#define PWM_FREQ   20000
#define PWM_BITS   10

void motor_init(void)
{
    pinMode(PIN_DIR_E, OUTPUT);
    pinMode(PIN_DIR_D, OUTPUT);

    analogWriteFrequency(PIN_PWM_E, PWM_FREQ);
    analogWriteFrequency(PIN_PWM_D, PWM_FREQ);
    analogWriteResolution(PIN_PWM_E, PWM_BITS);
    analogWriteResolution(PIN_PWM_D, PWM_BITS);

    // Garante motores parados na inicializacao
    motorE(0);
    motorD(0);
}

void motorE(int pwm)
{
    if (pwm == 0) {
        digitalWrite(PIN_DIR_E, LOW);
        analogWrite(PIN_PWM_E, 0);
    } else if (pwm > 0) {
        digitalWrite(PIN_DIR_E, HIGH);
        analogWrite(PIN_PWM_E, pwm);
    } else {
        digitalWrite(PIN_DIR_E, LOW);
        analogWrite(PIN_PWM_E, -pwm);
    }
}

void motorD(int pwm)
{
    if (pwm == 0) {
        digitalWrite(PIN_DIR_D, LOW);
        analogWrite(PIN_PWM_D, 0);
    } else if (pwm > 0) {
        digitalWrite(PIN_DIR_D, HIGH);
        analogWrite(PIN_PWM_D, pwm);
    } else {
        digitalWrite(PIN_DIR_D, LOW);
        analogWrite(PIN_PWM_D, -pwm);
    }
}
