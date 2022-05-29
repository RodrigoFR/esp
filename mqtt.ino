#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Nome da rede WiFi";
const char* password =  "Senha da rede WiFi";
const char* mqttServer = "nome.servidor.mqtt.com";
const int mqttPort = 1883;
const char* mqttUser = "Usuario MQTT";
const char* mqttPassword = "Senha";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Conectando na rede WiFi..");
  }
  Serial.println("Conectado na rede WiFi");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Conectando no servidor de MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("conectado");  
 
    } else {
 
      Serial.print("falha em conectar ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/teste", "Olá - ESP8266");
  client.subscribe("esp/teste");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Mensagem recebida no topico: ");
  Serial.println(topic);
 
  Serial.print("Mensagem:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}
