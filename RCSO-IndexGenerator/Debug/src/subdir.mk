################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CreateIndexAPP.cpp 

OBJS += \
./src/CreateIndexAPP.o 

CPP_DEPS += \
./src/CreateIndexAPP.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/alexis/PROJECTS/Eclipse/IndexCreator/include -I/home/alexis/PROJECTS/Eclipse/IndexCreator/src -I/home/alexis/PROJECTS/External/arboretumLast/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


