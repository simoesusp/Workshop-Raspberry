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
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
  pinMode(13, OUTPUT);
  
  // Open hardware serial communications and wait for port to open:
  Serial.begin(9600);
  
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

}

void loop() 
{
  //Serial.write("Oi");
  //mySerial.write("la vem !!!");
  //delay(500);              // wait for a second

  int a, i, j = 0;
  int v[500];  // maximun message size
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
              if(v[j+5]=='5' && v[j+4]==' ' && v[j+3]=='d' && v[j+2]=='n' && v[j+1]=='a' && v[j]=='m')
                 {
                     digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                     delay(5000);              // wait for a second
                     digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                 }
            
       }
    }
}
