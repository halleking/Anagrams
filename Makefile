

TARGET = alarm_signaler
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall -std=c89


all: alarm_signaler

alarm_signaler.o: alarm_signaler.c
	$(CC) $(CFLAGS) -c $< -o $@

alarm_signaler: alarm_signaler.o
	$(CC) $(OBJECTS) -Wall $(LIBS) $< -o $@

clean:
	-rm -f *.o
	-rm -f alarm_signaler
