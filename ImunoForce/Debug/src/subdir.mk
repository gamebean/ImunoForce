################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AllegroDef.c \
../src/ImunoEngine.c \
../src/ImunoForce.c 

OBJS += \
./src/AllegroDef.o \
./src/ImunoEngine.o \
./src/ImunoForce.o 

C_DEPS += \
./src/AllegroDef.d \
./src/ImunoEngine.d \
./src/ImunoForce.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


