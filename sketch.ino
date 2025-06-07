#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "104.41.58.58";
const int mqtt_port = 1883;

#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float latitude = -12.345678;
float longitude = -45.987654;

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 20000;

unsigned long lastAlertTime = 0;
const unsigned long alertInterval = 5000;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a rede Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

String checkAlert(float temp, float umid) {
  if (temp > 35 && umid > 70) return "Estresse térmico alto";
  else if (temp > 30 && umid < 30) return "Ambiente muito seco e quente";
  else if (temp < 5 && umid > 80) return "Risco de geada";
  else if (temp >= 10 && temp <= 20 && umid > 85) return "Risco de fungos e doenças";
  else if (temp > 40) return "Temperatura muito alta";
  else if (temp > 50 && umid < 30) return "Risco de queimada";
  else if (umid < 20) return "Umidade muito baixa";
  else if (temp < 0) return "Congelamento possível";
  else return "";
}

void sendAlert(String alertMsg, float temp, float umid) {
  String payload = "{\"alerta\":\"" + alertMsg + "\",\"temperatura\":" + String(temp) + ",\"umidade\":" + String(umid) +
                   ",\"latitude\":" + String(latitude, 6) + ",\"longitude\":" + String(longitude, 6) + "}";
  Serial.print("Enviando alerta MQTT: ");
  Serial.println(payload);
  client.publish("esp32/alertas", payload.c_str());
}

void sendData(float temp, float umid) {
  String payload = "{\"temperatura\":";
  payload += String(temp);
  payload += ",\"umidade\":";
  payload += String(umid);
  payload += ",\"latitude\":";
  payload += String(latitude, 6);
  payload += ",\"longitude\":";
  payload += String(longitude, 6);
  payload += "}";
  Serial.print("Enviando MQTT: ");
  Serial.println(payload);
  client.publish("esp32/sensores", payload.c_str());
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long now = millis();
  float temp = dht.readTemperature();
  float umid = dht.readHumidity();
  if (isnan(temp) || isnan(umid)) {
    Serial.println("Erro ao ler DHT22");
    return;
  }
  if (now - lastPublishTime >= publishInterval) {
    sendData(temp, umid);
    lastPublishTime = now;
  }
  String alertMsg = checkAlert(temp, umid);
  if (alertMsg != "" && (now - lastAlertTime >= alertInterval)) {
    sendAlert(alertMsg, temp, umid);
    lastAlertTime = now;
  }
}
