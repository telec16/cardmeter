################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../charset.c \
../LTC2402.c \
../LTC6911.c \
../main.c \
../NOKIA3310.c \
../setup.c \
../utils.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
charset.o \
LTC2402.o \
LTC6911.o \
main.o \
NOKIA3310.o \
setup.o \
utils.o

OBJS_AS_ARGS +=  \
charset.o \
LTC2402.o \
LTC6911.o \
main.o \
NOKIA3310.o \
setup.o \
utils.o

C_DEPS +=  \
charset.d \
LTC2402.d \
LTC6911.d \
main.d \
NOKIA3310.d \
setup.d \
utils.d

C_DEPS_AS_ARGS +=  \
charset.d \
LTC2402.d \
LTC6911.d \
main.d \
NOKIA3310.d \
setup.d \
utils.d

OUTPUT_FILE_PATH +=CardMeter.elf

OUTPUT_FILE_PATH_AS_ARGS +=CardMeter.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Programmes\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Programmes\AtmelStudio\7.0\Packs\atmel\ATtiny_DFP\1.3.147\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=attiny1616 -B "D:\Programmes\AtmelStudio\7.0\Packs\atmel\ATtiny_DFP\1.3.147\gcc\dev\attiny1616" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\Programmes\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="CardMeter.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=attiny1616 -B "D:\Programmes\AtmelStudio\7.0\Packs\atmel\ATtiny_DFP\1.3.147\gcc\dev\attiny1616"  
	@echo Finished building target: $@
	"D:\Programmes\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "CardMeter.elf" "CardMeter.hex"
	"D:\Programmes\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "CardMeter.elf" "CardMeter.eep" || exit 0
	"D:\Programmes\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "CardMeter.elf" > "CardMeter.lss"
	"D:\Programmes\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "CardMeter.elf" "CardMeter.srec"
	"D:\Programmes\AtmelStudio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "CardMeter.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "CardMeter.elf" "CardMeter.a" "CardMeter.hex" "CardMeter.lss" "CardMeter.eep" "CardMeter.map" "CardMeter.srec" "CardMeter.usersignatures"
	