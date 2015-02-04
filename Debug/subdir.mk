################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../display.c \
../glut_function.c \
../lighting.c \
../load_obj.c \
../mp3.c \
../normal.c \
../texture.c \
../util.c 

OBJ_SRCS += \
../teapot_0.obj 

OBJS += \
./display.o \
./glut_function.o \
./lighting.o \
./load_obj.o \
./mp3.o \
./normal.o \
./texture.o \
./util.o 

C_DEPS += \
./display.d \
./glut_function.d \
./lighting.d \
./load_obj.d \
./mp3.d \
./normal.d \
./texture.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


