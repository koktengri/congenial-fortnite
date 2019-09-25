all: clobber main

main : gphlib.o msclib.o mxplib.o explib.o ...
	clang -g gphlib.o msclib.o mxplib.o explib.o ... main.cpp -o main

msclib.o:
	clang -c msclib.cpp

mxplib.o: msclib.o
	clang -c mxplib.cpp

gphlib.o:
	clang -c gphlib.cpp

explib.o:
	clang -c explib.cpp

clean:
	rm -rf *.o

clobber: clean
	rm -rf main
