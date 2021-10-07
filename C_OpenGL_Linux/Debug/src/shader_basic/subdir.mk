################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/shader_basic/FirstShader.cpp 

OBJS += \
./src/shader_basic/FirstShader.o 

CPP_DEPS += \
./src/shader_basic/FirstShader.d 


# Each subdirectory must supply rules for building sources it contributes
src/shader_basic/%.o: ../src/shader_basic/%.cpp src/shader_basic/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


