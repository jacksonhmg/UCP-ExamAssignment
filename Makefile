CC = gcc -g
CFLAGS = -Wall -pedantic -ansi
OBJ = main.o setup.o random.o color.o newSleep.o
EXEC = ant

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c setup.h random.h
	$(CC) $(CFLAGS) -c main.c

setup.o : setup.c setup.h struct.h color.h newSleep.h random.h
	$(CC) $(CFLAGS) -c setup.c

random.o : random.c random.h
	$(CC) $(CFLAGS) -c random.c

color.o : color.c color.h
	$(CC) $(CFLAGS) -c color.c
	
newSleep.o : newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

clean:
	rm -f $(EXEC) $(OBJ)