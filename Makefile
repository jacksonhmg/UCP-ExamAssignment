CC = gcc -g
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o setup.o random.o
EXEC = ant

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c setup.h random.h
	$(CC) $(CFLAGS) -c main.c

setup.o : setup.c setup.h struct.h
	$(CC) $(CFLAGS) -c setup.c

random.o : random.c random.h
	$(CC) $(CFLAGS) -c random.c

clean:
	rm -f $(EXEC) $(OBJ)