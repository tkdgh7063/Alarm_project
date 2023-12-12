OBJECTS = main.o illumination/light.o KEYPAD/keypad.o
SRCS = main.c illumination/light.c KEYPAD/keypad.c
CC = gcc
CFLAGS = -lwiringPi -lpthread 
TARGET = result

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(CFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(TARGET)

main.o: main.c illumination/light.h KEYPAD/keypad.h
	$(CC) -c $< -o $@ -Iillumination -IKEYPAD $(CFLAGS)

illumination/light.o: illumination/light.c illumination/light.h
	$(CC) -c $< -o $@ -Iillumination $(CFLAGS)

KEYPAD/keypad.o: KEYPAD/keypad.c KEYPAD/keypad.h
	$(CC) -c $< -o $@ -IKEYPAD $(CFLAGS)