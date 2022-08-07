PROJECT = nicedice

F_CPU = 1200000
MCU = attiny13
MCU_AVRDUDE = t13

FILES = main.c

PROGRAMMER = usbasp
PORT = usb

# Common section

# Directories
BUILD_DIR = build
SRC_DIR = src

# Compilers and other
CC := avr-gcc
CXX := avr-g++
OBJCOPY := avr-objcopy
AVRSIZE := avr-size
AVRDUDE := avrdude

# File lists
OBJS := $(FILES:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Compiler setings
INC_FLAG := $(addprefix -I,$(INC_DIRS)) -I$(SRC_DIR) -Ilib
CPPFLAGS := $(INC_FLAG) -MMD -MP -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS := -mmcu=$(MCU)

#Targets

.PHONY: clean compile upload

compile: $(PROJECT).hex

upload: $(PROJECT).hex
	$(AVRDUDE) -v -p$(MCU) -c$(PROGRAMMER) -P$(PORT) -Uflash:w:$(PROJECT).hex:i

$(PROJECT).hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJECT).elf $(PROJECT).hex

$(BUILD_DIR)/$(PROJECT).elf: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	$(AVRSIZE) -C --mcu=$(MCU) $@

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	@if not exist $(BUILD_DIR)\\NUL mkdir $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR)\\NUL mkdir $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	del /q $(BUILD_DIR)\*
	del $(PROJECT).hex

-include $(DEPS)