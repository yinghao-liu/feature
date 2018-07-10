# test feature of language
This is a test for option -O2 in g++.  
Below is an excerpt from man gcc  
> -O2 turns on all optimization flags specified by -O.  It also turns on the following optimization flags: **-fthread-jumps -falign-functions  -falign-jumps
-falign-loops  -falign-labels -fcaller-saves -fcrossjumping -fcse-follow-jumps  -fcse-skip-blocks -fdelete-null-pointer-checks -fdevirtualize
-fdevirtualize-speculatively -fexpensive-optimizations -fgcse  -fgcse-lm -fhoist-adjacent-loads -finline-small-functions -findirect-inlining -fipa-cp
-fipa-bit-cp -fipa-vrp -fipa-sra -fipa-icf -fisolate-erroneous-paths-dereference -flra-remat -foptimize-sibling-calls -foptimize-strlen -fpartial-inlining
-fpeephole2 -freorder-blocks-algorithm=stc -freorder-blocks-and-partition -freorder-functions -frerun-cse-after-loop -fsched-interblock  -fsched-spec
-fschedule-insns  -fschedule-insns2 -fstore-merging -fstrict-aliasing -fstrict-overflow -ftree-builtin-call-dce -ftree-switch-conversion -ftree-tail-merge
-fcode-hoisting -ftree-pre -ftree-vrp -fipa-ra**

I do not know all of those optimization flags, but I think those should only be used in **release** version, so I can find errors when I debug this program. 
In this demo, when you run `make && ./main`, you would find the program crash because of **Segmentation fault**, then I can locate the location where caused this error through GDB or something else. you can see the difference between **make** and **make optimize**
