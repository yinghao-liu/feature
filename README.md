# test feature of language
This is a test for option -l in g++.  
Below is an excerpt from man gcc  
> It makes a difference where in the command you write this option; the linker searches and processes libraries and object files in the order they are
specified.  Thus, **foo.o -lz bar.o** searches library **z** after file foo.o but before bar.o.  If bar.o refers to functions in z, those functions may not be
loaded.

In this demo, **main** depend on **main.o mid.o**, and **mid.o** depend on **libmember.a**  
and then, you can see the difference between **make** and **make test\_option\_l**
