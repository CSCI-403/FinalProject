volatile unsigned long LastPulseTimeA;
volatile unsigned long LastPulseTimeB;
volatile unsigned long LastPulseTimeC;
volatile unsigned long LastPulseTimeD;

int durationA;
int durationB;
int durationC;
int durationD;

/*Sensor A */
//unsigned long startTime;
#define trigPinA 25
#define echoPinA 26

/*Sensor B */
#define trigPinB 12
#define echoPinB 13


/*Sensor C */
#define trigPinC 14
#define echoPinC 15


/*Sensor D */
#define trigPinD 0
#define echoPinD 2

void setup() {
 
   Serial.begin (9600);
  
  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);

  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);
  
  pinMode(trigPinD, OUTPUT);
  pinMode(echoPinD, INPUT);


attachInterrupt(digitalPinToInterrupt(echoPinA), EchoPinA_ISR, CHANGE);  // Pin 2 interrupt on any change

  
attachInterrupt(digitalPinToInterrupt(echoPinB), EchoPinB_ISR, CHANGE);  // Pin 2 interrupt on any change

  
attachInterrupt(digitalPinToInterrupt(echoPinC), EchoPinC_ISR, CHANGE);  // Pin 2 interrupt on any change


attachInterrupt(digitalPinToInterrupt(echoPinD), EchoPinD_ISR, CHANGE);  // Pin3 interrupt on any change
  
  delay(1000);
 
  xTaskCreate(
                    taskOne,          /* Task function. */
                    "TaskOne",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 
  xTaskCreate(
                    taskTwo,          /* Task function. */
                    "TaskTwo",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 



 
  xTaskCreate(
                    taskThree,          /* Task function. */
                    "TaskThree",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 


  xTaskCreate(
                    taskFour,          /* Task function. */
                    "TaskFour",        /* String with name of task. */
                    10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    NULL);            /* Task handle. */
 
    }
 
void loop() {
  
  //digitalWrite(trigPinA, LOW);
  //digitalWrite(trigPinB, LOW);
  //digitalWrite(trigPinC, LOW);
  //digitalWrite(trigPinD, LOW);
  
  //delayMicroseconds(2); 
  
  //digitalWrite(trigPinA, HIGH);
  //digitalWrite(trigPinB, HIGH);
 // digitalWrite(trigPinC, HIGH);
 // digitalWrite(trigPinD, HIGH);
  
 // delayMicroseconds(10); 
  
  //digitalWrite(trigPinA, LOW);
  //digitalWrite(trigPinB, LOW);
  //digitalWrite(trigPinC, LOW);
  //digitalWrite(trigPinD, LOW);
  
}
 
void taskOne( void * parameter )
{
  portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 33;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
    
    for( ; ;  ){
      
 //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );


   digitalWrite(trigPinA, LOW);

   delayMicroseconds(2); 
    
   digitalWrite(trigPinA, HIGH);

   delayMicroseconds(10); 
   
   digitalWrite(trigPinA, LOW);
    
   Serial.print("Sensor A  ");
   Serial.print(LastPulseTimeA);
   Serial.print('\t');
   Serial.print(((LastPulseTimeA/2)*(.3432)));
   Serial.println("mm");
     vTaskDelay(1) ;
    }
 
    Serial.println("Ending task 1");
    vTaskDelete( NULL );
 
}
 
void taskTwo( void * parameter)
{

 portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 70;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
 
    for( ; ; ){

       //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );


          digitalWrite(trigPinB, LOW);
          
          delayMicroseconds(2); 
          
          digitalWrite(trigPinB, HIGH);
            
            delayMicroseconds(10); 
            
            digitalWrite(trigPinB, LOW);
            
    Serial.print("Sensor B  ");
    Serial.print(LastPulseTimeB);
    Serial.print('\t');
    Serial.print(((LastPulseTimeB/2)*(.3432)));
    Serial.println("mm");
    }
    
    Serial.println("Ending task 2");
    vTaskDelete( NULL );
 
}




void taskThree( void * parameter)
{

 portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 99;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
 
    for( ; ; ){

       //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );


          digitalWrite(trigPinC, LOW);
          
          delayMicroseconds(2); 
          
          digitalWrite(trigPinC, HIGH);
            
            delayMicroseconds(10); 
            
            digitalWrite(trigPinC, LOW);
            
    Serial.print("Sensor C  ");
    Serial.print(LastPulseTimeC);
    Serial.print('\t');
    Serial.print(((LastPulseTimeC/2)*(.3432)));
    Serial.println("mm");
    }
    
    Serial.println("Ending task 3");
    vTaskDelete( NULL );
 
}




void taskFour( void * parameter)
{

 portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 200;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
 
    for( ; ; ){

       //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );


          digitalWrite(trigPinD, LOW);
          
          delayMicroseconds(2); 
          
          digitalWrite(trigPinD, HIGH);
            
          delayMicroseconds(10); 
            
          digitalWrite(trigPinD, LOW);
            
    Serial.print("Sensor D  ");
    Serial.print(LastPulseTimeD);
    Serial.print('\t');
    Serial.print(((LastPulseTimeD/2)*(.3432)));
    Serial.println("mm");
    }
    
    Serial.println("Ending task 4");
    vTaskDelete( NULL );
 
}


void EchoPinA_ISR() {
    static unsigned long startTimeA;
   
    if (digitalRead(echoPinA)) // Gone HIGH
        startTimeA = micros();
    else  // Gone LOW
        LastPulseTimeA = micros() - startTimeA;
}



void EchoPinB_ISR() {
    static unsigned long startTimeB;
   
    if (digitalRead(echoPinB)) // Gone HIGH
        startTimeB = micros();
    else  // Gone LOW
        LastPulseTimeB = micros() - startTimeB;
}


void EchoPinC_ISR() {
    static unsigned long startTimeC;
   
    if (digitalRead(echoPinC)) // Gone HIGH
        startTimeC = micros();
    else  // Gone LOW
        LastPulseTimeC = micros() - startTimeC;
}

void EchoPinD_ISR() {
    static unsigned long startTimeD;
   
    if (digitalRead(echoPinD)) // Gone HIGH
        startTimeD = micros();
    else  // Gone LOW
        LastPulseTimeD = micros() - startTimeD;
}
