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

## 📤 Formato dos Dados Enviados

### 📡 Tópico MQTT: `esp32/sensores`

```json
{
  "temperatura": 35.2,
  "umidade": 40.5,
  "latitude": -12.345678,
  "longitude": -45.987654
}
