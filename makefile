CC      = gcc
override CFLAGS += -Wall -fwrapv -lm -lpthread -Wall -m64

ifeq ($(OS),Windows_NT)
	override CFLAGS += 
	MAKE = mingw32-make
	RM = del
else
	override LDFLAGS += -pthread
	#RM = rm
endif

.PHONY : release debug clean

all: release

debug: CFLAGS += -DDEBUG -O0
debug: generateMapPreview
release: CFLAGS += -O3 
release: generateMapPreview


generateMapPreview: src/main.c cubiomes/libcubiomes.a
	$(CC) $^ $(CFLAGS) -o generateMapPreview


cubiomes/libcubiomes.a:
	cd cubiomes && $(MAKE)

clean:
	$(RM) generateMapPreview
	cd cubiomes && $(MAKE) clean

