MAJOR = 2
MINOR = 2
REVISION = 0
NAME  = 

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CXXFLAGS= -g -std=c++11
CC=$(CXX)
all:main

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o member.o
#client:client.o
clean:
	@rm -rf *.o *.so main
