CC = g++ -std=c++11

default: k-merge.o buffer-tree.o
	$(CC) main.cpp -o sort k-merge.o buffer-tree.o

k-merge.o:
	$(CC) -c k-merge.cpp -o k-merge.o

buffer-tree.o:
	$(CC) -c buffer-tree.cpp -o buffer-tree.o

clean:
	rm *.o sort
