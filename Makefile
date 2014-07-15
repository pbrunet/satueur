TOP_SRC_DIR=.

TARGET=i686-elf
OS_BIN=myos.bin

AS=$(TARGET)-as
CXX=$(TARGET)-g++

CXXFLAGS= -std=c++11 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
CPPFLAGS= -I$(TOP_SRC_DIR)/include
LDFLAGS=-lgcc

CPP_FILES=$(wildcard src/*.cpp)
OBJS=$(subst src/,obj/,$(subst .cpp,.o,$(CPP_FILES)))

AS_FILES=$(wildcard src/*.s)
OBJS+=$(subst src/,obj/,$(subst .s,.o,$(AS_FILES)))

all: $(OS_BIN)

$(OS_BIN): $(OBJS) linker/linker.ld
	$(CXX) -T linker/linker.ld -o $(OS_BIN) -ffreestanding -O2 -nostdlib $(OBJS) $(LDFLAGS)

obj/%.o: src/%.s
	$(AS) $^ -o $@

obj/%.o: src/%.cpp
	$(CXX) -c $^ -o $@ $(CPPFLAGS) $(CXXFLAGS)

clean:
	rm -f obj/* || true
	rm $(OS_BIN)

.PHONY: clean
