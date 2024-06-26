CC = g++
FLAGS = -g
OUTFILE = main.o
CFILES = src/main.cpp src/rules.cpp src/game.cpp

make:
	make build
	make run
build: 	
	g++ -o $(OUTFILE) $(FLAGS) $(CFILES)
run:
	./$(OUTFILE)
clean:
	rm $(OUTFILE)
