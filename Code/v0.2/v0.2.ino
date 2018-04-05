
  ////////////////////////////
  //Variables for IR sensors//
  ////////////////////////////

  const int irSensor1 = A0;
  int irSensor1Value;
  
  const int irSensor2;
  int irSensor2Value;
  
  const int irSensor3;
  int irSensor3Value;
  
  const int irSensor4;
  int irSensor4Value;
  
  int irSensorMaxValue;

  /////////////////////////////
  //Variables for thermistors//
  /////////////////////////////

  const int thermistor1 = A1;
  int thermistor1Value;

  const int thermistor2;
  int thermistor2Value;

  const int thermistor3;
  int thermistor3Value;

  const int thermistor4;
  int thermistor4Value;
  
  int thermistorMax;

  //////////////////////////////
  //Variables for piezo buzzer//
  //////////////////////////////

  const int buzzer = 3;
  int buzzerFrequency;

  //////////////////////
  //Variable for timer//
  //////////////////////

  unsigned long int timer;

  void setup() {

    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
    
  }
  
  void loop() {

    irSensorMaxValue = 250;

    irSensor1Value = analogRead(irSensor1);
    irSensor1Value = map(irSensor1Value,0,600,500,0);

    thermistor1Value = analogRead(thermistor1);
    
    buzzerFrequency = 500;

    timer = 500;

    Serial.println(irSensor1Value);
    
    // If temperature is bigger than or equal to max temperature and there is no pot on the stove
    if(thermistor1Value >= thermistorMax && irSensor1Value >= irSensorMaxValue){

      // Play warning noise
      tone(buzzer,buzzerFrequency);
      Serial.println("Alarm on");
      delay(timer);
      noTone(buzzer);
      Serial.println("Alarm wait");
      delay(timer);

      // If temperature is bigger than or equal to max temperature and there is a pot on the stove
      } else {
        
          // Don't play a warning noise
          noTone(buzzer);
          Serial.println("Alarm off");
        
        }
  
  }
