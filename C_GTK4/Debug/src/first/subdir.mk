################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/first/1_first_window.cpp 

CPP_DEPS += \
./src/first/1_first_window.d 

OBJS += \
./src/first/1_first_window.o 


# Each subdirectory must supply rules for building sources it contributes
src/first/%.o: ../src/first/%.cpp src/first/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/gtk-4.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/sysprof-4 -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/fribidi -I/usr/include/libxml2 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/graphene-1.0 -I/usr/lib64/graphene-1.0/include -I/usr/include/gio-unix-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src-2f-first

clean-src-2f-first:
	-$(RM) ./src/first/1_first_window.d ./src/first/1_first_window.o

.PHONY: clean-src-2f-first

