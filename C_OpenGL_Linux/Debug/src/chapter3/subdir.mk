################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/chapter3/Cone.cpp \
../src/chapter3/LINESW.cpp \
../src/chapter3/LSTIPPLE.cpp \
../src/chapter3/LStrips.cpp \
../src/chapter3/Lines.cpp \
../src/chapter3/POINTS.cpp \
../src/chapter3/Pointsz.cpp \
../src/chapter3/Pstipple.cpp \
../src/chapter3/Star.cpp \
../src/chapter3/scissor.cpp \
../src/chapter3/stencil.cpp 

OBJS += \
./src/chapter3/Cone.o \
./src/chapter3/LINESW.o \
./src/chapter3/LSTIPPLE.o \
./src/chapter3/LStrips.o \
./src/chapter3/Lines.o \
./src/chapter3/POINTS.o \
./src/chapter3/Pointsz.o \
./src/chapter3/Pstipple.o \
./src/chapter3/Star.o \
./src/chapter3/scissor.o \
./src/chapter3/stencil.o 

CPP_DEPS += \
./src/chapter3/Cone.d \
./src/chapter3/LINESW.d \
./src/chapter3/LSTIPPLE.d \
./src/chapter3/LStrips.d \
./src/chapter3/Lines.d \
./src/chapter3/POINTS.d \
./src/chapter3/Pointsz.d \
./src/chapter3/Pstipple.d \
./src/chapter3/Star.d \
./src/chapter3/scissor.d \
./src/chapter3/stencil.d 


# Each subdirectory must supply rules for building sources it contributes
src/chapter3/%.o: ../src/chapter3/%.cpp src/chapter3/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


