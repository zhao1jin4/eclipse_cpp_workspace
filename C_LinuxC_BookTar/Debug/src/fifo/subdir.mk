################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_UPPER_SRCS += \
../src/fifo/fifo_read.C \
../src/fifo/fifo_write.C 

C_UPPER_DEPS += \
./src/fifo/fifo_read.d \
./src/fifo/fifo_write.d 

OBJS += \
./src/fifo/fifo_read.o \
./src/fifo/fifo_write.o 


# Each subdirectory must supply rules for building sources it contributes
src/fifo/%.o: ../src/fifo/%.C src/fifo/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


