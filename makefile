all: sem.c
	gcc sem.c
clean:
	rm *.o
run: all
	./a.out
	./a.out -c
	./a.out -c 100
	./a.out -c 30
	./a.out -v
	./a.out -r
	./a.out -v
	./a.out -r
	./a.out -c 30
