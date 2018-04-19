
  /////////////////////////////
  //  Kira, Signe & Thomas T //
  //  2.z - Programmering B  //
  //  Stove_Reminder         //
  //  Version 1.0            //
  //  19. april 2018         //
  /////////////////////////////


  #include <thermistor.h>           
  #include "HardwareSerial.h"       //  Imported code to measure and calculate temperature using the thermistor
  
  ///////////////////////////
  //Variables for IR sensor//
  ///////////////////////////

  const int irSensor1 = A5;         //  IR Sensor on pin #A5
  
  int irSensor1Value;               //  Variable to hold value of sensor read
  
  int irSensorMaxValue = 250;       //  Threshold value of IR sensor

  bool potOnStove;                  //  Bool set by function to check if there's a pot on the stove

  ////////////////////////////////////////////
  //Variables for thermistor and temperature//
  ////////////////////////////////////////////

  #define NTC_PIN               A1
  THERMISTOR thermistor(NTC_PIN, 10000, 3950, 10000);

  int temp0;                        //  Temperature multiplied by 10, last time the code was run
  
  int temp;                         //  Temperature multiplied by 10

  int limit = 100;                  //  Maximum amount of change in temperature in given time - 10 degrees celcius  
  
  int tempMax = 400;                //  Absolute maximum temperature - 40 degrees celcius

  //////////////////////////////////
  //Variables for alarm components//
  //////////////////////////////////

  const int buzzer = 5;             //  Piezo buzzer on pin #5

  const int LED = 7;                //  LED on pin #7

  //////////////////////
  //Variable for timer//
  //////////////////////

  unsigned long cTime;              //  Variable to hold current time since start
  
  unsigned long pTime = 0;          //  Time since start, last time the code was run

  unsigned long dely = 300000;      //  300000 - 3000 seconds / 5 minutes
  
  unsigned long timer = 750;        //  7,5 seconds
  
  void setup() {                    //  Setup runs once

    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);        //  Set buzzer to take a signal from the Arduino
    pinMode(LED, OUTPUT);           //  Set LED to take a signal from the Arduino

    Serial.println("Arduino up and running!");

  }
  
  void loop() {                     //  Runs as fast as the Arduino can tick
    
    Serial.println("______________________________");
    
    cTime = millis();               //  Sets current time to the amount of time since Arduino was started
    
    checkTemp();                    //  Run function to check the temperature
    potOnStoveChecker();            //  Run function to check if there's a pot on the stove
    delay(dely);
    
  }

  void potOnStoveChecker(){         //  Function to check if there's a pot on the stove

    irSensor1Value = analogRead(irSensor1);             //  Set variable to contain the read from the IR Sensor
    irSensor1Value = map(irSensor1Value,0,600,500,0);   //  Map the read from the IR Sensor to fit in millimeters
    
    if(irSensor1Value < irSensorMaxValue){              //  If there is something within the IR Sensors' threshold...
      
      potOnStove = true;                                //  ... there is a pot on the stove
      Serial.println("Pot on stove.");
      
      } else {                                          //  If not...
        
        potOnStove = false;                             //  ... there is no pot on the stove
        Serial.println("No pot on stove.");
        
        }
    
    }
    
    void checkTemp () {                               //  Function to check the temperature
      
      temp = thermistor.read();                       //  Set variable to contain the read from the thermistor (Temperature calculations done in the imported library)
      
      if(cTime - pTime >= dely){                      //  If time since Arduino started - last time this function was run >= dely, go in to the statement
        
        if(temp >= tempMax) {                         //  If temperature >= absolute maximum temperature...
          
          alarm ();                                   //  ... start the alarm
          
          } else {                                    //  If not...
            
            alarmOff ();                              //  ... stop the alarm
            
           }
          
        if(temp - temp0 >= limit) {                   //  If the change in temperature since the last time this was run is bigger than the limit, go into the statement
         
          if(potOnStove == false){                    //  If there is no pot on the stove...
  
            alarm ();                                 //  ... start the alarm
            
            } else {                                  //  If not...
              
              alarmOff ();                            //  ... stop the alarm
              
              }
        }
        
        if(temp - temp0 >= limit - 3 && temp - temp0 < limit) {   //  If the change in temperature is big, but not bigger than the limit...
          
          limit - 3;                                    //  ... make the limit smaller for next check.
          
        }
       
       pTime = cTime;                                   //  Set previous time to contain the amount of time since Arduino started, as of right now
       temp0 = temp;                                    //  Set start temperature to contain the current temperature
       
      }
    }

    void alarm () {                                 //  Alarm function
      // Alarm
      Serial.println("Alarm");
      digitalWrite(LED, HIGH);                      //  Turn on LED
      tone(buzzer,500);                             //  Turn on buzzer
      delay(dely);
      Serial.println("Wait");
      digitalWrite(LED, LOW);                       //  Turn off LED
      noTone(buzzer);                               //  Turn off buzzer
      delay(timer);
    }

    void alarmOff() { 
          // Alarm off
          digitalWrite(LED,LOW);                    //  Turn off LED
          noTone(buzzer);                           //  Turn off buzzer
          Serial.println("Everything's fine");
    }











    

