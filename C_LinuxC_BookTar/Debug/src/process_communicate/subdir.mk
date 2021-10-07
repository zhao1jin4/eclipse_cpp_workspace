################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_UPPER_SRCS += \
../src/process_communicate/message_queue.C \
../src/process_communicate/share_memory.C 

C_UPPER_DEPS += \
./src/process_communicate/message_queue.d \
./src/process_communicate/share_memory.d 

OBJS += \
./src/process_communicate/message_queue.o \
./src/process_communicate/share_memory.o 


# Each subdirectory must supply rules for building sources it contributes
src/process_communicate/%.o: ../src/process_communicate/%.C src/process_communicate/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


