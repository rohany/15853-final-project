CC = g++ -std=c++11

default: k-merge.o buffer-tree.o
	$(CC) main.cpp -o sort k-merge.o buffer-tree.o -O3

k-merge.o: k-merge.cpp k-merge.hpp
	$(CC) -c k-merge.cpp -o k-merge.o -O3

buffer-tree.o: buffer-tree.cpp buffer-tree.hpp
	$(CC) -c buffer-tree.cpp -o buffer-tree.o -O3

clean:
	rm *.o sort
