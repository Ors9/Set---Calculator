myset: myset.o troubleshooter.o set.o

	gcc -g -Wall -ansi -pedantic myset.o troubleshooter.o set.o -o myset

set.o: set.c set.h

	gcc -c -Wall -ansi -pedantic set.c -o set.o	

troubleshooter.o: troubleshooter.c

	gcc -c -Wall -ansi -pedantic troubleshooter.c -o troubleshooter.o

myset.o: myset.c set.h

	gcc -c -Wall -ansi -pedantic myset.c -o myset.o 

exec:

		./myset