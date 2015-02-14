pi-clock: pi-clock.h pi-clock.c
	gcc -Wall -O3 -o ./pi-clock pi-clock.c -lbcm2835
