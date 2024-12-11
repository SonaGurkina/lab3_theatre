CC = gcc
CFLAGS = -Wall -g

all: lab3_main
	./lab3_main

lab3_main: lab3_main.o lab3_db_func.o
	$(CC) $(CFLAGS) lab3_main.o lab3_db_func.o -o lab3_main

%.o: %.c Perfomance.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f lab3_main *.o
