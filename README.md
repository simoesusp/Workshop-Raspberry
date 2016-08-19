# Workshop-Raspberry

################ Facebook Group ################
https://www.facebook.com/groups/raspbcc/?fref=ts
################################################
Next meeting TODAY (19/08/2016): 08:00h at Lab 6306

Repository of examples and tutorials for projects combining RaspberryPi + Arduino.

Created and maintained by a group of students of the University of São Paulo.

With RaspberryPi 2, do not forget to configure GCC to compile optimizing to its ARM7: 
gcc -O3 -march=armv7-a -mfpu=vfp -mfloat-abi=hard -Wall test.c -o test

1-	Under folder Raspbian: you will find configuration files and tips to set Debian up correctly for the RAspberryPi2 board.

2-	Under folder SoftwareRaspberry: you will find c code that program RaspberryPi to command an Arduino (Arduino Mini Pro) to control multiple devices and read multiple sensors.

3-	Under folder SoftwareArduino: you will find c code that program Arduino (Arduino Mini Pro) to communicate with RaspberryPi and to control multiple devices and read multiple sensors.

4-	Do not forget also to take a look on our other project with a RaspberryPi controlling a High Speed Robot (85 Km/h) at: https://github.com/simoesusp/high-speed-robot

5-	FernandosProject PDF also present a very interesting design of a remote controlled robot using 2 Raspberrys and Arduinos to pilot a camera using robot via FPV.

6-  Checkout how to connect RaspberryPi and Arduino on Figure ConectingRasptoArduino.jpg. It is just one of the 1000 ways to connect them... but one that works! Do not forget to enable the Raspberry Serial Port with raspi-config --> Advanced Options --> Enable Serial Port.


Have fun!!
Eduardo Simoes


