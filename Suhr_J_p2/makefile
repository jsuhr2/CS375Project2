P=program2
CFLAGS= -Wall -Wextra -DDEBUG -g -pedantic -std=c++14

all: $(P)

$(P).o: $(P).cpp
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o

$(P): $(P).o
	g++ $(CFLAGS) $(P).o -o $(P)

run: all
	./$(P) input.txt output.txt

clean:
	rm $(P).o
	rm $(P)
