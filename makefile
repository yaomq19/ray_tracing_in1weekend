all:main
main:./src/$(fn).cpp 
	g++ -o main -DDEBUG ./src/$(fn).cpp  -I ./include -g