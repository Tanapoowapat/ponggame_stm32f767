################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/ILI9341/ILI9341_GFX.c \
../Core/Inc/ILI9341/ILI9341_STM32_Driver.c \
../Core/Inc/ILI9341/ILI9341_Touchscreen.c 

OBJS += \
./Core/Inc/ILI9341/ILI9341_GFX.o \
./Core/Inc/ILI9341/ILI9341_STM32_Driver.o \
./Core/Inc/ILI9341/ILI9341_Touchscreen.o 

C_DEPS += \
./Core/Inc/ILI9341/ILI9341_GFX.d \
./Core/Inc/ILI9341/ILI9341_STM32_Driver.d \
./Core/Inc/ILI9341/ILI9341_Touchscreen.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/ILI9341/%.o Core/Inc/ILI9341/%.su: ../Core/Inc/ILI9341/%.c Core/Inc/ILI9341/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Komet/Downloads/LCDT/Core/Inc/ILI9341" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-ILI9341

clean-Core-2f-Inc-2f-ILI9341:
	-$(RM) ./Core/Inc/ILI9341/ILI9341_GFX.d ./Core/Inc/ILI9341/ILI9341_GFX.o ./Core/Inc/ILI9341/ILI9341_GFX.su ./Core/Inc/ILI9341/ILI9341_STM32_Driver.d ./Core/Inc/ILI9341/ILI9341_STM32_Driver.o ./Core/Inc/ILI9341/ILI9341_STM32_Driver.su ./Core/Inc/ILI9341/ILI9341_Touchscreen.d ./Core/Inc/ILI9341/ILI9341_Touchscreen.o ./Core/Inc/ILI9341/ILI9341_Touchscreen.su

.PHONY: clean-Core-2f-Inc-2f-ILI9341

