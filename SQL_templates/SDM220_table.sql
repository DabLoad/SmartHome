create table SDM220_long (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL UNIQUE, 
	`TimeStamp` INT UNSIGNED NOT NULL UNIQUE, 
	Line_to_neutral_volts FLOAT(10,7) NOT NULL,
	Current FLOAT(10,7) NOT NULL,
	Active_power   FLOAT(12,7) NOT NULL,
	Apparent_power   FLOAT(12,7) NOT NULL,
	Reactive_power   FLOAT(12,7) NOT NULL,
	Power_factor  FLOAT(12,7) NOT NULL,
	Phase_angle   FLOAT(9,7) NOT NULL,
	Frequency   FLOAT(9,7) NOT NULL,
	Import_active_energy   FLOAT(12,7) NOT NULL,
	Export_active_energy  FLOAT(12,7) NOT NULL,
	Import_reactive_energy   FLOAT(12,7) NOT NULL,
	Export_reactive_energy   FLOAT(12,7) NOT NULL,
	Total_active_energy   FLOAT(12,7) NOT NULL,
	Total_reactive_energy FLOAT(12,7) NOT NULL,
	PRIMARY KEY(TimeStamp)
	);

create table SDM220 (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL UNIQUE, 
	`TimeStamp` INT UNSIGNED NOT NULL UNIQUE, 
	Line_to_neutral_volts FLOAT(21,18) NOT NULL,
	Current FLOAT(21,18) NOT NULL,
	Active_power   FLOAT(23,18) NOT NULL,
	Import_active_energy   FLOAT(23,18) NOT NULL,
	SYS_info TINYINT UNSIGNED DEFAULT 0,
	PRIMARY KEY(TimeStamp)
	);

create table SDM220 (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL UNIQUE, 
	`TimeStamp` INT UNSIGNED NOT NULL UNIQUE, 
	Line_to_neutral_volts FLOAT(10,7) NOT NULL,
	Current FLOAT(10,7) NOT NULL,
	Active_power   FLOAT(12,7) NOT NULL,
	Import_active_energy   FLOAT(8,3) NOT NULL,
	SYS_info TINYINT UNSIGNED NULL,
	PRIMARY KEY(TimeStamp)
	);

INSERT INTO SDM220 (
`TimeStamp`, 
Line_to_neutral_volts,
Current,
Active_power,
Apparent_power,
Reactive_power,
Power_factor,
Phase_angle,
Frequency,
Import_active_energy,
Export_active_energy,
Import_reactive_energy,
Export_reactive_energy,
Total_active_energy,
Total_reactive_energy,
) 
VALUES ();

create table DHT22 (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL UNIQUE, 
	`TimeStamp` INT UNSIGNED NOT NULL UNIQUE, 
	Humidity FLOAT NOT NULL,
	Temperature FLOAT NOT NULL,
	PRIMARY KEY(TimeStamp)
	);

create table Texts (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL UNIQUE,
	`TimeStamp` INT UNSIGNED NOT NULL,
	Author VARCHAR(32) NOT NULL,
	`Text` MEDIUMTEXT NOT NULL,
	PRIMARY KEY(ID)
); 

create table ads (
	ID INT UNSIGNED AUTO_INCREMENT NOT NULL UNIQUE, 
	`TimeStamp` FLOAT NOT NULL UNIQUE,
	PRIMARY KEY(`TimeStamp`)
	);
