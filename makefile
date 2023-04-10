all:main
main:./src/dielectric.cpp 
	g++ -o main.exe -DDEBUG ./src/dielectric.cpp  -I ./include -g