MAJOR = 0
MINOR = 0
REVISION = 0
BUILD = $(shell date +%Y%m%d_%H%M%S)
VERSION = "$(MAJOR).$(MINOR).$(REVISION).$(BUILD)"


CFLAGS=-g -D'VERSION=$(VERSION)'
all:main slave
main:main.c
slave:slave.c

clean:
	rm -rf main slave *.i *.o


.PHONY:clean all
