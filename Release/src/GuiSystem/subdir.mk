################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GuiSystem/Out_Video.cpp \
../src/GuiSystem/Point.cpp \
../src/GuiSystem/SDL_collide.cpp \
../src/GuiSystem/Texture.cpp \
../src/GuiSystem/XG_Button.cpp \
../src/GuiSystem/XG_Component.cpp \
../src/GuiSystem/XG_Container.cpp \
../src/GuiSystem/XG_ContextMenu.cpp \
../src/GuiSystem/XG_FontSys.cpp \
../src/GuiSystem/XG_GuiSystem.cpp \
../src/GuiSystem/XG_Label.cpp \
../src/GuiSystem/XG_Picture.cpp \
../src/GuiSystem/XG_Screen.cpp \
../src/GuiSystem/XG_TextBox.cpp \
../src/GuiSystem/XG_Window.cpp \
../src/GuiSystem/XGraphSettings.cpp \
../src/GuiSystem/resize++.cpp 

OBJS += \
./src/GuiSystem/Out_Video.o \
./src/GuiSystem/Point.o \
./src/GuiSystem/SDL_collide.o \
./src/GuiSystem/Texture.o \
./src/GuiSystem/XG_Button.o \
./src/GuiSystem/XG_Component.o \
./src/GuiSystem/XG_Container.o \
./src/GuiSystem/XG_ContextMenu.o \
./src/GuiSystem/XG_FontSys.o \
./src/GuiSystem/XG_GuiSystem.o \
./src/GuiSystem/XG_Label.o \
./src/GuiSystem/XG_Picture.o \
./src/GuiSystem/XG_Screen.o \
./src/GuiSystem/XG_TextBox.o \
./src/GuiSystem/XG_Window.o \
./src/GuiSystem/XGraphSettings.o \
./src/GuiSystem/resize++.o 

CPP_DEPS += \
./src/GuiSystem/Out_Video.d \
./src/GuiSystem/Point.d \
./src/GuiSystem/SDL_collide.d \
./src/GuiSystem/Texture.d \
./src/GuiSystem/XG_Button.d \
./src/GuiSystem/XG_Component.d \
./src/GuiSystem/XG_Container.d \
./src/GuiSystem/XG_ContextMenu.d \
./src/GuiSystem/XG_FontSys.d \
./src/GuiSystem/XG_GuiSystem.d \
./src/GuiSystem/XG_Label.d \
./src/GuiSystem/XG_Picture.d \
./src/GuiSystem/XG_Screen.d \
./src/GuiSystem/XG_TextBox.d \
./src/GuiSystem/XG_Window.d \
./src/GuiSystem/XGraphSettings.d \
./src/GuiSystem/resize++.d 


# Each subdirectory must supply rules for building sources it contributes
src/GuiSystem/%.o: ../src/GuiSystem/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


