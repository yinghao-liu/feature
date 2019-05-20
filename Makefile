MAJOR = 2
MINOR = 2
REVISION = 0
NAME  = 

BUILD = $(shell date +%c)
VERSION = "$(NAME) version $(MAJOR).$(MINOR).$(REVISION)\ncompiled $(BUILD)"

CXXFLAGS= -g#-std=c++11 #-fno-elide-constructors
LDFLAGS=
#LDLIBS=-lrt
#CC=$(CXX
all:main 

optimize:CXXFLAGS+=-O2
optimize:main

main.o:CXXFLAGS += -D'VERSION=$(VERSION)' -D'NAME="$(NAME)"'
main:main.o

clean:
	rm -rf *.o *.so *.a main
