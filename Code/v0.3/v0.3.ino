
  #include <thermistor.h>
  #include "HardwareSerial.h"
  
  ///////////////////////////
  //Variables for IR sensor//
  ///////////////////////////

  const int irSensor1 = A0;
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

  const int buzzer = 3;
  int buzzerFrequency;

  int LED = 7;

  //////////////////////
  //Variable for timer//
  //////////////////////

  unsigned long int timer;

  void setup() {

    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    pinMode(LED, OUTPUT);

    irSensorMaxValue = 250;

    tempMax = 300;
    
    buzzerFrequency = 500;

    timer = 500;
    
  }
  
  void loop() {

    Serial.println("______________________________");
    potOnStoveChecker();

    temperatureChecker();

    //Serial.println(irSensor1Value);
    
    // If temperature is bigger than or equal to max temperature and there is no pot on the stove
    if(temperatureTooHigh == true && potOnStove == false){

      // Turn on LED
      digitalWrite(LED,HIGH);
      
      // Play warning noise
      tone(buzzer,buzzerFrequency);
      Serial.println("Alarm on");
      delay(timer);
      noTone(buzzer);
      Serial.println("Alarm wait");
      delay(timer);

      // If temperature is bigger than or equal to max temperature and there is a pot on the stove
      } else {

          // Turn off LED
          digitalWrite(LED,LOW);
          
          // Don't play a warning noise
          noTone(buzzer);
          Serial.println("Alarm off");
        
        }
      
      delay(5000);

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

  void temperatureChecker(){

    temp = thermistor.read();

    if(temp >= tempMax){

      temperatureTooHigh = true;
      Serial.println("Temperature over max.");
      
      } else {
        
        temperatureTooHigh = false;
        Serial.println("Temperature under max.");
        
        }
    
    }
