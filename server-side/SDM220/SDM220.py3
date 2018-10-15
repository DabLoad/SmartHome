#!/usr/bin/env python
import os, signal, time, minimalmodbus, mysql.connector;
#import argparse;
from shutil import rmtree;
from struct import *;
#print(os.path.dirname(os.path.realpath(__file__)));
with open(os.path.dirname(os.path.realpath(__file__)) + "/ProgData.txt", "r") as file:
    ProgData = [row.strip() for row in file]
    #print (ProgData);
#SQLinit
SDM220CodesSQL = {
	"Start": 0x01,#1<<0
	"Import_active_energy_overflow": 0x02,#1<<1
	"Start|Import_active_energy_overflow": 0x03,#1<<1 | 1<<0
	"Closed": 0x04,#1<<2
	"IOError": 0x10,#1<<4
	"CRCError": 0x20,#1<<5
	"OSerr": 0x40,#1<<6
	"OTHERerror": 0x80, #1<<7
	"TargetInstrumentNotFound": 0x80|0x10
}
SmartHomeDB = mysql.connector.connect(
  	host=ProgData[3],
  	user=ProgData[4],
  	passwd=ProgData[5],
  	database=ProgData[6]
)
SmartHomeCursor = SmartHomeDB.cursor();
#/SQLinit
#SYS_infoUtil
def SqlReadSYS_info(ID):
	SmartHomeCursor.execute("SELECT SYS_info FROM SDM220 WHERE ID =" + str(ID));
	SqlResult = SmartHomeCursor.fetchall()[0][0];
	if SqlResult:
		return SqlResult;
	else:
		return 0;

def SqlReadSYS_infoFromLastID():
	SmartHomeCursor.execute("SELECT MAX(ID) FROM SDM220");
	SqlMaxID = SmartHomeCursor.fetchall()[0][0];
	if not SqlMaxID:
		RootSqlID = 1;
	else:
		return SqlReadSYS_info(SqlMaxID);

def SqlWriteSYS_info(info, ID):
	SYS_info = SqlReadSYS_info(ID);
	if  SYS_info & info != info: #Increase memory life by reducing amount of writes to it
		SmartHomeCursor.execute("update SDM220 set SYS_info = " + str(SYS_info | info) + " where ID=" + str(ID));
		SmartHomeDB.commit();

#/SYS_infoUtil
#SqlWriteSYS_infoToLastID
def SqlWriteSYS_infoToLastID(info):
	RootSqlID = 0;
	SmartHomeCursor.execute("SELECT MAX(ID) FROM SDM220");
	SqlMaxID = SmartHomeCursor.fetchall()[0][0];

	if SqlMaxID:
		SqlWriteSYS_info(info, SqlMaxID);
#/SqlWriteSYS_infoToLastID

SqlWriteSYS_infoToLastID(SDM220CodesSQL["Start"]);

#argparce
#parser = argparse.ArgumentParser();
#parser.add_argument("UART_device", type=str, help="set target uart");
#parser.add_argument("Target_dir", type=str, help="set target dir");
#args = parser.parse_args();
#/argparce
#SerialInit
try:
	SDM220 = minimalmodbus.Instrument(ProgData[1] , 1, 'rtu');#args.UART_device
except:
	SqlWriteSYS_infoToLastID(SDM220CodesSQL["TargetInstrumentNotFound"]|SDM220CodesSQL["Closed"]);
	exit("SerialException");

SDM220.serial.baudrate= 9600;
SDM220.serial.timeout = 0.2;
#/SerialInit
#SDM220algorithmData
SDM220regsPattern = [[0x0000, 0x0026],[0x0046, 0x000A],[0x0156, 0x0004]]; #Magic Numbers!
SDM220regsInt = {
	0: 	0x0000,#Volts
	1: 	0x0006,#Amps
	2: 	0x000C,#Watts
	3: 	0x0012,#VoltAmps
	4: 	0x0018,#VAr
	5: 	0x001E,#None
	6: 	0x0024,#Degree
	7: 	0x0046,#Hz
	8: 	0x0048,#kwh
	9: 	0x004A,#kwh
	10: 0x004C,#kvarh
	11: 0x004E,#kvarh
	12: 0x0156,#kwh
	13: 0x0158 #kvarh
};
SDM220regsName = {
	0: "Line_to_neutral_volts",	#Volts 		Напряжение -
	1: "Current",				#Amps		Ток -
	2: "Active_power",			#Watts		Активная мощность -
	3: "Apparent_power",		#VoltAmps	Полная мощность
	4: "Reactive_power",		#VAr		Реактивная мощность
	5: "Power_factor",			#None		Коэффициент мощности
	6: "Phase_angle",			#Degree		Угол сдвига Фазы
	7: "Frequency",				#Hz			Частота
	8: "Import_active_energy",	#kwh		Полученная активная энергия -
	9: "Export_active_energy",	#kwh		Сгенерированная активная энергия #?
	10:"Import_reactive_energy",#kvarh		Полученная реактивная энергия
	11:"Export_reactive_energy",#kvarh		Сгенерированная реактивная энергия
	12:"Total_active_energy",	#kwh		Общая активная энергия
	13:"Total_reactive_energy"	#kvarh		Общая реактивная энергия
};
#/SDM220algorithmData

SDM220regMapCopy = [0 for i in range(0x160)];
SDM220cuttedRegsNormalized = [0 for i in range(14)];

LastTime = 0;
CreatedFiles = 0;
SQL_SDM220_values = [0 for i in range(6)];

def CloseHandler(signum, frame):
	rmtree(ProgData[2]);
	SqlWriteSYS_infoToLastID(SDM220CodesSQL["Closed"]);
	exit('EXIT');


def SingnalHandler(signum, frame):
	print(signum);
	#rmtree(ProgData[2]);
	#SqlWriteSYS_infoToLastID(SDM220CodesSQL["Start"]|SDM220CodesSQL["Closed"]);
#SignalSetup
signal.signal(1, SingnalHandler);
signal.signal(2, SingnalHandler);
signal.signal(3, SingnalHandler);
signal.signal(signal.SIGTERM, SingnalHandler)
signal.signal(15, SingnalHandler);
signal.signal(20, SingnalHandler);
signal.signal(45, CloseHandler);
#/SignalSetup
#SDM220func
def ARRcopy(outARR, inARR, outARR_addr, lenToCopy):
	i = 0;
	while i < lenToCopy:
		outARR[i + outARR_addr] = inARR[i];
		i += 1;
def SDM220readAllData():
	for i in range(3):
		try:
			ARRcopy(SDM220regMapCopy, SDM220.read_registers(SDM220regsPattern[i][0], SDM220regsPattern[i][1], 4), SDM220regsPattern[i][0], SDM220regsPattern[i][1]);
			i += 1;
		except IOError:
			#SqlWriteSYS_infoToLastID(SDM220CodesSQL["IOError"]|SDM220CodesSQL["Closed"]);
			print('IOERR');
			return SDM220CodesSQL["IOError"];
		except ValueError:
			#SqlWriteSYS_infoToLastID(SDM220CodesSQL["CRCError"]|SDM220CodesSQL["Closed"]);
			print("SDM220 CRCERR");
			return SDM220CodesSQL["CRCError"];
	return 0;
def SDM220cutAllInfo():
	for i in range(14):
		#SDM220cuttedRegPacked = pack('I',(SDM220regMapCopy[SDM220regsInt[i]] << 16) | SDM220regMapCopy[SDM220regsInt[i]]);
		SDM220cuttedRegsNormalized[i] = unpack('f', pack('I',(SDM220regMapCopy[SDM220regsInt[i]] << 16) | SDM220regMapCopy[SDM220regsInt[i] + 1]))[0];
		#SDM220cuttedRegsNormalized[i] = float((SDM220regMapCopy[SDM220regsInt[i]] << 16) | SDM220regMapCopy[SDM220regsInt[i]]);--
		i += 1;
def SDM220printInfo():
	print ('-' * 50);
	for i in range(14):
		print(SDM220regsName[i], ': ', SDM220cuttedRegsNormalized[i]);
		i += 1;
#/SDM220func
SQL_SDM220_write = "INSERT INTO SDM220 (`TimeStamp`,Line_to_neutral_volts,Current,Active_power,Import_active_energy,SYS_info) VALUES  (%s, %s, %s, %s, %s, %s)"
try:
	os.mkdir(ProgData[2]);
	pass
except:
	pass
while 1==1:
	NowTime = int(time.time());
	SDM220Code = SDM220readAllData(); 
	SDM220cutAllInfo();
	SDM220printInfo();
	if (LastTime != NowTime):
		#WriteToFile
		f = open(ProgData[2] + '/' + str(NowTime) + '.xml', 'w');
		f.write('<?xml version="1.0" encoding="us-ascii"?>\n');
		f.write('<SDM220 TimeStamp="' + str(NowTime) + '" Code="' + str(SDM220Code) + '">\n');
		for i in range(14):
			f.write('\t<' + SDM220regsName[i] + '>' +  str(SDM220cuttedRegsNormalized[i]) + '</' + SDM220regsName[i] + '>\n');
			i += 1; 
		f.write('</SDM220>');
		f.close();
		#/WriteToFile
		#WriteToSql
		#WriteToSqlOnlyImportantData
		SQL_SDM220_values[0] = NowTime;
		ARRcopy(SQL_SDM220_values, SDM220cuttedRegsNormalized, 1 , 3);
		SQL_SDM220_values[4] = SDM220cuttedRegsNormalized[8];
		SQL_SDM220_values[5] = SDM220Code;
		#/#WriteToSqlOnlyImportantData
		SmartHomeCursor.execute(SQL_SDM220_write, SQL_SDM220_values);
		SmartHomeDB.commit();
		#/WriteToSql

		CreatedFiles += 1;
		if CreatedFiles >= 61:
			try:
				os.remove(ProgData[2] + '/' + str(NowTime - 60) + '.xml');
			except:
				pass
		if CreatedFiles >= 70:
			CreatedFiles = 61;
		LastTime = int(NowTime);
