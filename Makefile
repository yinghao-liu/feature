all:main

main:main.o print.o
	gcc -lstdc++ -o main main.o print.o
main.o:main.c
print.o:print.cpp
.PHONY:clean all
clean:
	rm -rf main *.o
