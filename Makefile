.default: all

all: 

clean:
	rm -f assignment_1 *.o

assignment_1: Node.o NodeList.o PathPlanner.o main.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -c $^
