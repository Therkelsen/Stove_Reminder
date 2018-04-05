#include <thermistor.h>
#include "HardwareSerial.h"

int LED = 7;
int green = 1;
#define NTC_PIN               A1
THERMISTOR thermistor(NTC_PIN, 10000, 3950, 10000);
int temp;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
      temp = thermistor.read();   // Read temperature

      Serial.print("Temp in 1/10 ºC : ");
      Serial.println(temp);
      
      if (temp > 300) {
      digitalWrite (LED,HIGH);
      }
      else {
      digitalWrite (LED,LOW);
      }

      delay(5000);
}

