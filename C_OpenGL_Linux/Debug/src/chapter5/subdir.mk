################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/chapter5/Ambient.cpp \
../src/chapter5/SpotLight.cpp \
../src/chapter5/Triangle.cpp \
../src/chapter5/ccube.cpp 

OBJS += \
./src/chapter5/Ambient.o \
./src/chapter5/SpotLight.o \
./src/chapter5/Triangle.o \
./src/chapter5/ccube.o 

CPP_DEPS += \
./src/chapter5/Ambient.d \
./src/chapter5/SpotLight.d \
./src/chapter5/Triangle.d \
./src/chapter5/ccube.d 


# Each subdirectory must supply rules for building sources it contributes
src/chapter5/%.o: ../src/chapter5/%.cpp src/chapter5/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


