CC      = gcc
override CFLAGS += -Wall -fwrapv -lm -lpthread -Wall -m64 -std=c99

ifeq ($(OS),Windows_NT)
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
	cd cubiomes && $(MAKE) CFLAGS+="-m64"

clean:
	$(RM) generateMapPreview
	cd cubiomes && $(MAKE) clean

