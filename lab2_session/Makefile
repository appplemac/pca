all: measure

popul: popul.c
	gcc -o popul popul.c

pi-O%: pi.c
	gcc -O$* -o pi-O$* pi.c

pi-pg-O%: pi.c
	gcc -O$* -pg -g -o pi-pg-O$* pi.c

pi-g-O%: pi.c
	gcc -O$* -g -o pi-g-O$* pi.c
