#define BLYNK_TEMPLATE_ID "TMPL6BXDH_FXl"
#define BLYNK_TEMPLATE_NAME "Coba"
#define BLYNK_AUTH_TOKEN "e9fVdcmFjFE0vMuJSuw3mnBAm-X7IcFJ"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_FIRMWARE_VERSION "0.1.0"

char auth[] = "e9fVdcmFjFE0vMuJSuw3mnBAm-X7IcFJ";
char ssid[] = "Tya";
char pass[] = "Tyara2006224";

unsigned long previousMillisGetHR = 0;
unsigned long previousMillisResultHR = 0;
const long intervalGetHR = 20;
const long intervalResultHR = 10000;
int PulseSensorSignal;
const int PulseSensorHRWire = 36;
int LED13 = 14;
int highThreshold = 850;
int lowThreshold = 850;
int cntHB = 0;
boolean ThresholdStat = true;
int BPMval = 0;

BlynkTimer timer;

void sendSensor (){
  Blynk.virtualWrite (V6, BPMval);
}

void setup ()
{
  //Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval (1000L, sendSensor); pinMode (LED13, OUTPUT);
}

void loop() 
{
  unsigned long currentMillisGetHR = millis();
  if (currentMillisGetHR - previousMillisGetHR >= intervalGetHR) {
    previousMillisGetHR = currentMillisGetHR;

  PulseSensorSignal = analogRead(PulseSensorHRWire);
  //Serial.println(PulseSensorSignal);

  if (PulseSensorSignal > highThreshold && ThresholdStat == true) {
    cntHB++;
    digitalWrite(LED13,1);
    ThresholdStat = false;
  }
  if (PulseSensorSignal < lowThreshold){
  digitalWrite (LED13,0);
  ThresholdStat = true;
  }
}

  //proses mengubah dari pembacaan ke nilai BPM
  unsigned long currentMillisResultHR = millis();

  if (currentMillisResultHR - previousMillisResultHR >= intervalResultHR) {
    previousMillisResultHR = currentMillisResultHR;
    BPMval = cntHB * 6;
    Serial.print("BPM: ");
    Serial.println (BPMval);
    cntHB = 0;
  }
  Blynk.run();
  timer.run();
}