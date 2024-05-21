CC = gcc
CFLAGS = -fPIC -shared -o
TARGET = libhermes.so

all: $(TARGET)

$(TARGET): hermes.c
	$(CC) $(CFLAGS) ../$(TARGET) hermes.c 

clean:
	rm -f ../$(TARGET)

