all: btree
	g++ btree.cpp -o btree


run:
	./btree

clean:
	rm -rf *.o
