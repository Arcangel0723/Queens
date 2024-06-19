main: main.o genericCardGame.o
	gcc -Wall -Wextra -pedantic -o Queens main.o genericCardGame.o
main.o: main.c
	gcc -Wall -Wextra -pedantic -c main.c
genericCardGame.o: genericCardGame.c
	gcc -Wall -Wextra -pedantic -c genericCardGame.c
clean:
	rm Queens *.o