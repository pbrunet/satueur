#===============================================================================
#
# main Makefile for satueur kernel
#
#===============================================================================

#-------------------------------------------------------------------------------
# target, cross-compiler, flags, ...
#-------------------------------------------------------------------------------
OS_BIN=satueur.bin

TARGET=i686-elf

AS=$(TARGET)-as
CXX=$(TARGET)-g++
CC=$(TARGET)-gcc

CXXFLAGS= -std=c++11 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -DSTR_AUTOTEST=$(STR_AUTOTEST)
CFLAGS= -std=c11 -ffreestanding -O2 -Wall -Wextra
CPPFLAGS= -I kernel -I lib/libc/include
LDFLAGS= -lgcc

objects=
linker=

#-------------------------------------------------------------------------------
# includes
#-------------------------------------------------------------------------------
# tools
include scripts/utils.mk

# kernel core
include kernel/Makefile
include lib/Makefile

#-------------------------------------------------------------------------------
# compile rules
#-------------------------------------------------------------------------------
all: $(OS_BIN)

$(OS_BIN): $(objects)
	$(CXX) -T $(linker) -o $(OS_BIN) -ffreestanding -O2 \
		-nostdlib $(objects) $(LDFLAGS)
%.o: %.s
	$(AS) $^ -o $@

%.o: %.c
	$(CC) -c $^ -o $@ $(CPPFLAGS) $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $^ -o $@ $(CPPFLAGS) $(CXXFLAGS)

clean:
	find . -name *.o | xargs rm -f
	rm -f $(OS_BIN)