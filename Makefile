MAJOR = 2
MINOR = 2
REVISION = 0
NAME  = 

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CXXFLAGS= -c -g -std=c++11
#LDFLAGS= -lpthread #-lcurl
CC=$(CXX)
all:main 

optimize:CXXFLAGS+=-O2
optimize:main

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o client.o

clean:
	rm -rf *.o *.so *.a main
