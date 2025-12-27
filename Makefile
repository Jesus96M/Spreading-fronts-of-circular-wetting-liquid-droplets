TARGET = ejecutableContinuo
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -O2

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)
	-rm -r Salida_*
	-rm -r Correlacion_*
	-rm -r Fourier_*
	-rm -r Frontera*
	-rm -r Configuracion*
	-rm -r Conectados*
	-rm -r descripcion*
	-rm -r Num*
