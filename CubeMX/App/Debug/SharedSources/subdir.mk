################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/circularBuffer.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/cmdhandler.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/cmdqueue.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/crc.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/eeprom.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/flash.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/fwUpgrade.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/led.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/scheduler.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/serial.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/systemRestart.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/template.c 

OBJS += \
./SharedSources/circularBuffer.o \
./SharedSources/cmdhandler.o \
./SharedSources/cmdqueue.o \
./SharedSources/crc.o \
./SharedSources/eeprom.o \
./SharedSources/flash.o \
./SharedSources/fwUpgrade.o \
./SharedSources/led.o \
./SharedSources/scheduler.o \
./SharedSources/serial.o \
./SharedSources/systemRestart.o \
./SharedSources/template.o 

C_DEPS += \
./SharedSources/circularBuffer.d \
./SharedSources/cmdhandler.d \
./SharedSources/cmdqueue.d \
./SharedSources/crc.d \
./SharedSources/eeprom.d \
./SharedSources/flash.d \
./SharedSources/fwUpgrade.d \
./SharedSources/led.d \
./SharedSources/scheduler.d \
./SharedSources/serial.d \
./SharedSources/systemRestart.d \
./SharedSources/template.d 


# Each subdirectory must supply rules for building sources it contributes
SharedSources/circularBuffer.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/circularBuffer.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/cmdhandler.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/cmdhandler.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/cmdqueue.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/cmdqueue.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/crc.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/crc.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/eeprom.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/eeprom.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/flash.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/flash.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/fwUpgrade.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/fwUpgrade.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/led.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/led.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/scheduler.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/scheduler.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/serial.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/serial.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/systemRestart.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/systemRestart.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/template.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/template.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSER_VECT_TAB_ADDRESS -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SharedSources

clean-SharedSources:
	-$(RM) ./SharedSources/circularBuffer.cyclo ./SharedSources/circularBuffer.d ./SharedSources/circularBuffer.o ./SharedSources/circularBuffer.su ./SharedSources/cmdhandler.cyclo ./SharedSources/cmdhandler.d ./SharedSources/cmdhandler.o ./SharedSources/cmdhandler.su ./SharedSources/cmdqueue.cyclo ./SharedSources/cmdqueue.d ./SharedSources/cmdqueue.o ./SharedSources/cmdqueue.su ./SharedSources/crc.cyclo ./SharedSources/crc.d ./SharedSources/crc.o ./SharedSources/crc.su ./SharedSources/eeprom.cyclo ./SharedSources/eeprom.d ./SharedSources/eeprom.o ./SharedSources/eeprom.su ./SharedSources/flash.cyclo ./SharedSources/flash.d ./SharedSources/flash.o ./SharedSources/flash.su ./SharedSources/fwUpgrade.cyclo ./SharedSources/fwUpgrade.d ./SharedSources/fwUpgrade.o ./SharedSources/fwUpgrade.su ./SharedSources/led.cyclo ./SharedSources/led.d ./SharedSources/led.o ./SharedSources/led.su ./SharedSources/scheduler.cyclo ./SharedSources/scheduler.d ./SharedSources/scheduler.o ./SharedSources/scheduler.su ./SharedSources/serial.cyclo ./SharedSources/serial.d ./SharedSources/serial.o ./SharedSources/serial.su ./SharedSources/systemRestart.cyclo ./SharedSources/systemRestart.d ./SharedSources/systemRestart.o ./SharedSources/systemRestart.su ./SharedSources/template.cyclo ./SharedSources/template.d ./SharedSources/template.o ./SharedSources/template.su

.PHONY: clean-SharedSources

