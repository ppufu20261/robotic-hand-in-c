#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Protagonistas";
const char* password = "L@majugi26";
const char* mqtt_server = "broker.hivemq.com"; 

WiFiClient espClient;
PubSubClient client(espClient);

const int btnAbrir  = 4;
const int btnFechar = 5;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ESP32 #1 ao MQTT...");
    String clientId = "ESP32_Tx_Mao_";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println(" Conectado!");
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(btnAbrir, INPUT_PULLUP);
  pinMode(btnFechar, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
  }
  Serial.println("\nWi-Fi Conectado no ESP32 #1!");

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) { 
    reconnect(); 
  }
  client.loop();

  bool estadoAbrir  = (digitalRead(btnAbrir) == LOW);
  bool estadoFechar = (digitalRead(btnFechar) == LOW);

  if (estadoFechar && !estadoAbrir) {
    client.publish("projeto/mao/comando", "FECHAR");
    delay(30); // Envia o sinal rapidamente enquanto seguro
  } 
  else if (estadoAbrir && !estadoFechar) {
    client.publish("projeto/mao/comando", "ABRIR");
    delay(30); // Envia o sinal rapidamente enquanto seguro
  } 
  else {
    client.publish("projeto/mao/comando", "PARAR");
    delay(50);
  }
}