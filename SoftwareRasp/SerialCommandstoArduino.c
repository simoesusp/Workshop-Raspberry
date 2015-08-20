/*
 * 
 *    Example program to read and write bytes from/to the Serial line
 *  It communicates with an Arduino which is responsible to read sensors and control devices such as brushless motors
 * 

Gide: http://www.cyberciti.biz/tips/connect-soekris-single-board-computer-using-minicom.html

Serial Wiring Pi library: http://wiringpi.com/download-and-install/
Wiring Pi library commands:      http://wiringpi.com/reference/serial-library/

    gcc -o nomeprograma nomeprograma.c -lwiringPi
     
Do not forget to optimize GCC to RaspberryPi2  Arm7
    gcc -O3 -march=armv7-a -mfpu=vfp -mfloat-abi=hard -Wall test.c -o test -lwiringPi


./nomeprograma --> to run the programa
Ctrl+C terminate running program
  
  
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>        // Necessary only to print serial start error messages
#include <errno.h>        // Necessary only to print serial start error messages

#include <wiringSerial.h>    // Allow to access i/o pins and hardware serial port

int main ()
{
  int fd ;
  printf("Abrindo Serial\n");

  if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
      {
        printf ("Unable to open serial device: %s\n", strerror (errno)) ;
        return 1 ;
      }
  else printf("Abriu!!\n");


  int distance = 0;
  int b = 0;
  int a = 0;
  int i = 0;
  int v[20];

  for (;;)
  {
    serialPrintf(fd, "command %dX", b);        // Sends message to serial port (Arduino)
    printf("Mandou command %dX\n", b);

    while((a=serialDataAvail(fd))==0);
    delay(50);
    a = serialDataAvail(fd);    // Have to read "a" again after delay because is takes a while to receive all bytes!
    for (i=a;i>0;i--){            // a = nr. of bytes received
        if (b == 5)                // If Command 5 prepare to receive ultrasound mesured distance
            {putchar (v[i]=serialGetchar (fd));        // debug serial communication
            if(a > 5)        // reads byte right before word "cm" into variable "distance"
                { if(v[i] == 'm' && v[i+1] == 'c')   distance = v[i+2];
                }
        
            }
        else putchar (serialGetchar (fd) );        // debug serial communication
        }
    if (b == 5)     // If Command = 5, print ultrasound mesured distance
        printf("\nDistancia = %d cm", distance);
    
    printf("\nVolta %d\n",b);
    b++;
    delay(2000);
    if (b==10) break;
  }
  
  serialClose(fd);    // It is very important to close the serial port so that it can be used by other programs...
  return 0;            // But it seams that debian closes it automaticaly for us ...
  
}