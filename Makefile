XPACK=/usr/local/CrossPack-AVR/bin

AVR=atmega8

CXX=g++
CC=gcc
AS=as

EXEC=$(notdir $(CURDIR))


LIBS=-I/usr/local/Cellar/boost/1.59.0/include

CXXFLAGS=-Wall -Wextra -O2 -ftrapv -Wundef -fverbose-asm -std=c++11 $(LIBS)
CFLAGS=-Wall -Wextra -O2 -ftrapv -Wundef -fverbose-asm -std=c99
ASFLAGS=

CPP_FILES := $(shell find src -name '*.cpp')
C_FILES := $(shell find src -name '*.c')
AS_FILES := $(shell find src -name '*.as')
SOURCES := $(CPP_FILES:.cpp=.o) $(C_FILES.cpp=.o) $(AS_FILES.cpp=.o)
OBJS := $(foreach file, $(SOURCES), $(file))

all: $(OBJS)
	@echo "[LD] ./$(EXEC)"
	@$(CXX) $(OBJS) -o $(EXEC)

%o: %cpp
	@echo "[CXX] $@"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

%o: %c
	@echo "[C] $@"
	@$(C) $(CFLAGS) -o "$@" -c "$<"

%o: %as
	@echo "[AS] $@"
	@$(AS) $(ASFLAGS) -o "$@" -c "$<"

clean:
	rm -f $(EXEC) $(OBJS)

print-%:
	@echo '$*=$($*)'

-include $(OBJS:.o=.d)

compile:
	./$(EXEC) | $(XPACK)/avr-as -mmcu=$(AVR) -D --gdwarf-2 -o avrprog.elf

debug:
	$(XPACK)/simulavr -d $(AVR) avrprog.elf 






