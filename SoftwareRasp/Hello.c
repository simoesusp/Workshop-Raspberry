// gcc -O3 -march=armv7-a -mfpu=vfp -mfloat-abi=hard -Wall test.c -o test


#include <stdio.h>
#include <stdlib.h>

int main()
{
int a = 6;

printf("Hello Rasp!  A = %d", a);

return 0;
}