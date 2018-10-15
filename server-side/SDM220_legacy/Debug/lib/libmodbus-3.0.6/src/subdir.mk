################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/libmodbus-3.0.6/src/modbus-data.c \
../lib/libmodbus-3.0.6/src/modbus-rtu.c \
../lib/libmodbus-3.0.6/src/modbus-tcp.c \
../lib/libmodbus-3.0.6/src/modbus.c 

OBJS += \
./lib/libmodbus-3.0.6/src/modbus-data.o \
./lib/libmodbus-3.0.6/src/modbus-rtu.o \
./lib/libmodbus-3.0.6/src/modbus-tcp.o \
./lib/libmodbus-3.0.6/src/modbus.o 

C_DEPS += \
./lib/libmodbus-3.0.6/src/modbus-data.d \
./lib/libmodbus-3.0.6/src/modbus-rtu.d \
./lib/libmodbus-3.0.6/src/modbus-tcp.d \
./lib/libmodbus-3.0.6/src/modbus.d 


# Each subdirectory must supply rules for building sources it contributes
lib/libmodbus-3.0.6/src/%.o: ../lib/libmodbus-3.0.6/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -Wall -c -fmessage-length=0 -fpermissive -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


