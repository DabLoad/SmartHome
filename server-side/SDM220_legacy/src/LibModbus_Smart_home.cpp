#include <iostream>
#include <ctime>
#include <fstream>
#include "../lib/libmodbus-3.0.6/src/modbus.h"
#include "../lib/XMLwriter/XMLwriter.h"
#include <map>
#include <iterator>
#include <signal.h>
#include <cstring>

#include "SDM220regs.h"

using namespace std;

float bintofloat(uint32_t x) {
    float *f = (float *)&x;
    return *f;
}

volatile sig_atomic_t flag = 0;

void SIGHUP_func (int sig){flag = 1 ;}
void SIGINT_func (int sig){flag = 2 ;}
void SIGQUIT_func(int sig){flag = 3 ;}
void SIGKILL_func(int sig){flag = 9 ;}
void SIGTERM_func(int sig){flag = 15;}
void SIGTSTP_func(int sig){flag = 20;}

float SDM220registersConnected[14];
uint16_t SDM220buf[0x28];
uint16_t SDM220regMapCopy[0x160] = {0};
volatile int8_t ModbusCode[3], FinalModbusCode = 1;
uint8_t CreatedFiles = 0;

time_t LastTime = 0;
time_t NowTime;
ofstream XMLout;

uint16_t SDM220regsPattern[3][2] = {{0x0000, 0x0026},{0x0046, 0x000A},{0x0156, 0x0004}};

int main(int argc, char **argv)
{
	if(argc != 3) return 0;
	#if 1
	signal(SIGHUP, SIGHUP_func);
	signal(SIGINT, SIGINT_func);
	signal(SIGQUIT, SIGQUIT_func);
	signal(SIGKILL, SIGKILL_func);
	signal(SIGTERM, SIGTERM_func);
	signal(SIGTSTP, SIGTSTP_func);
	#endif
	modbus_t *SDM220 = modbus_new_rtu(argv[1], 9600, 'N', 8, 1);
	modbus_set_slave(SDM220, 1);
	if (modbus_connect(SDM220) == -1)
	{
		cout << "ERR" << endl;
		return -1;
	}
	system((string("mkdir ") + string(argv[2])).c_str());
	system((string("rm -rf ") + string(argv[2]) + string("/*")).c_str());
	while(1)
	{
		for(uint32_t i = 0; i < 3; i++)
		{
			ModbusCode[i] = modbus_read_input_registers(SDM220, SDM220regsPattern[i][0], SDM220regsPattern[i][1], SDM220buf);
			memcpy(SDM220regMapCopy + (SDM220regsPattern[i][0]), SDM220buf,  SDM220regsPattern[i][1] * 2);
		}
		for(uint32_t i = 0; i < SDM220regsInt.size(); i++)
		{
			SDM220registersConnected[i] = bintofloat((SDM220regMapCopy[SDM220regsInt.at(i)]<<16) | (SDM220regMapCopy[SDM220regsInt.at(i) + 1]));
		}
		if(ModbusCode[0] == -1 || ModbusCode[1] == -1 || ModbusCode[2] == -1) { FinalModbusCode == -1; }
		else { FinalModbusCode == 14; }
		NowTime = std::time(nullptr);
		if(LastTime != NowTime){

		XMLout.open((string(argv[2]) + string("/") + string(to_string(NowTime)) + string(".xml")).c_str(), ios_base::out | ios::trunc);
		XMLwriter XMLwriter(XMLout);
		XMLwriter.openElt("SDM220").attr("TimeStamp", to_string(NowTime)).attr("ModbusCode", to_string(FinalModbusCode));
		for(uint32_t i = 0; i < SDM220regsInt.size(); i++)
		{
			XMLwriter.openElt(SDM220regsName.at(i).c_str()).content(to_string(SDM220registersConnected[i]).c_str()).closeElt();
		}
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
			system((string("rm -Rf ") + string(argv[2])).c_str());
			modbus_close(SDM220);
			modbus_free(SDM220);
			return 0;
		}
	}
	modbus_close(SDM220);
	modbus_free(SDM220);
	return 0;
}
/*{"Line_to_neutral_volts",  0x0000},//Volts Напряжение
{"Current", 			   0x0006},//Amps	Ток
{"Active_power", 		   0x000C},//Watts	Активная мощность
{"Apparent_power", 		   0x0012},//VoltAmps	Полная мощность
{"Reactive_power", 		   0x0018},//VAr	Реактивная мощность
{"Power_factor", 		   0x001E},//None	Коэффициент мощности
{"Phase_angle", 		   0x0024},//Degree	Угол сдвига Фазы
{"Frequency", 			   0x0046},//Hz	Частота
{"Import_active energy",   0x0048},//kwh	Полученная активная энергия
{"Export_active energy",   0x004A},//kwh	Сгенерированная активная энергия //?
{"Import_reactive energy", 0x004C},//kvarh	Полученная реактивная энергия
{"Export_reactive energy", 0x004E},//kvarh	Сгенерированная реактивная энергия
{"0x54", 				   0x54},
{"Total_active energy",    0x0056},//kwh	Общая активная энергия
{"Total_reactive energy",  0x0058},//kvarh	Общая реактивная энергия
{"0x5A", 				   0x5A},
{"0x102", 				   0x102},
{"0x108",				   0x108},
{"0x156",				   0x156},
{"0x158", 				   0x158}
};*/
