MAJOR = 2
MINOR = 2
REVISION = 0
NAME  = 

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CPPFLAGS= -c -g -std=c++11
#LDFLAGS= -lpthread #-lcurl
CC=g++
all:libmember.a main 

libmember.a:member.o
	ar rs $@ $^

LDLIBS=-lmember -L.

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o mid.o

test_option_l:
	g++   main.o -lmember mid.o -L. -o main

#client:client.o
clean:
	rm -rf *.o *.so *.a main
