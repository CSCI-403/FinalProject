#include <WiFi.h>
#include <WiFiUdp.h>

/* WiFi network name and password */
const char* ssid = "";
const char* password =  "";

// IP address to send UDP data to.
// it can be ip address of the server or 
// a network broadcast address
// here is broadcast address
const char * udpAddress = "10.0.0.255";
//const int udpPort = 44444;
const int udpPort = 3333;

//create UDP instance
WiFiUDP udp;

// -----End of Wifi---- 



//define pin varaibles 

volatile unsigned long LastPulseTimeA;
volatile unsigned long LastPulseTimeB;
volatile unsigned long LastPulseTimeC;
volatile unsigned long LastPulseTimeD;

long distanceA;
long distanceB;
long distanceC;
long distanceD;



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



// create a Queue handler 
QueueHandle_t  xQueueENCODER_Readings;

String stringOne = " ";

int x = 0 ; 

// Store data for  time and distance 

 struct ENCODER_Motion 
  {
    int    Current_Day ;
    long  Current_DistanceA;
    long  Current_DistanceB;
    long  Current_DistanceC;
    long  Current_DistanceD;
  } ;


  // two instances of structs 
   struct   ENCODER_Motion   ENCODER_MOTION_NOW;
   struct      ENCODER_Motion   ENCODER_Received;

  
void setup() {
 Serial.begin(115200);

 
//Connect to the WiFi network
   WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //This initializes udp and transfer buffer
  udp.begin(udpPort);

//-------End of Wifi setup -----------

//--Setting i/o configurations--//

  pinMode(trigPinA, OUTPUT);
  pinMode(echoPinA, INPUT);

  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);

  pinMode(trigPinC, OUTPUT);
  pinMode(echoPinC, INPUT);
  
  pinMode(trigPinD, OUTPUT);
  pinMode(echoPinD, INPUT);


attachInterrupt(digitalPinToInterrupt(echoPinA), EchoPinA_ISR, CHANGE);  // Pin 26 interrupt on any change

  
attachInterrupt(digitalPinToInterrupt(echoPinB), EchoPinB_ISR, CHANGE);  // Pin 13 interrupt on any change

  
attachInterrupt(digitalPinToInterrupt(echoPinC), EchoPinC_ISR, CHANGE);  // Pin 15 interrupt on any change


attachInterrupt(digitalPinToInterrupt(echoPinD), EchoPinD_ISR, CHANGE);  // Pin2 interrupt on any change

 
 
 delay(1000);
 
// create a struct queue of size 10 
 xQueueENCODER_Readings  = xQueueCreate( 10  , sizeof( struct  ENCODER_Motion ) );


 /// checking if queue was made correctly 
  if(xQueueENCODER_Readings==NULL){
      Serial.println("ERROR Creating queue");
    }
     
 
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


 xTaskCreate(        taskThree,          /* Task function. */
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
 
xTaskCreate(
                   taskFive,          /* Task function. */
                   "TaskFive",        /* String with name of task. */
                   10000,            /* Stack size in words. */
                    NULL,             /* Parameter passed as input of the task */
                   1,                /* Priority of the task. */
                    NULL);            /* Task handle. */

                    
 
}
 
void loop() {
  delay(1000);

  
}





 // task one takes care of collecting data and sending to queue 
void taskOne( void * parameter )
{

  portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 1000;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
    

  // infinite loop of checking sensor data 
    for(  ; ; ){

       
        ENCODER_MOTION_NOW.Current_Day = 100;

        //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );
           
            //clears TrigPin
            digitalWrite(trigPinA, LOW);
            delayMicroseconds(2); 
            
             //sets the trigPin HIGH 
            digitalWrite(trigPinA, HIGH);
            delayMicroseconds(10); 
            digitalWrite(trigPinA, LOW);

            // Reads echoPin , returns duration 
            // calculate distance  
          
          Serial.print("Sensor A  ");
          Serial.print(LastPulseTimeA);
          Serial.print('\t');
          distanceA = (LastPulseTimeA/2)*(.3432); 
          Serial.print((distanceA));
          Serial.println("mm");
    
        ENCODER_MOTION_NOW.Current_DistanceA = distanceA;
            //Sending to Queue
       xQueueSend(xQueueENCODER_Readings,(void *) &ENCODER_MOTION_NOW, portMAX_DELAY );
       
    }
 
}





 //Takes care of recieving data and displaying to Screen 
 
void taskTwo( void * parameter)
{
 
  // Infininite loop 
  for(  ; ; ){
    
   if (xQueueReceive ( xQueueENCODER_Readings ,  &(ENCODER_Received) , portMAX_DELAY ) ){
    
       udp.beginPacket(udpAddress, udpPort);
      
      if  ( x  < 1) {
       
 stringOne+= String (ENCODER_Received.Current_Day);
      stringOne.concat(" ");
   stringOne.concat(ENCODER_Received.Current_DistanceA);
    stringOne.concat(" ");
     stringOne.concat(ENCODER_Received.Current_DistanceB);
     //Serial.print("|");
      stringOne.concat(" ");
     stringOne.concat(ENCODER_Received.Current_DistanceC);
      stringOne.concat(" ");
     stringOne.concat(ENCODER_Received.Current_DistanceD);
      stringOne.concat("|");
      /**/
      Serial.print(stringOne);
       
        x++; 
      }

     else{
       // end packet 
       udp.print(stringOne);
       udp.endPacket();
       stringOne = "";
       // reset counter 
       x = 0 ; 
     }
   
   }
   //Serial.println(); 
  }
}





 // task one takes care of collecting data and sending to queue 
void taskThree( void * parameter )
{

  portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 1000;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
    

  // infinite loop of checking sensor data 
    for(  ; ; ){

       
        ENCODER_MOTION_NOW.Current_Day = 100;

        //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );
           
            //clears TrigPin
            digitalWrite(trigPinB, LOW);
            delayMicroseconds(2); 
            
             //sets the trigPin HIGH 
            digitalWrite(trigPinB, HIGH);
            delayMicroseconds(10); 
            digitalWrite(trigPinB, LOW);

            // Reads echoPin , returns duration 
            // calculate distance  
          
          Serial.print("Sensor B  ");
          Serial.print(LastPulseTimeB);
          Serial.print('\t');
          distanceB = (LastPulseTimeB/2)*(.3432); 
          Serial.print((distanceB));
          Serial.println("mm");
    
        ENCODER_MOTION_NOW.Current_DistanceB = distanceB;
            //Sending to Queue
       xQueueSend(xQueueENCODER_Readings,(void *) &ENCODER_MOTION_NOW, portMAX_DELAY );
       
    }
 
}


 // task one takes care of collecting data and sending to queue 
void taskFour( void * parameter )
{

  portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 1000;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
    

  // infinite loop of checking sensor data 
    for(  ; ; ){

       
        ENCODER_MOTION_NOW.Current_Day = 100;

        //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );
           
            //clears TrigPin
            digitalWrite(trigPinC, LOW);
            delayMicroseconds(2); 
            
             //sets the trigPin HIGH 
            digitalWrite(trigPinC, HIGH);
            delayMicroseconds(10); 
            digitalWrite(trigPinC, LOW);

            // Reads echoPin , returns duration 
            // calculate distance  
          
          Serial.print("Sensor C  ");
          Serial.print(LastPulseTimeC);
          Serial.print('\t');
          distanceC = (LastPulseTimeC/2)*(.3432); 
          Serial.print((distanceC));
          Serial.println("mm");
    
        ENCODER_MOTION_NOW.Current_DistanceC = distanceC;
            //Sending to Queue
       xQueueSend(xQueueENCODER_Readings,(void *) &ENCODER_MOTION_NOW, portMAX_DELAY );
       
    }
 
}

// task one takes care of collecting data and sending to queue 
void taskFive( void * parameter )
{

  portTickType lastTimeRun;
  
  // checks the sensosor evey 1000 ms 
  const TickType_t xFrequency = 1000;

 
// Initialise the lastTimeRun variable with the current time.
    lastTimeRun = xTaskGetTickCount();
    

  // infinite loop of checking sensor data 
    for(  ; ; ){

       
        ENCODER_MOTION_NOW.Current_Day = 100;

        //block the task for specific amount of time 
          vTaskDelayUntil( &lastTimeRun, xFrequency );
           
            //clears TrigPin
            digitalWrite(trigPinD, LOW);
            delayMicroseconds(2); 
            
             //sets the trigPin HIGH 
            digitalWrite(trigPinD, HIGH);
            delayMicroseconds(10); 
            digitalWrite(trigPinD, LOW);

            // Reads echoPin , returns duration 
            // calculate distance  
          
          Serial.print("Sensor D  ");
          Serial.print(LastPulseTimeD);
          Serial.print('\t');
          distanceD = (LastPulseTimeD/2)*(.3432); 
          Serial.print((distanceD));
          Serial.println("mm");
    
        ENCODER_MOTION_NOW.Current_DistanceD = distanceD;
            //Sending to Queue
       xQueueSend(xQueueENCODER_Readings,(void *) &ENCODER_MOTION_NOW, portMAX_DELAY );
       
    }
 
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

