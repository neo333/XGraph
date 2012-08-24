################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/InputSystem/Gestore_Input.cpp \
../src/InputSystem/Mouse.cpp \
../src/InputSystem/Tastiera.cpp 

OBJS += \
./src/InputSystem/Gestore_Input.o \
./src/InputSystem/Mouse.o \
./src/InputSystem/Tastiera.o 

CPP_DEPS += \
./src/InputSystem/Gestore_Input.d \
./src/InputSystem/Mouse.d \
./src/InputSystem/Tastiera.d 


# Each subdirectory must supply rules for building sources it contributes
src/InputSystem/%.o: ../src/InputSystem/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


