#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "RODRIGUES";
const char* password = "analiana21";
String serverName = "http://localhost:3000";

int Pinbuzzer = 4; //PINO UTILIZADO PELO BUZZER
int PinA0 = A0;//PINO UTILIZADO PELO SENSOR DE GÁS MQ-2
float gas;
 
int leitura_sensor = 300;//DEFININDO UM VALOR LIMITE (NÍVEL DE GÁS NORMAL)

void Conectar(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("IP: " + (String)WiFi.localIP());  
  
};
 
void setup(){
pinMode(PinA0, INPUT); //DEFINE O PINO COMO ENTRADA
pinMode(Pinbuzzer, OUTPUT); //DEFINE O PINO COMO SAÍDA
Serial.begin(9600);//INICIALIZA A SERIAL
Conectar();
}

void Gas(){
  gas = analogRead(PinA0);
  Serial.println("Nivel de gas:" + (String) gas);
}

void loop(){
int valor_analogico = analogRead(PinA0); //VARIÁVEL RECEBE O VALOR LIDO NO PINO ANALÓGICO
Serial.print("Leitura: "); //EXIBE O TEXTO NO MONITOR SERIAL
Serial.println(valor_analogico);// MOSTRA NO MONITOR SERIAL O VALOR LIDO DO PINO ANALÓGICO
 if (valor_analogico > leitura_sensor){//SE VALOR LIDO NO PINO ANALÓGICO FOR MAIOR QUE O VALOR LIMITE, FAZ 
 digitalWrite(Pinbuzzer, HIGH); //ATIVA O BUZZER E O MESMO EMITE O SINAL SONORO
 }else{ //SENÃO, FAZ
 digitalWrite(Pinbuzzer, LOW);//BUZZER DESLIGADO
 }
 delay(100); //INTERVALO DE 100 MILISSEGUNDOS
}

void Enviar(){
  WiFiClient client;
  HTTPClient http;
  http.begin(serverName.c_str());
  int httpResponseCode = http.POST("Hello, World!");
  delay(300);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
        
  http.end();

}