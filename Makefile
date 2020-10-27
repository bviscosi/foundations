CC = g++
CFLAGS = -c -g -Og -std=c++17
OBJ = main.o character.o alphabet.o string.o DFA.o Corpus.o
DEPS =
LIBS =
EXE = run

all:  $(OBJ)

	$(CC)  $(OBJ) -o  $(EXE)  $(LIBS)

%.o: %.cpp  $(DEPS)

	$(CC)  $(CFLAGS) -o  $@ $<

clean:

	rm $(OBJ) $(EXE)
