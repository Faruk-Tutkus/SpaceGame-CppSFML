all : compile link run clean

compile :
	g++ -c main.cpp -Isrc/include

link :
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

run :
	./main.exe

clean :
	cls