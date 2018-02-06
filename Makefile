MAJOR = 2
MINOR = 0
REVISION = 1
NAME  = curl_test

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CPPFLAGS= -c -g
LDFLAGS= -lpthread -lcurl
CC=g++
all:main

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o curl_builder.o
clean:
	@rm -rf *.o *.so main
