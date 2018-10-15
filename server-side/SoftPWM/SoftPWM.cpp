#include <wiringPi.h>
int main()
{    
	wiringPiSetup();       
	int t_on, t_off;

	int d, i; 
	d=20;
		
	t_on=50*d;
	t_off=50*(30-d); 
	for (i=10; i!=0; i++) 
	{             
		digitalWrite(16, LOW);   
		delayMicroseconds(t_off);    
		digitalWrite(16, HIGH);       
		delayMicroseconds(t_on);     
	}
return 0;
}
