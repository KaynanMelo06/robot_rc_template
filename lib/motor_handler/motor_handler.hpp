#pragma once
#include <stdint.h>


//  Pinagem e ajuste conforme seu hardware

#define PIN_DIR_E   47   // Motor esquerdo: direcao
#define PIN_PWM_E   33   // Motor esquerdo: velocidade
#define PIN_DIR_D   34   // Motor direito:  direcao
#define PIN_PWM_D   48   // Motor direito:  velocidade


/**
 * @brief Inicializa os pinos dos motores.
 *        Chamar uma vez no setup().
 */
void motor_init(void);

/**
 * @brief Define a velocidade do motor esquerdo.
 * @param pwm  -1023 (re maxima) a +1023 (frente maxima). 0 = freio.
 */
void motorE(int pwm);

/**
 * @brief Define a velocidade do motor direito.
 * @param pwm  -1023 (re maxima) a +1023 (frente maxima). 0 = freio.
 */
void motorD(int pwm);
