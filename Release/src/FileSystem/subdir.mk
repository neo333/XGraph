################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FileSystem/Cache.cpp \
../src/FileSystem/De_Encoder.cpp \
../src/FileSystem/HardDisk.cpp \
../src/FileSystem/Manager_Caches.cpp 

OBJS += \
./src/FileSystem/Cache.o \
./src/FileSystem/De_Encoder.o \
./src/FileSystem/HardDisk.o \
./src/FileSystem/Manager_Caches.o 

CPP_DEPS += \
./src/FileSystem/Cache.d \
./src/FileSystem/De_Encoder.d \
./src/FileSystem/HardDisk.d \
./src/FileSystem/Manager_Caches.d 


# Each subdirectory must supply rules for building sources it contributes
src/FileSystem/%.o: ../src/FileSystem/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


