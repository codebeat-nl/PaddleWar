################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\DisplayFoundation.cpp \
..\sloeber.ino.cpp 

LINK_OBJ += \
.\DisplayFoundation.cpp.o \
.\sloeber.ino.cpp.o 

CPP_DEPS += \
.\DisplayFoundation.cpp.d \
.\sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
DisplayFoundation.cpp.o: ..\DisplayFoundation.cpp
	@echo 'Building file: $<'
	@echo 'Start de C++ bouw'
	"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\eightanaloginputs" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

sloeber.ino.cpp.o: ..\sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Start de C++ bouw'
	"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\eightanaloginputs" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"

	@echo 'Finished building: $<'
	@echo ' '


