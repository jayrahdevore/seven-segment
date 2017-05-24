# Generic makefile for the AVR ATMega328
# Created by legowave440 on 5/24/17

# microcontroller target
TARGET_MCU = atmega328p

# programmer
PROGRAMMER = buspirate

# programmer port
PORT = /dev/ttyUSB0

# compiler flage
CFLAGS =-std=c99 -Wall -Os

# target executable
TARGET_FILE = main

# build the executable
all: $(TARGET_FILE)

$(TARGET_FILE): $(TARGET_FILE).c
	avr-gcc $(CFLAGS) -mmcu=$(TARGET_MCU) -o $(TARGET_FILE) $(TARGET_FILE).c

upload:
	avr-gcc $(CFLAGS) -mmcu=$(TARGET_MCU) -o $(TARGET_FILE) $(TARGET_FILE).c
	avrdude -p $(TARGET_MCU) -P $(PORT) -c $(PROGRAMMER) $(TARGET_FILE) -U flash:w:$(TARGET_FILE)

clean:
	$(RM) $(TARGET_FILE)
