all:main slave
main:main.c
	cc -g -o main main.c
slave:slave.c

clean:
	rm -rf main slave


.PHONY:clean all
