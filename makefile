all : timer_jitter histogramme calculStats

histogramme: histogramme.c
	gcc histogramme.c -o histogramme

calculStats: calculStats.c
	gcc calculStats.c -o calculStats -lm

timer_jitter: timer_jitter.c
	gcc timer_jitter.c -o timer_jitter  -lrt

clean :
	rm -rf timer_jitter timer