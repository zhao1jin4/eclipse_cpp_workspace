################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hellow/avg.c \
../hellow/hello.c \
../hellow/max.c \
../hellow/min.c 

OBJS += \
./hellow/avg.o \
./hellow/hello.o \
./hellow/max.o \
./hellow/min.o 

C_DEPS += \
./hellow/avg.d \
./hellow/hello.d \
./hellow/max.d \
./hellow/min.d 


# Each subdirectory must supply rules for building sources it contributes
hellow/%.o: ../hellow/%.c hellow/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


