################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../simple_file_parser/simple_file_parser.cc 

CC_DEPS += \
./simple_file_parser/simple_file_parser.d 

OBJS += \
./simple_file_parser/simple_file_parser.o 


# Each subdirectory must supply rules for building sources it contributes
simple_file_parser/%.o: ../simple_file_parser/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/alexis/PROJECTS/External/arboretum/include -I/home/alexis/PROJECTS/External/simple_file_parser -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


