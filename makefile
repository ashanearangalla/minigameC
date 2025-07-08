escape : main.o displayMap.o random.o terminal.o newSleep.o linked.o
	gcc main.o displayMap.o random.o terminal.o newSleep.o linked.o -o escape

main.o : main.c displayMap.h random.h terminal.h newSleep.h linked.h
	gcc -Wall -ansi -pedantic main.c -c

displayMap.o : displayMap.c displayMap.h random.h newSleep.h linked.h
	gcc -Wall -ansi -pedantic displayMap.c -c

random.o : random.c random.h
	gcc -Wall -ansi -pedantic random.c -c

terminal.o : terminal.c terminal.h
	gcc -Wall -ansi -pedantic terminal.c -c

newSleep.o : newSleep.c newSleep.h
	gcc -Wall -ansi -pedantic newSleep.c -c

linked.o : linked.c linked.h
	gcc -Wall -ansi -pedantic linked.c -c

clean : 
	rm -f escape main.o displayMap.o random.o terminal.o newSleep.o linked.o