all: test

AVL.o: AVL.c AVL.h
	gcc -c AVL.c -o AVL.o

#verification.o: verification.c verification.h AVL2.h
	#gcc -c verification.c -o verification.o

main.o: main.c AVL.h 
	gcc -c main.c -o main.o

test: AVL.o main.o
	gcc AVL.o main.o -o test
