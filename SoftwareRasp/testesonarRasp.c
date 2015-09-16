#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <string.h>

FILE *fp;
 
#define TRIG0 17
#define ECHO0 18
 
//#define TRIG1 27
//#define ECHO1 22 
 
//#define TRIG2 23
//#define ECHO2 24  


 
void setup() {
        wiringPiSetupGpio();
        pinMode(TRIG0, OUTPUT);
        pinMode(ECHO0, INPUT);
        /*
		pinMode(TRIG1, OUTPUT);
        pinMode(ECHO1, INPUT);
		
		pinMode(TRIG2, OUTPUT);
        pinMode(ECHO2, INPUT);
		*/
		
        //TRIG pin must start LOW
        digitalWrite(TRIG0, LOW);
		//digitalWrite(TRIG1, LOW);
		//digitalWrite(TRIG2, LOW);
        delay(30);
		
		
}
 
float getCM(int TRIG, int ECHO) {		
	
		//Send trig pulse
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(20);
        digitalWrite(TRIG, LOW);

        //Wait for echo start
		printf("ta baixo    ");
        while(digitalRead(ECHO) == LOW);
		long startTime = micros();
		long travelTime = 0.0;
		printf("ta alto   ");
        
	  while(digitalRead(ECHO) == HIGH){
		travelTime = micros() - startTime;
		if (travelTime >= 14640 ) goto sai;  // 2,50m fundo de escala
	  }
		
	  sai:;
		
		//Get distance in cm
        float distance = travelTime / 58;
 
        printf("%f",distance);
		//printf("\n");
		return (distance);
}
 
int main(void) {		
		
		float d0,d1;
		int count=0;
					printf("\npasso1: ");

		setup();
		//delayMicroseconds(2000000);

		
							printf("\npasso2: ");

		
		
		while(1){
			
			printf("\nSENSOR0: ");
			d0 = getCM(TRIG0, ECHO0);
			//printf("\nSENSOR1: ");
			//d1 = getCM(TRIG1, ECHO1);
			
			
			delayMicroseconds(250000);
			count++;
			//printf("count: %d", count);
		}
		
        return 0;
}
