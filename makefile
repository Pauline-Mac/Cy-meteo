all: exec clean

main.o: main.c fonction.h
	gcc -c $< -o $@

fonction.o: fonction.c fonction.h
	gcc -c $< -o $@

exec: main.o fonction.o
	gcc $^ -o $@

clean:
	rm -f *.o
