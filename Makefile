
.SUFFIXES:

include $(DEVKITARM)/gba_rules

TARGET := ShotgunKing
BUILD := build
SOURCES := .
INCLUDES := .

ARCH := -mthumb -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi

CFLAGS := -g -Wall -O2 $(ARCH)
CFLAGS += $(INCLUDE)
ASFLAGS := -g $(ARCH)
LDFLAGS := -g $(ARCH)

LIBS := -lgba
LIBDIRS := $(LIBGBA)

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT := $(CURDIR)/$(TARGET)
export VPATH := $(CURDIR)
export DEPSDIR := $(CURDIR)/$(BUILD)

CFILES := $(notdir $(wildcard *.c))
export OFILES := $(CFILES:.c=.o)

export INCLUDE := $(foreach dir,$(LIBDIRS),-I$(dir)/include)
export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: all clean
all: $(BUILD)

$(BUILD):
	@mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

clean:
	rm -rf $(BUILD) $(TARGET).elf $(TARGET).gba

else

$(OUTPUT).gba: $(OUTPUT).elf

$(OUTPUT).elf: $(OFILES) $(LIBGBA)/lib/libgba.a

-include $(DEPSDIR)/*.d

endif
