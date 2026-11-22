
TARGET := ShotgunKing
BUILD := build

SOURCES := .
INCLUDES := .

ARCH := -mthumb -mthumb-interwork -mcpu=arm7tdmi

CFLAGS := -g -Wall -O2 $(ARCH)
LDFLAGS := -g $(ARCH)

LIBS := -ltonc
LIBDIRS := $(LIBTONC)

include $(DEVKITARM)/gba_rules
