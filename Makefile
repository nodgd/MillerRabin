GCCO = g++ -Wall -O2

default: main.exe

run: default
	main.exe
clean:
	rm *.exe *.o

main.exe: main.o uint1024.o
	$(GCCO) main.o uint1024.o -o main.exe
main.o: main.cpp uint1024.h
	$(GCCO) main.cpp -o main.o -c
uint1024.o: uint1024.cpp uint1024.h
	$(GCCO) uint1024.cpp -o uint1024.o -c
