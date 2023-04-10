all:main
main:./src/metal.cpp 
	g++ -o main.exe -DDEBUG ./src/metal.cpp  -I ./include -g