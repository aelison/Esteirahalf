
#include <ESP8266HttpClient.h>
#include <ESP8266WiFi.h>
#include "motor.h"
#include "led.h"

const char* SSID = "emanuel";
const char* PASS = "123";

HTTPClient http;

const String LOCATION = "http://projetoprog10.herokuapp.com/";

const String UPLOAD = "upload";
const String DOWNLOAD = "download";
const String CONTADOR = "\"CONTADOR\":";
const String MOTOR = "\"MOTOR\":";
int val=0;
int sensor = 13;
Motor motor1(12);
int contador = 0;
Led led1(2);
Led led2(4);
void uploadMOTOR(){
      
      http.begin(LOCATION+UPLOAD); 
      http.addHeader("Content-Type", "application/json"); 
      http.POST(JSON_MOTOR()); 
      http.end();  
  
  }
void uploadCONTADOR(){
  
      http.begin(LOCATION+UPLOAD); 
      http.addHeader("Content-Type", "application/json"); 
     http.POST(JSON_CONTADOR()); 
      http.end();  
  }

String downloadWEB(){
  
      http.begin(LOCATION+DOWNLOAD); 
      http.GET();
      String payload = http.getString();
      http.end();
      return payload;
  
}
void atualizarMotor(String comando){

  if(comando.startsWith("{") && comando.endsWith("}")){ 
  
          if(comando.indexOf(MOTOR +" 1") > 0){
              motor1.ligar();
            }else if(comando.indexOf(MOTOR +" 0") > 0){
              motor1.desligar();
            }
        }
  }
String JSON_MOTOR(){
      
      return "{" + 
                  MOTOR + String(motor1.status()) +
            "}";
    }

String JSON_CONTADOR(){
    return "{" +
               CONTADOR + String(contador) + 
           "}";
  }
void setup() {
  
 
  pinMode(sensor, INPUT);
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);    //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {   
    delay(500);
    Serial.println(" Aguardando conexão");
  }

}

void loop() {
  val = digitalRead(sensor);
  if(Serial.available() > 0){
      String comando = Serial.readString();
      atualizarMotor(comando);
      Serial.print(JSON_MOTOR());   
    delay(10);
    }   
    Serial.print(JSON_CONTADOR());
    if(val==HIGH){
    Serial.println("DECTADO");
    delay(3000);// delay para previnir que a esteira ande antes do objeto ser colocado
    motor1.ligar();
    led1.ligar();
    led2.desligar();
    delay(3000);
    }
    else{
      motor1.desligar();
      digitalWrite(led2,HIGH);
    digitalWrite(led1,LOW);
    }
    atualizarMotor(downloadWEB());
    uploadMOTOR();
    delay(10);
    uploadCONTADOR();
            
    Serial.print(JSON_MOTOR());
    delay(10);

    Serial.print(JSON_CONTADOR());
    delay(10);  
}
