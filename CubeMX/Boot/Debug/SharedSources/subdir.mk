################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/circularBuffer.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/flash.c \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/scheduler.c 

OBJS += \
./SharedSources/circularBuffer.o \
./SharedSources/flash.o \
./SharedSources/scheduler.o 

C_DEPS += \
./SharedSources/circularBuffer.d \
./SharedSources/flash.d \
./SharedSources/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
SharedSources/circularBuffer.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/circularBuffer.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/flash.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/flash.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
SharedSources/scheduler.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/scheduler.c SharedSources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SharedSources

clean-SharedSources:
	-$(RM) ./SharedSources/circularBuffer.cyclo ./SharedSources/circularBuffer.d ./SharedSources/circularBuffer.o ./SharedSources/circularBuffer.su ./SharedSources/flash.cyclo ./SharedSources/flash.d ./SharedSources/flash.o ./SharedSources/flash.su ./SharedSources/scheduler.cyclo ./SharedSources/scheduler.d ./SharedSources/scheduler.o ./SharedSources/scheduler.su

.PHONY: clean-SharedSources

