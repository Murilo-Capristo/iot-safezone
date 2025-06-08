# 🌡️ SafeZone – Monitoramento Ambiental com ESP32, DHT22 e MQTT

O **SafeZone** é um sistema de monitoramento ambiental que utiliza o microcontrolador **ESP32** e o sensor **DHT22** para coletar dados de **temperatura** e **umidade**. Esses dados são enviados para um **broker MQTT**, processados via **Node-RED**, armazenados em um banco de dados e visualizados em tempo real por meio de um **aplicativo mobile**.

Ideal para aplicações como:
- Prevenção de queimadas
- Controle climático de ambientes sensíveis
- Automação agrícola e rural

---

## 🧑‍💻 Integrantes do Grupo
- Guilherme Romanholi Santos - RM557462  
- Murilo Capristo - RM556794  
- Nicolas Guinante Cavalcanti - RM557844  

---
## 📋 Como testar o projeto

### 🖥️ 1. Acesse a VM no Azure

Execute os comandos listados no arquivo `azure.txt` (fornecido na entrega) para iniciar a máquina virtual com:

- Mosquitto (broker MQTT)
- Node-RED

> A VM será responsável por receber dados do ESP32 e repassar ao backend.

---

### 📦 2. Clone o repositório IoT

```bash
git clone https://github.com/Murilo-Capristo/iot-safezone.git
cd iot-safezone
```

---

### 📲 3. Clone o Repositório Mobile para Dashboard

O app foi desenvolvido em **React Native com Expo**.

```bash
git clone https://github.com/Murilo-Capristo/mobile-safezone.git
cd mobile-safezone
npm install
npx expo start
```

Use o aplicativo **Expo Go** no celular para escanear o QR Code.

Crie um usuário ADMIN para ter acesso às leituras ou use a conta já criada, listada no arquivo `azure.txt`.

---

### 🤖 4. Simule o hardware com Wokwi

O ESP32 simula a leitura de tags RFID.

1. Acesse [https://wokwi.com](https://wokwi.com)
2. Crie um novo projeto com ESP32
3. Substitua o conteúdo pelo código da pasta:

```
iot-safezone/
```

Bibliotecas Necessárias:
1. PubSubClient

Mude a temperatura e Umidade para ter leituras variadas, o app mostrará apenas os avisos, mas ambos são salvos em nosso banco de dados.

---

## 🚨 Regras de Alerta (`checkAlert`)

O sistema analisa as leituras de temperatura e umidade para identificar condições ambientais críticas e emitir alertas automáticos. As regras seguem a seguinte lógica:

| Condição | Alerta |
|----------|--------|
| 🌡️ `Temperatura > 35°C` e `Umidade > 70%` | **Estresse térmico alto** |
| 🔥 `Temperatura > 30°C` e `Umidade < 30%` | **Ambiente muito seco e quente** |
| ❄️ `Temperatura < 5°C` e `Umidade > 80%` | **Risco de geada** |
| 🌫️ `10°C ≤ Temperatura ≤ 20°C` e `Umidade > 85%` | **Risco de fungos e doenças** |
| 🥵 `Temperatura > 40°C` | **Temperatura muito alta** |
| 🔥 `Temperatura > 50°C` e `Umidade < 30%` | **Risco de queimada** |
| 💧 `Umidade < 20%` | **Umidade muito baixa** |
| 🧊 `Temperatura < 0°C` | **Congelamento possível** |

---

## 🎯 Objetivo

Desenvolver uma solução IoT que:
- Realiza leituras periódicas de temperatura e umidade.
- Transmite os dados por MQTT.
- Detecta condições críticas e gera alertas automáticos.
- Armazena os dados para análise posterior.
- Exibe as informações em um aplicativo mobile integrado ao back-end.

---

## 🧠 Tecnologias e Conceitos Envolvidos

| Categoria        | Tecnologia / Conceito                    |
|------------------|------------------------------------------|
| Microcontrolador | ESP32                                    |
| Sensor           | DHT22                                    |
| Comunicação      | MQTT (via biblioteca `PubSubClient`)     |
| Plataforma       | Wokwi (simulação)          |
| Processamento    | Node-RED                                 |
| Armazenamento    | Banco de dados relacional                |
| Interface        | App mobile em Expo (React Native)        |
| Back-end         | API REST Java com Spring Boot            |

---


## 📤 Formato dos Dados Enviados

### 📡 Tópico MQTT: `esp32/sensores`

```json
{
  "temperatura": 35.2,
  "umidade": 40.5,
  "latitude": -12.345678,
  "longitude": -45.987654
}
