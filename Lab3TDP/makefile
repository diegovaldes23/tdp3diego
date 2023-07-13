FLAGS = -g

all: main test_Simplex test_Node

test_Simplex: Simplex.o Node.o Heap.o test_Simplex.cpp
	g++ $(FLAGS) Simplex.o Node.o Heap.o test_Simplex.cpp -o test_Simplex
	
Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

Node.o: Node.cpp  Node.h
	g++ $(FLAGS) -c Node.cpp

Heap.o: Heap.cpp Heap.h
	g++ $(FLAGS) -c Heap.cpp

test_Node: Node.o test_Node.cpp
	g++ $(FLAGS) Node.o test_Node.cpp -o test_Node

main: Simplex.o Node.o Heap.o main.cpp
	g++ $(FLAGS) Simplex.o Node.o Heap.o main.cpp -o main

clean:
	rm -f *.o test_Simplex test_Node main
