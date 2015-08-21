/*
  Software serial receive commands from RaspberryPi and turn led on

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 stores in vector v the message
 sends message back to RaspberryPi via software serial
 checks if message = command 5 and turn on led for 5 sec

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 by Simoes
 based on Tom Igoe and Mikal Hart's example
*/

#define trigPin 7
#define echoPin 8
#define motorleft 9               // the pin that the LED is attached to
//#define motorright 10



#include <SoftwareSerial.h>

#include <PWM.h>

int32_t frequency = 100;    //frequency (in Hz)
uint8_t pwm_value = 25;     // pwm_value  = Motor Stopped   :  Pulse Widh = 1ns
long duration, distance;
int a, i, j = 0;
int v[500];  // maximun message size


SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
  pinMode(13, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  pinMode(motorleft, OUTPUT);

  // Open hardware serial communications and wait for port to open:
  Serial.begin(9600);
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  //initialize all timers except for 0, to save time keeping functions
  InitTimersSafe(); 
  //sets the frequency for the specified pin
  bool success = SetPinFrequencySafe(motorleft, frequency);
  //if the pin frequency was set successfully, pin 13 turn on
  if(success)     digitalWrite(13, HIGH);    
  else            digitalWrite(13, LOW);
  
  pwmWrite(motorleft, pwm_value);   // pwmWrite(pin, DUTY * 255 / 100);  
                                    // Can use pwm_values between 30 (min speed) to 58 (max speed) 
                                    // minimum value to turn on motor is 41, then it can be reduced up to 30
  
  delay(5000);    // Time to turn motors on with low throtle 
  digitalWrite(13, LOW);


}

void loop() 
{
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW

  while(1)  // run over and over
    {
        if (Serial.available())   // Receives from the hardware serial, sends to software serial.
      {
          mySerial.write(Serial.read());
      }
    
    if (mySerial.available())
      {
          i = 0;
          while(1)
            {
                // Receives from software serial, sends to hardware serial.
                a=mySerial.read();
                Serial.write(a);
                v[i] = a;  //  stores in vector v the message
                if(a=='X') break;
                while (mySerial.available()==0);  // Wait for next byte
                i++;        
            }
          // sends message back to RaspberryPi via software serial
          for(j = 0; j < i; j++)
               mySerial.write(v[j]);
               
          for(j = 0; j < (i-5); j++)    //  checks if message = command 5 and turn on led for 5 sec
              {
              if(v[j+5]=='5' && v[j+4]==' ' && v[j+3]=='d' && v[j+2]=='n' && v[j+1]=='a' && v[j]=='m')
                 {
                      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                                         
                      digitalWrite(trigPin, LOW);  // Added this line
                      delayMicroseconds(2); // Added this line
                      digitalWrite(trigPin, HIGH);
                      delayMicroseconds(10); // Added this line
                      digitalWrite(trigPin, LOW);
                      duration = pulseIn(echoPin, HIGH);
                      distance = (duration/2) / 29.1;
                      
                      if (distance >= 600 || distance <= 0){
                        Serial.println("Out of range");
                      }
                      else {
                        Serial.print(distance);
                        Serial.println(" cm");
                        mySerial.println("\nSonar Reading = ");
                        mySerial.write(distance);
                        mySerial.println("cm");
                      }
                      
                     
                     delay(5000);              // wait for a second
                     digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                 }



              if(v[j+5]=='8' && v[j+4]==' ' && v[j+3]=='d' && v[j+2]=='n' && v[j+1]=='a' && v[j]=='m')
                 {
                     digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                     
                     mySerial.println("\nLiga Motor");
                     Serial.println("\nLiga Motor");                    
                     pwm_value = 45;
                     pwmWrite(motorleft, pwm_value);  // pwmWrite(pin, DUTY * 255 / 100);  
                                                     // Can use pwm_values between 30 (min speed) to 58 (max speed) 
                                                     // minimum value to turn on motor is 41, then it can be reduced up to 30

                      
                     delay(10000);              // wait for a second

                     mySerial.println("\nDesliga Motor");                     
                     Serial.println("\nDesliga Motor");
                     pwm_value = 25;
                     pwmWrite(motorleft, pwm_value);  
                     
                     digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                 }
              }            
       }
    }
}


