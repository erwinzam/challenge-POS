CC = gcc.exe
CFLAGS = -ansi -pedantic -Wall
LFLAGS = -Wall
OBJS = main.o input.o my_string.o card_utils.o messages.o


ejercicio2:$(OBJS) generate_ranges_cards
	$(CC) $(LFLAGS) $(OBJS) -o ejercicio2
	
main.o: main.c types.h input.h
	$(CC) $(CFLAGS) -c main.c
	
input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c
	
card_utils.o: card_utils.c card_utils.h
	$(CC) $(CFLAGS) -c card_utils.c
	
messages.o: messages.c messages.h types.h
	$(CC) $(CFLAGS) -c messages.c

test_my_string.o: test_my_string.c my_string.h
	$(CC) $(CFLAGS) -c test_my_string.c
	
test_my_string: test_my_string.o my_string.o
	$(CC) $(LFLAGS) test_my_string.o my_string.o -o test_my_string

generate_ranges_cards.o: generate_ranges_cards.c types.h card_utils.h
	$(CC) $(CFLAGS) -c generate_ranges_cards.c
	
generate_ranges_cards: generate_ranges_cards.o card_utils.o 
	$(CC) $(LFLAGS) generate_ranges_cards.o card_utils.o -o generate_ranges_cards
	./generate_ranges_cards

clean:
	rm *.exe *.o
