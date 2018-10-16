P=program2
CFLAGS= -Wall -Wextra -DDEBUG -g -pedantic -std=c++14

all: $(P)

$(P).o: $(P).cpp
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o

$(P): $(P).o
	g++ $(CFLAGS) $(P).o -o submission

run: all
	./submission input.txt output.txt

clean:
	rm $(P).o
	rm submission
