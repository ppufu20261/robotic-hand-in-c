#include <WiFi.h>
#include <PubSubClient.h>

// ==========================================
// CONFIGURAÇÕES DE REDE
// ==========================================
const char* ssid        = "Protagonistas";   // Substitua pelo nome da sua rede
const char* password    = "L@majugi26";   // Substitua pela senha
const char* mqtt_server = "broker.hivemq.com"; 

WiFiClient espClient;
PubSubClient client(espClient);

// ==========================================
// PINOS DO DRIVER A4988
// ==========================================
const int pinStep = 18;
const int pinDir  = 19;

// Tempo do pulso em microsegundos (2500us = velocidade com ótimo torque)
const int velocidade = 2500; 

// Controle do estado do movimento
String comandoAtual = "PARAR";
unsigned long ultimoTempoMensagem = 0;

// ==========================================
// FUNÇÃO DE RECEPÇÃO MQTT 
// ==========================================
void callback(char* topic, byte* payload, unsigned int length) {
  String mensagem = "";
  for (int i = 0; i < length; i++) {
    mensagem += (char)payload[i];
  }

  comandoAtual = mensagem;
  ultimoTempoMensagem = millis(); // Atualiza o cronômetro do último comando recebido
}

// ==========================================
// CONEXÃO AO BROKER MQTT
// ==========================================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ESP32 #2 ao MQTT...");
    
    // Gera um ID único para evitar queda de conexão
    String clientId = "ESP32_Rx_Mao_";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println(" Conectado com sucesso!");
      client.subscribe("projeto/mao/comando");
    } else {
      Serial.print(" Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando em 2s...");
      delay(2000);
    }
  }
}

// ==========================================
// SETUP
// ==========================================
void setup() {
  Serial.begin(115200);

  // Configuração dos pinos do motor
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
  digitalWrite(pinStep, LOW);
  digitalWrite(pinDir, LOW);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500); 
    Serial.print(".");
  }
  Serial.println("\nWi-Fi Conectado no ESP32 #2!");

  // Configuração do cliente MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) { 
    reconnect(); 
  }
  client.loop();

  if (millis() - ultimoTempoMensagem > 300) {
    comandoAtual = "PARAR";
  }

  // MOVIMENTO DE FECHAR A MÃO
  if (comandoAtual == "FECHAR") {
    digitalWrite(pinDir, LOW);
    delayMicroseconds(10); // Estabilização do sinal de direção no driver
    
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(velocidade);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(velocidade);
    
    yield(); // Alimenta as tarefas em segundo plano do ESP32 (Wi-Fi)
  } 
  // MOVIMENTO DE ABRIR A MÃO
  else if (comandoAtual == "ABRIR") {
    digitalWrite(pinDir, HIGH);
    delayMicroseconds(10); // Estabilização do sinal de direção no driver
    
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(velocidade);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(velocidade);
    
    yield(); // Alimenta as tarefas em segundo plano do ESP32 (Wi-Fi)
  }
  // Se comandoAtual for "PARAR", o motor não recebe pulsos e fica imóvel.
}