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


  int b = 0;
 

  for (;;)
  {
    serialPrintf(fd, "command %dX", b);        // Sends message to serial port (Arduino)
    printf("Mandou command %dX\n", b);


    
    printf("\nVolta %d\n",b);
    b++;
    delay(2000);
    if (b==3) break;
  }
  
  serialClose(fd);    // It is very important to close the serial port so that it can be used by other programs...
  return 0;            // But it seams that debian closes it automaticaly for us ...
  
}