################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Resource/COPRGTL_TTF.cpp \
../src/Resource/CORBEL_TTF.cpp \
../src/Resource/button_off_res_gif.cpp \
../src/Resource/button_on_res_gif.cpp \
../src/Resource/contextmenu_png.cpp \
../src/Resource/textbox_res_png.cpp \
../src/Resource/win_res_png.cpp 

OBJS += \
./src/Resource/COPRGTL_TTF.o \
./src/Resource/CORBEL_TTF.o \
./src/Resource/button_off_res_gif.o \
./src/Resource/button_on_res_gif.o \
./src/Resource/contextmenu_png.o \
./src/Resource/textbox_res_png.o \
./src/Resource/win_res_png.o 

CPP_DEPS += \
./src/Resource/COPRGTL_TTF.d \
./src/Resource/CORBEL_TTF.d \
./src/Resource/button_off_res_gif.d \
./src/Resource/button_on_res_gif.d \
./src/Resource/contextmenu_png.d \
./src/Resource/textbox_res_png.d \
./src/Resource/win_res_png.d 


# Each subdirectory must supply rules for building sources it contributes
src/Resource/%.o: ../src/Resource/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


