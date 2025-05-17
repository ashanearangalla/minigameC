prog : main.o displayMap.o random.o
	gcc main.o displayMap.o random.o -o prog

main.o : main.c displayMap.h random.h
	gcc -Wall -ansi -pedantic main.c -c

displayMap.o : displayMap.c random.h
	gcc -Wall -ansi -pedantic displayMap.c -c

random.o : random.c
	gcc -Wall -ansi -pedantic random.c -c

clean : 
	rm -f prog main.o displayMap.o random.o