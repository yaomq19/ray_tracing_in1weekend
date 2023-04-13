all:main
main:./src/$(fn).cpp 
	g++ -o ./bin/main ./src/$(fn).cpp  -I ./include -g