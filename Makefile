CFLAGS= -c -fpic -g
LDFLAGS=-Wl,-rpath,.
LIBFLAGS=-shared

all:main print.so

main:main.o print.so
	gcc -o $@ $^ $(LDFLAGS)
print.so:print.o
	gcc -o $@ $^ $(LIBFLAGS)
%.o:%.c
	gcc -o $@ $^ $(CFLAGS)
clean:
	@rm -rf *.o *.so main 
