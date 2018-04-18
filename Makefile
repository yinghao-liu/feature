MAJOR = 2
MINOR = 2
REVISION = 0
NAME  = 

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CPPFLAGS= -c -g -std=c++11
#LDFLAGS= -lpthread #-lcurl
CC=g++
all:main client

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o
client:client.o
clean:
	@rm -rf *.o *.so main
