all : timer_jitter histogramme calculStats

histogramme: src/histogramme.c
	gcc src/histogramme.c -o bin/histogramme

calculStats: src/calculStats.c
	gcc src/calculStats.c -o bin/calculStats -lm

timer_jitter: src/timer_jitter.c
	gcc src/timer_jitter.c -o bin/timer_jitter  -lrt

clean :
	rm -rf timer_jitter timer