#include <Arduino.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
#include "motor_handler.hpp"

// ============================================================
//  Instancia do controle Xbox
// ============================================================
XboxSeriesXControllerESP32_asukiaaa::Core xbox;

// ============================================================
//  Zona morta dos analogicos
//  Valores abaixo disso são tratados como 0 (evita drift)
// ============================================================
#define DEAD_ZONE 200

// ============================================================
//  setup() roda uma vez ao ligar
// ============================================================
void setup()
{
    Serial.begin(115200);
    motor_init();
    xbox.begin();
    Serial.println("KaBullto RC - aguardando controle...");
}

// ============================================================
//  loop() roda continuamente
// ============================================================
void loop()
{
    xbox.onLoop();

    if (xbox.isConnected())
    {
        // --- Leitura dos eixos ---
        // Eixo Y: diferenca entre gatilho direito (RT) e esquerdo (LT)
        //         RT sozinho = frente, LT sozinho = re
        int16_t vel = xbox.xboxNotif.trigRT - xbox.xboxNotif.trigLT;

        // Eixo X: analogico esquerdo horizontal (girar)
        // map converte de 0-65535 para -1023..+1023
        int16_t giro = map(xbox.xboxNotif.joyLHori, 0, 65535, -1023, 1023);

        // --- Zona morta ---
        if (abs(giro) < DEAD_ZONE) giro = 0;
        if (abs(vel)  < DEAD_ZONE) vel  = 0;

        // --- Mistura arcade ---
    	// Mix para andar para frente e virar ao mesmo tempo
        // motorEsquerdo = vel + giro
        // motorDireito  = vel - giro
        int16_t velE =  vel + giro;
        int16_t velD =  vel - giro;

        // Normaliza para nao ultrapassar 1023
        // a gente faz o pwm de 255 virar 1023 para melhorar a resolucao
        int16_t maior = max(abs(velE), abs(velD));
        if (maior > 1023) {
            float fator = 1023.0f / (float)maior;
            velE = (int16_t)(velE * fator);
            velD = (int16_t)(velD * fator);
        }

        // --- Aplica nos motores ---
        // Nota: MotorD pode precisar de sinal invertido dependendo da
        //       montagem mecanica do seu robo. Troque o sinal se necessario.
        motorE(velE);
        motorD(-velD);

        // Debug no Serial Monitor
        Serial.printf("vel=%d  giro=%d  E=%d  D=%d\n", vel, giro, velE, -velD);
    }
    else
    {
        // Controle desconectado: para os motores por seguranca
        motorE(0);
        motorD(0);

        Serial.println("Controle nao conectado...");

        // Se falhar muitas vezes, reinicia o BLE
        if (xbox.getCountFailedConnection() > 2) {
            ESP.restart();
        }
    }

    delay(10); // 10ms
}
