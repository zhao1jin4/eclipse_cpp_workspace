################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/chapter4/Perspect.cpp \
../src/chapter4/Solar.cpp 

OBJS += \
./src/chapter4/Perspect.o \
./src/chapter4/Solar.o 

CPP_DEPS += \
./src/chapter4/Perspect.d \
./src/chapter4/Solar.d 


# Each subdirectory must supply rules for building sources it contributes
src/chapter4/%.o: ../src/chapter4/%.cpp src/chapter4/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


