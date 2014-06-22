TARGET=i686-elf
OS_BIN=myos.bin

AS=$(TARGET)-as
CXX=$(TARGET)-g++

CXXFLAGS= -std=c++11 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LDFLAGS=-lgcc

all: $(OS_BIN)

$(OS_BIN): obj/boot.o obj/kernel.o linker/linker.ld
	$(CXX) -T linker/linker.ld -o $(OS_BIN) -ffreestanding -O2 -nostdlib obj/boot.o obj/kernel.o $(LDFLAGS)

obj/boot.o: src/boot.s
	$(AS) $^ -o obj/boot.o

obj/kernel.o: src/kernel.cpp
	$(CXX) -c $^ -o obj/kernel.o $(CXXFLAGS)

clean:
	rm obj/*

.PHONY: clean
