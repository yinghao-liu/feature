MAJOR = 2
MINOR = 1
REVISION = 0
NAME  = time

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CPPFLAGS= -c -g
#LDFLAGS= -lpthread -lcurl
CC=g++
all:main

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o
clean:
	@rm -rf *.o *.so main
