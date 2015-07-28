RRNAfold: RRNAfold.o RRNAfold_opts.o
	gcc RRNAfold.o RRNAfold_opts.o -o RRNAfold -L/Users/jpbida/archive/horton/projects/APPS/ViennaRNA-2.1.9/lib -lRNA -lm 

RRNAfold.o: RRNAfold.c
	gcc -c RRNAfold.c -I/Users/jpbida/archive/horton/projects/APPS/ViennaRNA-2.1.9/H

RRNAfold_opts.o: RRNAfold_opts.c
	gcc -c RRNAfold_opts.c 
