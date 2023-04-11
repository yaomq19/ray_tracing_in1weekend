all:main
main:./src/manySphere.cpp 
	g++ -o main.exe -DDEBUG ./src/manySphere.cpp  -I ./include -g