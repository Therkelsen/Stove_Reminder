
  #include <thermistor.h>
  #include "HardwareSerial.h"
  
  ///////////////////////////
  //Variables for IR sensor//
  ///////////////////////////

  const int irSensor1 = A5;
  int irSensor1Value;
  
  int irSensorMaxValue;

  bool potOnStove;

  ////////////////////////////
  //Variables for thermistor//
  ////////////////////////////

  #define NTC_PIN               A1
  THERMISTOR thermistor(NTC_PIN, 10000, 3950, 10000);
  int temp;
  
  int tempMax;

  bool temperatureTooHigh;

  //////////////////////////////////////
  //Variables for piezo buzzer and LED//
  //////////////////////////////////////

  const int buzzer = 5;
  int buzzerFrequency;

  int LED = 7;

  //////////////////////
  //Variable for timer//
  //////////////////////

  unsigned long int timer;

  int grn = 75;           //100

  int temp0;

  int temppMax = 400;

  unsigned long cTime;

  int dely = 5000; //300000

  unsigned long pTime = 0;

  void setup() {

    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(LED, OUTPUT);

    irSensorMaxValue = 250;

    timer = 750;

  }
  
  void loop() {
    cTime = millis();
    Serial.println("______________________________");
    tjekTemp();
    potOnStoveChecker();
    delay(dely);
  }

  void potOnStoveChecker(){

    irSensor1Value = analogRead(irSensor1);
    irSensor1Value = map(irSensor1Value,0,600,500,0);
    
    if(irSensor1Value < irSensorMaxValue){
      
      potOnStove = true;
      Serial.println("Pot on stove.");
      
      } else {
        
        potOnStove = false;
        Serial.println("No pot on stove.");
        
        }
    
    }
    
    void tjekTemp () {
    temp = thermistor.read();
    if(cTime - pTime >= dely){
      if(temp>=temppMax) {
        alarm ();
        } else {
          alarmOff ();
        }
      if(temp - temp0 >= grn) {
        if(potOnStove == false){
          alarm ();
          } else {
            alarmOff ();
          }
      }
    if(temp-temp0>=grn-3 && temp-temp0<grn) {
      grn-3; 
     }
     pTime=cTime;
     temp0=temp;
    }
    }

    
    void alarm () {
      // Alarm
      Serial.println("Alarm");
      digitalWrite(LED, HIGH);
      tone(buzzer,500);
      delay(dely);
      Serial.println("Wait");
      digitalWrite(LED, LOW);
      noTone(buzzer);
      delay(timer);
    }

    void alarmOff() {
          // Alarm off
          digitalWrite(LED,LOW);
          noTone(buzzer);
          Serial.println("Errthing's fine");
    }











    

