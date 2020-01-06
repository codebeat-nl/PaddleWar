################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
F:\Program\ Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1\TVout.cpp \
F:\Program\ Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1\TVoutPrint.cpp \
F:\Program\ Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1\video_gen.cpp 

LINK_OBJ += \
.\libraries\TVout\TVout.cpp.o \
.\libraries\TVout\TVoutPrint.cpp.o \
.\libraries\TVout\video_gen.cpp.o 

CPP_DEPS += \
.\libraries\TVout\TVout.cpp.d \
.\libraries\TVout\TVoutPrint.cpp.d \
.\libraries\TVout\video_gen.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\TVout\TVout.cpp.o: F:\Program\ Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1\TVout.cpp
	@echo 'Building file: $<'
	@echo 'Start de C++ bouw'
	"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\eightanaloginputs" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries\TVout\TVoutPrint.cpp.o: F:\Program\ Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1\TVoutPrint.cpp
	@echo 'Building file: $<'
	@echo 'Start de C++ bouw'
	"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\eightanaloginputs" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries\TVout\video_gen.cpp.o: F:\Program\ Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1\video_gen.cpp
	@echo 'Building file: $<'
	@echo 'Start de C++ bouw'
	"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino5/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\cores\arduino" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.8.2\variants\eightanaloginputs" -I"F:\Program Files\Arduino\Sloeber\arduinoPlugin\libraries\TVout\1.0.1" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


