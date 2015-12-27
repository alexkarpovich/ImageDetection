################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sources/HopfieldNetwork.cpp \
../sources/Matrix.cpp \
../sources/main.cpp 

OBJS += \
./sources/HopfieldNetwork.o \
./sources/Matrix.o \
./sources/main.o 

CPP_DEPS += \
./sources/HopfieldNetwork.d \
./sources/Matrix.d \
./sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
sources/%.o: ../sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


