all:main slave
main:main.c
slave:slave.c
.PHONY:clean all

clean:
	rm -rf main slave
