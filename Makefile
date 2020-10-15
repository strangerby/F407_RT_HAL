##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.7.1] date: [Thu Sep 10 16:17:20 CST 2020] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = $(shell basename $(shell pwd))


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

#Output path
OUTPUT_DIR = Output


######################################
# source
######################################
# C sources
C_SOURCES =  \
$(wildcard Applications/*.c)	\
$(wildcard Libraries/STM32F4xx_HAL_Driver/Src/*.c)\
$(wildcard Libraries/STM32F4xx_HAL_Driver/Src/Legacy/*.c)\
$(wildcard RT-Thread/components/finsh/*.c)\
$(wildcard RT-Thread/bsp/*.c)\
$(wildcard RT-Thread/src/*.c)\
$(wildcard RT-Thread/libcpu/arm/cortex-m4/*.c)\
$(wildcard derivers/uart1/*c)


# ASM sources
ASM_SOURCES =  \
$(wildcard Applications/*.s)	\
$(wildcard Libraries/STM32F4xx_HAL_Driver/Src/*.s)\
$(wildcard Libraries/STM32F4xx_HAL_Driver/Src/Legacy/*.s)\
$(wildcard RT-Thread/components/finsh/*.s)\
$(wildcard RT-Thread/bsp/*.s)\
$(wildcard RT-Thread/src/*.s)\
$(wildcard RT-Thread/libcpu/arm/cortex-m4/*.s)\
startup_stm32f407xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=soft
#FLOAT-ABI = -mfloat-abi=hard
#FLOAT-ABI = -mfloat-abi=softfp

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F407xx \
-D__VFP_FP__

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-IInc \
-ILibraries/STM32F4xx_HAL_Driver/Inc/Legacy \
-ILibraries/STM32F4xx_HAL_Driver/Inc \
-ILibraries/CMSIS/Device/ST/STM32F4xx/Include \
-IRT-Thread/include \
-ILibraries/CMSIS/Include \
-IApplications/include	\
-IDrivers/include \
-IRT-Thread/components/finsh \
-ILibraries/CMSIS/DSP/Include \
-Iderivers/uart1\
-IRT-Thread/bsp


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -fdiagnostics-color=auto
ASFLAGS += -Wa,-mimplicit-it=thumb

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections  -fdiagnostics-color=auto

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F407VETx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = Libraries/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a
LDFLAGS = $(MCU) -u_printf_float -u_sprintf_float -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(OUTPUT_DIR)/$(TARGET).hex $(OUTPUT_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(OUTPUT_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(OUTPUT_DIR)
	$(HEX) $< $@
	
$(OUTPUT_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(OUTPUT_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

$(OUTPUT_DIR):
	mkdir $@		


.PHONY : clean cleanall

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
cleanall :
	-rm -rf $(BUILD_DIR) $(OUTPUT_DIR)
 
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***