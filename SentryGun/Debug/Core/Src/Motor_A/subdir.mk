################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Motor_A/L298N_5AD.c \
../Core/Src/Motor_A/motor.c \
../Core/Src/Motor_A/pid_controller.c 

OBJS += \
./Core/Src/Motor_A/L298N_5AD.o \
./Core/Src/Motor_A/motor.o \
./Core/Src/Motor_A/pid_controller.o 

C_DEPS += \
./Core/Src/Motor_A/L298N_5AD.d \
./Core/Src/Motor_A/motor.d \
./Core/Src/Motor_A/pid_controller.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Motor_A/%.o: ../Core/Src/Motor_A/%.c Core/Src/Motor_A/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Core/Inc/Motor_A -I../Core/Src/Motor_A -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Motor_A

clean-Core-2f-Src-2f-Motor_A:
	-$(RM) ./Core/Src/Motor_A/L298N_5AD.d ./Core/Src/Motor_A/L298N_5AD.o ./Core/Src/Motor_A/motor.d ./Core/Src/Motor_A/motor.o ./Core/Src/Motor_A/pid_controller.d ./Core/Src/Motor_A/pid_controller.o

.PHONY: clean-Core-2f-Src-2f-Motor_A

