################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../arboretum/CStorage.cpp \
../arboretum/stDBMNode.cpp \
../arboretum/stDFNode.cpp \
../arboretum/stDiskPageManager.cpp \
../arboretum/stDummyNode.cpp \
../arboretum/stGHNode.cpp \
../arboretum/stListPriorityQueue.cpp \
../arboretum/stMNode.cpp \
../arboretum/stMemoryPageManager.cpp \
../arboretum/stPage.cpp \
../arboretum/stPlainDiskPageManager.cpp \
../arboretum/stResult.cpp \
../arboretum/stSlimNode.cpp \
../arboretum/stStructUtils.cpp \
../arboretum/stTreeInformation.cpp \
../arboretum/stUtil.cpp \
../arboretum/stVPNode.cpp 

OBJS += \
./arboretum/CStorage.o \
./arboretum/stDBMNode.o \
./arboretum/stDFNode.o \
./arboretum/stDiskPageManager.o \
./arboretum/stDummyNode.o \
./arboretum/stGHNode.o \
./arboretum/stListPriorityQueue.o \
./arboretum/stMNode.o \
./arboretum/stMemoryPageManager.o \
./arboretum/stPage.o \
./arboretum/stPlainDiskPageManager.o \
./arboretum/stResult.o \
./arboretum/stSlimNode.o \
./arboretum/stStructUtils.o \
./arboretum/stTreeInformation.o \
./arboretum/stUtil.o \
./arboretum/stVPNode.o 

CPP_DEPS += \
./arboretum/CStorage.d \
./arboretum/stDBMNode.d \
./arboretum/stDFNode.d \
./arboretum/stDiskPageManager.d \
./arboretum/stDummyNode.d \
./arboretum/stGHNode.d \
./arboretum/stListPriorityQueue.d \
./arboretum/stMNode.d \
./arboretum/stMemoryPageManager.d \
./arboretum/stPage.d \
./arboretum/stPlainDiskPageManager.d \
./arboretum/stResult.d \
./arboretum/stSlimNode.d \
./arboretum/stStructUtils.d \
./arboretum/stTreeInformation.d \
./arboretum/stUtil.d \
./arboretum/stVPNode.d 


# Each subdirectory must supply rules for building sources it contributes
arboretum/%.o: ../arboretum/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/alexis/PROJECTS/External/arboretum/include -I/home/alexis/PROJECTS/Eclipse/IndexCreator/sfp -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


