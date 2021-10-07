################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/chapter6/Bitmaps.cpp \
../src/chapter6/MyTest.cpp 

C_SRCS += \
../src/chapter6/texsub.c 

OBJS += \
./src/chapter6/Bitmaps.o \
./src/chapter6/MyTest.o \
./src/chapter6/texsub.o 

CPP_DEPS += \
./src/chapter6/Bitmaps.d \
./src/chapter6/MyTest.d 

C_DEPS += \
./src/chapter6/texsub.d 


# Each subdirectory must supply rules for building sources it contributes
src/chapter6/%.o: ../src/chapter6/%.cpp src/chapter6/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/chapter6/%.o: ../src/chapter6/%.c src/chapter6/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


