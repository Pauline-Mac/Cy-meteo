all: t1 p1 h m w clean

t1.o: t1.c function.h
	gcc -c $< -o $@

p1.o: p1.c function.h
	gcc -c $< -o $@

w.o: w.c function.h
	gcc -c $< -o $@

h.o: h.c function.h
	gcc -c $< -o $@

m.o: m.c function.h
	gcc -c $< -o $@

function.o: fonction.c function.h
	gcc -c $< -o $@

t1: t1.o
	gcc t1.o -o t1
p1: p1.o
	gcc p1.o -o p1
h: h.o
	gcc h.o -o h
m: m.o
	gcc m.o -o m
w: w.o
	gcc w.o -o w


clean:
	rm -f *.o
