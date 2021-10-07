################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/chapter2/BOUNCE.cpp \
../src/chapter2/GLRect.cpp \
../src/chapter2/Simple.cpp 

OBJS += \
./src/chapter2/BOUNCE.o \
./src/chapter2/GLRect.o \
./src/chapter2/Simple.o 

CPP_DEPS += \
./src/chapter2/BOUNCE.d \
./src/chapter2/GLRect.d \
./src/chapter2/Simple.d 


# Each subdirectory must supply rules for building sources it contributes
src/chapter2/%.o: ../src/chapter2/%.cpp src/chapter2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


