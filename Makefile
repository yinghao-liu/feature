CPPFLAGS= -c -g
LDFLAGS= -lrt
CC=g++
all:main
main:main.o
clean:
	@rm -rf *.o *.so main 
