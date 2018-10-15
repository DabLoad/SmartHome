#include <wiringPi.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include "XMLwriter.h"
#include <signal.h>
#include <cstring>
#include "math.h"

#define MAX_TIMINGS 85
#define DHT_PIN 7
static float TemperatureBuf = 0, HumidityBuf; 
using namespace std;

volatile sig_atomic_t flag = 0;

void SIGHUP_func (int sig){flag = 1 ;}
void SIGINT_func (int sig){flag = 2 ;}
void SIGQUIT_func(int sig){flag = 3 ;}
void SIGKILL_func(int sig){flag = 9 ;}
void SIGTERM_func(int sig){flag = 15;}
void SIGTSTP_func(int sig){flag = 20;}

float average(float *vector, uint8_t length)
{
    float avg = 0; // среднее арифметическое
    for (uint8_t i = 0; i < length; i++)
    {
        avg += vector[i]; // накапливаем сумму элементов массива
    }
    return (avg / length); // накопленную сумму делим на количество элементов и возвращаем полученно значение в main функцию
}

void read_dht_data(float *humidity, float *temperature) //2 floats
{
    uint8_t data[5] = {0};
    uint8_t laststate    = HIGH;
    uint8_t counter        = 0;
    uint8_t j            = 0, i;
 
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;
    pinMode( DHT_PIN, OUTPUT );
    digitalWrite( DHT_PIN, LOW );
    delay( 18 );
    pinMode( DHT_PIN, INPUT );
    for ( i = 0; i < MAX_TIMINGS; i++ )
    {
        counter = 0;
        while ( digitalRead( DHT_PIN ) == laststate )
        {
            counter++;
            delayMicroseconds( 1 );
            if ( counter == 255 )
            {
                break;
            }
        }
        laststate = digitalRead( DHT_PIN );
 
        if ( counter == 255 )
            break;
        if ( (i >= 4) && (i % 2 == 0) )
        {
            data[j / 8] <<= 1;
            if ( counter > 16 )
                data[j / 8] |= 1;
            j++;
        }
    }
    if ( (j >= 40) &&
         (data[4] == ( (data[0] + data[1] + data[2] + data[3]) & 0xFF) ) )
    {
        *humidity = (float)((data[0] << 8) + data[1]) / 10;
        if ( *humidity > 100 )
        {
            *humidity = data[0];    // for DHT11
        }
        *temperature = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
        if ( *temperature > 125 )
        {
            *temperature = data[2];    // for DHT11
        }
        if ( data[2] & 0x80 )
        {
            *temperature = -*temperature;
        }
        HumidityBuf = *humidity;
        TemperatureBuf = *temperature;
    } 
    else  
    {
        *humidity = HumidityBuf;
        *temperature = TemperatureBuf;
    }
}

uint8_t ReaderNum = 5;
float ReaderDataHumiditySt[5] = {0};
float ReaderDataTemperatureSt[5] = {0};
time_t LastTime = 0;
time_t NowTime;
ofstream XMLout;
float ReaderDataHumidity = 0, ReaderDataTemperature = 0;
uint8_t CreatedFiles = 0; 
int main(int argc, char **argv)
{
    if ( wiringPiSetup() == -1 ) exit( 1 );
	signal(SIGHUP, SIGHUP_func);
	signal(SIGINT, SIGINT_func);
	signal(SIGQUIT, SIGQUIT_func);
	signal(SIGKILL, SIGKILL_func);
	signal(SIGTERM, SIGTERM_func);
	signal(SIGTSTP, SIGTSTP_func);
	
	system((string("mkdir ") + string(argv[1])).c_str());
	system((string("rm -rf ") + string(argv[1]) + string("/*")).c_str());
    read_dht_data(&ReaderDataHumiditySt[0], &ReaderDataTemperatureSt[0]); //first reading always 0
	while(1)
	{
        for(uint8_t i = 0; i < ReaderNum; i++)
        {
		read_dht_data(&ReaderDataHumiditySt[i], &ReaderDataTemperatureSt[i]);
        delay( 470 );
        }

        ReaderDataHumidity = average(ReaderDataHumiditySt, 5);
        ReaderDataTemperature = average(ReaderDataTemperatureSt, 5);
        cout << ReaderDataHumidity << " " << ReaderDataTemperature <<endl;
      	//delay( 470 ); /* wait 1 second before next read */
		NowTime = time(nullptr);
		if(LastTime != NowTime)
        {
		XMLout.open((string(argv[1]) + string("/") + string(to_string(NowTime)) + string(".xml")).c_str());
		XMLwriter XMLwriter(XMLout);
		XMLwriter.openElt("DHT22").attr("TimeStamp", to_string(NowTime));

		XMLwriter.openElt("Temperature").content(to_string(ReaderDataHumidity).c_str()).closeElt();
		XMLwriter.openElt("Temperature").content(to_string(ReaderDataTemperature).c_str()).closeElt();

		XMLwriter.closeAll();
		XMLout.close();
		CreatedFiles++;
		if(CreatedFiles >= 61)
		{
			system((string("rm ") + string(argv[2]) + string("/") + string(to_string(NowTime-60)) + string(".xml")).c_str());
			if(CreatedFiles >= 70) CreatedFiles = 61;
		}
		LastTime = NowTime;
		}
		if(flag == 1 || flag == 2 || flag == 3 || flag == 9 || flag == 15 || flag == 20)
		{
			system((string("rm -Rf ") + string(argv[1])).c_str());
			return 0;
		}
	}
}
