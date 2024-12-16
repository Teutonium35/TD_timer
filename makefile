all : timer_jitter

timer_jitter: timer_jitter.c
	gcc timer_jitter.c -o timer_jitter  -lrt

clean :
	rm -rf timer_jitter timer