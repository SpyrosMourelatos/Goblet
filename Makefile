
debug: 
	g++ *.cpp -o game -lncurses -g -ggdb3
build: 
	g++ *.cpp -o game -lncurses -o3
clean:
	rm -f game outputs.txt
