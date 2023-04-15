all:main
main:./src/$(fn).cpp 
	g++ -o main ./src/$(fn).cpp  -I ./include -g