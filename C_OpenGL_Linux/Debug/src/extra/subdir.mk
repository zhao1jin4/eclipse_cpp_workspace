################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/extra/ImageLoad____.cpp 

C_SRCS += \
../src/extra/LoadTGA.c 

OBJS += \
./src/extra/ImageLoad____.o \
./src/extra/LoadTGA.o 

CPP_DEPS += \
./src/extra/ImageLoad____.d 

C_DEPS += \
./src/extra/LoadTGA.d 


# Each subdirectory must supply rules for building sources it contributes
src/extra/%.o: ../src/extra/%.cpp src/extra/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/extra/%.o: ../src/extra/%.c src/extra/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


