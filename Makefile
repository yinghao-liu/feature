NAME  = feature
MAJOR = 0
MINOR = 0
REVISION = 0

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"


CFLAGS=-g -D'VERSION=$(VERSION)'
all:main slave
main:main.c
slave:slave.c

clean:
	rm -rf main slave *.i *.o


.PHONY:clean all
