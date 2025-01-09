################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/scheduler/scheduler.c 

OBJS += \
./SharedSources/scheduler/scheduler.o 

C_DEPS += \
./SharedSources/scheduler/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
SharedSources/scheduler/scheduler.o: C:/Users/wxj509/Data/MicroRepo/CubeMX/SharedSources/scheduler/scheduler.c SharedSources/scheduler/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I../../SharedSources -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SharedSources-2f-scheduler

clean-SharedSources-2f-scheduler:
	-$(RM) ./SharedSources/scheduler/scheduler.cyclo ./SharedSources/scheduler/scheduler.d ./SharedSources/scheduler/scheduler.o ./SharedSources/scheduler/scheduler.su

.PHONY: clean-SharedSources-2f-scheduler

