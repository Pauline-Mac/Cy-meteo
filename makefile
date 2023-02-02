all: t1 t2 p1 h m w clean

t1.o: t1.c
	gcc -c $< -o $@

t2.o: t2.c
	gcc -c $< -o $@

p1.o: p1.c
	gcc -c $< -o $@

w.o: w.c
	gcc -c $< -o $@ -lm

h.o: h.c
	gcc -c $< -o $@

m.o: m.c
	gcc -c $< -o $@

function.o: fonction.c function.h
	gcc -c $< -o $@

t1: t1.o
	gcc t1.o -o t1

t2: t2.o
	gcc t2.o -o t2

p1: p1.o
	gcc p1.o -o p1
h: h.o
	gcc h.o -o h
m: m.o
	gcc m.o -o m
w: w.o
	gcc w.o -o w -lm


clean:
	rm -f *.o
