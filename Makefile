TOP_SRC_DIR=.

TARGET=i686-elf
OS_BIN=satueur.bin

AS=$(TARGET)-as
CXX=$(TARGET)-g++
CC=$(TARGET)-gcc

CXXFLAGS= -std=c++11 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
CFLAGS= -std=c11 -ffreestanding -O2 -Wall -Wextra
CPPFLAGS= -I$(TOP_SRC_DIR)/include
LDFLAGS= -lgcc

CPP_FILES=$(wildcard src/*.cpp)
OBJS=$(subst src/,obj/,$(subst .cpp,.o,$(CPP_FILES)))

AS_FILES=$(wildcard src/*.s)
OBJS+=$(subst src/,obj/,$(subst .s,.o,$(AS_FILES)))

C_FILES=$(wildcard src/*.c)
OBJS+=$(subst src/,obj/,$(subst .c,.o,$(C_FILES)))

all: $(OS_BIN)

$(OS_BIN): $(OBJS) linker/linker.ld
	$(CXX) -T linker/linker.ld -o $(OS_BIN) -ffreestanding -O2 \
		-nostdlib $(OBJS) $(LDFLAGS)

obj/%.o: src/%.s
	$(AS) $^ -o $@

obj/%.o: src/%.cpp
	$(CXX) -c $^ -o $@ $(CPPFLAGS) $(CXXFLAGS)

obj/%.o: src/%.c
	$(CC) -c $^ -o $@ $(CPPFLAGS) $(CFLAGS)

clean-doc:
	rm -f *.pdf

clean: clean-doc
	rm -f obj/* || true
	rm -f $(OS_BIN)

.PHONY: clean
