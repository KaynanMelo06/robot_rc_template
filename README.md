# Robô RC — Template mínimo (ESP32-S3 + Xbox BLE)

![Plataforma](https://img.shields.io/badge/platform-ESP32--S3-blue)
![Framework](https://img.shields.io/badge/framework-Arduino-teal)
![Build](https://img.shields.io/badge/build-PlatformIO-orange)

Ponto de partida para um robô controlado por rádio usando ESP32-S3
e controle Xbox Series X/S via Bluetooth.

## Pré-requisitos

- [VS Code](https://code.visualstudio.com/)
- Extensão [PlatformIO IDE](https://platformio.org/install/ide?install=vscode) para VS Code
- Controle Xbox Series X/S (conexão via Bluetooth)

## Estrutura

```
mini_sumo_RC/
├── src/
│   └── main.cpp              # Loop principal (leitura do Xbox + mistura arcade)
├── lib/
│   └── motor_handler/
│       ├── motor_handler.hpp # Interface pública dos motores
│       └── motor_handler.cpp # Driver PWM (DIR + PWM por motor)
├── platformio.ini            # Configuração da build
└── .gitignore
```

## Como usar

1. Clone o repositório e abra a pasta no VS Code
2. Aguarde o PlatformIO baixar as dependências automaticamente
3. Ajuste a pinagem em `lib/motor_handler/motor_handler.hpp` conforme seu hardware
4. Compile e faça upload: botão ✓ para compilar, → para gravar
5. Abra o Serial Monitor (115200 baud) para ver o debug
6. Emparelhe o controle Xbox segurando o botão de pareamento até piscar rápido

## Pinagem padrão

| Função        | Pino    |
|---------------|---------|
| Motor E — DIR | GPIO 47 |
| Motor E — PWM | GPIO 33 |
| Motor D — DIR | GPIO 34 |
| Motor D — PWM | GPIO 48 |

## Próximos passos

- Adicionar LEDs de feedback (Debug)
- Adicionar IMU para girar com precisão (PID)
- Adicionar OTA para gravar sem cabo (wifi_OTA)
