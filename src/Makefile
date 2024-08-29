CFLAGS = -std=c99 -O2 -Wall -Wextra -Wshadow -Wvla -Wpointer-arith -Walloca -Wduplicated-cond -Wtrampolines -Wlarger-than=1048576 -Wframe-larger-than=32768 -Wdouble-promotion -Werror=return-type -Wno-unknown-warning-option
LFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OBJS = $(patsubst %.c,build/%.o,$(wildcard *.c))
TARGET = ../tankzors

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $@
	strip -s $(TARGET)

build/%.o: %.c %.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: all clean
