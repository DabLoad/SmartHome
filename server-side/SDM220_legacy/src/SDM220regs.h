#ifndef SDM220REGS_CPP_
#define SDM220REGS_CPP_

#include <iostream>
#include <map>
#include <string>
using namespace std;

#if 0
const map <string, uint16_t> SDM220regsStr = {
	{"Line_to_neutral_volts",  0x0000},//Volts Напряжение
	{"Current", 			   0x0006},//Amps	Ток
	{"Active_power", 		   0x000C},//Watts	Активная мощность
	{"Apparent_power", 		   0x0012},//VoltAmps	Полная мощность
	{"Reactive_power", 		   0x0018},//VAr	Реактивная мощность
	{"Power_factor", 		   0x001E},//None	Коэффициент мощности
	{"Phase_angle", 		   0x0024},//Degree	Угол сдвига Фазы
	{"Frequency", 			   0x0046},//Hz	Частота
	{"Import_active_energy",   0x0048},//kwh	Полученная активная энергия
	{"Export_active_energy",   0x004A},//kwh	Сгенерированная активная энергия
	{"Import_reactive_energy", 0x004C},//kvarh	Полученная реактивная энергия
	{"Export_reactive_energy", 0x004E},//kvarh	Сгенерированная реактивная энергия
	{"Total_active_energy",    0x0056},//kwh	Общая активная энергия
	{"Total_reactive_energy",  0x0058}//kvarh	Общая реактивная энергия
};

const map <string, uint16_t> SDM220regsStrFull = {
	{"Line_to_neutral_volts",  0x0000},//Volts Напряжение
	{"Current", 			   0x0006},//Amps	Ток
	{"Active_power", 		   0x000C},//Watts	Активная мощность
	{"Apparent_power", 		   0x0012},//VoltAmps	Полная мощность
	{"Reactive_power", 		   0x0018},//VAr	Реактивная мощность
	{"Power_factor", 		   0x001E},//None	Коэффициент мощности
	{"Phase_angle", 		   0x0024},//Degree	Угол сдвига Фазы
	{"Frequency", 			   0x0046},//Hz	Частота
	{"Import_active_energy",   0x0048},//kwh	Полученная активная энергия
	{"Export_active_energy",   0x004A},//kwh	Сгенерированная активная энергия //?
	{"Import_reactive_energy", 0x004C},//kvarh	Полученная реактивная энергия
	{"Export_reactive_energy", 0x004E},//kvarh	Сгенерированная реактивная энергия
	{"0x54", 				   0x54},
	{"Total_active_energy",    0x0056},//kwh	Общая активная энергия
	{"Total_reactive_energy",  0x0058},//kvarh	Общая реактивная энергия
	{"0x5A", 				   0x5A},
	{"0x102", 				   0x102},
	{"0x108",				   0x108},
	{"0x156",				   0x156},
	{"0x158", 				   0x158}
};
#endif
const map <uint8_t,string> SDM220regsNameFull = {
	{0, "Line_to_neutral_volts"},//Volts Напряжение
	{1, "Current"},//Amps	Ток
	{2, "Active_power"},//Watts	Активная мощность
	{3, "Apparent_power"},//VoltAmps	Полная мощность
	{4, "Reactive_power"},//VAr	Реактивная мощность
	{5, "Power_factor"},//None	Коэффициент мощности
	{6, "Phase_angle"},//Degree	Угол сдвига Фазы
	{7, "Frequency"},//Hz	Частота
	{8, "Import_active_energy"},//kwh	Полученная активная энергия
	{9, "Export_active_energy"},//kwh	Сгенерированная активная энергия //?
	{10,"Import_reactive_energy"},//kvarh	Полученная реактивная энергия
	{11,"Export_reactive_energy"},//kvarh	Сгенерированная реактивная энергия
	{12,"0x0054"},
	{13,"Total_active_energy"},//kwh	Общая активная энергия
	{14,"Total_reactive_energy"},//kvarh	Общая реактивная энергия
	{15,"0x5A"},
	{16,"0x00102"},
	{17,"0x0108"},
	{18,"0x0156"},
	{19,"0x0158"}
};

const map <uint8_t,string> SDM220regsName = {
	{0, "Line_to_neutral_volts"},//Volts Напряжение
	{1, "Current"},//Amps	Ток
	{2, "Active_power"},//Watts	Активная мощность
	{3, "Apparent_power"},//VoltAmps	Полная мощность
	{4, "Reactive_power"},//VAr	Реактивная мощность
	{5, "Power_factor"},//None	Коэффициент мощности
	{6, "Phase_angle"},//Degree	Угол сдвига Фазы
	{7, "Frequency"},//Hz	Частота
	{8, "Import_active_energy"},//kwh	Полученная активная энергия
	{9, "Export_active_energy"},//kwh	Сгенерированная активная энергия //?
	{10,"Import_reactive_energy"},//kvarh	Полученная реактивная энергия
	{11,"Export_reactive_energy"},//kvarh	Сгенерированная реактивная энергия
	{12,"Total_active_energy"},//kwh	Общая активная энергия
	{13,"Total_reactive_energy"}//kvarh	Общая реактивная энергия
};

const map <uint8_t,string> SDM220regsNameReduced = {
	{0, "Line_to_neutral_volts"},//Volts Напряжение
	{1, "Current"},//Amps	Ток
	{2, "Active_power"},//Watts	Активная мощность
	{3, "Apparent_power"},//VoltAmps	Полная мощность
	{4, "Reactive_power"},//VAr	Реактивная мощность
	{5, "Power_factor"},//None	Коэффициент мощности
	{6, "Phase_angle"},//Degree	Угол сдвига Фазы
	{7, "Frequency"},//Hz	Частота
	{8, "Import_active_energy"},//kwh	Полученная активная энергия
};

const map <uint8_t,uint16_t> SDM220regsIntFull = {
	{0, 0x0000},//Volts Напряжение
	{1, 0x0006},//Amps	Ток
	{2, 0x000C},//Watts	Активная мощность
	{3, 0x0012},//VoltAmps	Полная мощность
	{4, 0x0018},//VAr	Реактивная мощность
	{5, 0x001E},//None	Коэффициент мощности
	{6, 0x0024},//Degree	Угол сдвига Фазы
	{7, 0x0046},//Hz	Частота
	{8, 0x0048},//kwh	Полученная активная энергия
	{9, 0x004A},//kwh	Сгенерированная активная энергия //?
	{10,0x004C},//kvarh	Полученная реактивная энергия
	{11,0x004E},//kvarh	Сгенерированная реактивная энергия
	{12,0x0054},
	{13,0x0056},//kwh	Общая активная энергия
	{14,0x0058},//kvarh	Общая реактивная энергия
	{15,0x005A},
	{16,0x0102},
	{17,0x0108},
	{18,0x0156},
	{19,0x0158}
};

const map <uint8_t, uint16_t> SDM220regsInt = {
	{0, 0x0000},//Volts
	{1, 0x0006},//Amps
	{2, 0x000C},//Watts
	{3, 0x0012},//VoltAmps
	{4, 0x0018},//VAr
	{5, 0x001E},//None
	{6, 0x0024},//Degree
	{7, 0x0046},//Hz
	{8, 0x0048},//kwh
	{9, 0x004A},//kwh
	{10, 0x004C},//kvarh
	{11, 0x004E},//kvarh
	{12, 0x0156},//kwh
	{13, 0x0158}//kvarh
};

const map <uint8_t, uint16_t> SDM220regsIntReduced = {
	{0, 0x0000},//Volts
	{1, 0x0006},//Amps
	{2, 0x000C},//Watts
	{3, 0x0012},//VoltAmps
	{4, 0x0018},//VAr
	{5, 0x001E},//None
	{6, 0x0024},//Degree
	{7, 0x0046},//Hz
	{8, 0x0048},//kwh
};

/*const int SDM220regs[]  =  {
		0x0000,
		0x0006,
		0x000C,
		0x0012,
		0x0018,
		0x001E,
		0x0024,
		0x0046,
		0x0048,
		0x004A,
		0x004C,
		0x004E,
		0x0056,
		0x0058
};
*/

#endif /* SDM220REGS_CPP_ */
