
.SUFFIXES:

include $(DEVKITARM)/gba_rules

TARGET := ShotgunKing
BUILD := build
SOURCES := .
DATA :=
INCLUDES := .

ARCH := -mthumb -mthumb-interwork -mcpu=arm7tdmi

CFLAGS := -g -Wall -O2 $(ARCH)
CXXFLAGS := $(CFLAGS)
ASFLAGS := -g $(ARCH)

LDFLAGS = -g $(ARCH)

LIBS := -lgba
LIBDIRS := $(LIBGBA)
