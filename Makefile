
debug: 
	g++ -Iinclude src/*.cpp -o game -lncurses -g -ggdb3
build: 
	g++ -Iinclude src/*.cpp -o game -lncurses -o3
clean:
	rm -f game outputs.txt
