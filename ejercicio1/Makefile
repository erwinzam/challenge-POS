CC = gcc.exe
CFLAGS = -ansi -pedantic -Wall
LFLAGS = -Wall
OBJS = main.o input.o my_string.o vector.o


ejercicio1:$(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ejercicio1 
	
main.o: main.c types.h input.h
	$(CC) $(CFLAGS) -c main.c
	
input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

my_string.o: my_string.c my_string.h types.h
	$(CC) $(CFLAGS) -c my_string.c
	
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c
	
test_my_string: my_string.o vector.o test_my_string.c
	$(CC) $(LFLAGS) test_my_string.c my_string.o vector.o -o test_my_string
	./test_my_string
	
	
clean:
	rm *.exe *.o
