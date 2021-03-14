#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "AsyncTelegram.h"

AsyncTelegram myBot;

#define SOILSENSORA A0
#define SOILSENSORD D1

const char* ssid = "SSID";
const char* password = "WIFIPASS";
const char* BotToken = "TOKEN INCLUDING NUMBERS";

const char* channel = "@YOURBOT";

double analogSoil = 0.0;
int digitalSoil = 0;
String msga = "";

WiFiClientSecure net_ssl;

void setup() {
  // put your setup code here, to run once:
  pinMode(SOILSENSORA, INPUT);
  pinMode(SOILSENSORD, INPUT);
  setupLedMatrix();
  Serial.begin(115200);
  Serial.println("start");  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  delay(500);

  myBot.setClock("CET-1CEST,M3.5.0,M10.5.0/3");
  
  // Set the Telegram bot properies
  myBot.setUpdateTime(2000);
  myBot.setTelegramToken(BotToken);

  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");

  
}
void loop() {
  analogSoil = analogRead(SOILSENSORA);
  digitalSoil = digitalRead(SOILSENSORD);
  
  Serial.println(analogSoil);
  Serial.println(digitalSoil);

  if(digitalSoil == 1){
    msga = "I am thirsty";
    setSad();
    Serial.println(msga);
  } else {
    msga = "I am happy";
    setSmiley();
    Serial.println(msga);
  }

  TBMessage msg;
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("HOWRU")) {
      myBot.sendMessage(msg, msga);
    }
  }
  delay(2000); // slow down for 2 seconds 
}
