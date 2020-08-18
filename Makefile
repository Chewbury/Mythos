mythos : main.o display.o generate.o
	gcc -o mythos main.o display.o generate.o -lncurses

main.o : main.c
	gcc -c main.c

generate.o : generate.c
	gcc -c generate.c

display.o : display.c
	gcc -c display.c

clean :
	rm mythos main.o display.o generate.o
