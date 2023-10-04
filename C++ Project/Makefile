MODE =

.PHONY: compilation_commands

main.exe: main.o
	g++ $(MODE) main.o -o main.exe

main.o: main.cpp grafoT.h
	g++ $(MODE) -c main.cpp -o main.o

.PHONY: custom_commands

clean_all:
	rm *.o *.exe

clean:
	rm *.o
