CC = g++
CPPFLAGS = -g -Wall -std=c++11
DEPS = Bag.h Move.h rang.h Tile.h Board.h Player.h Square.h Dictionary.h Exceptions.h ConsolePrinter.h
OBJ = Bag.o Move.o Board.o Player.o PassMove.o scrabble.o PlaceMove.o Dictionary.o ExchangeMove.o ConsolePrinter.o 

all: scrabble

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

scrabble: $(OBJ)
	$(CC) -o $@ $^ $(CPPFLAGS)

.PHONY: clean
clean: 
	rm -f *.o scrabble
