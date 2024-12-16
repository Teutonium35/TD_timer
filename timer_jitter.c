#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

void deroute(int sigNum) {
    // if (sigNum == 34){
    //     printf("1");
    // } 
    // else {
    //     printf("2");
    // }
    // fflush(stdout);
}
void my_function(int signo, int timer_delay, int nano_timer_delay){
    // Préparation d’une structure évènementielle et le traitement associé
    struct sigevent event;
    struct sigaction actEvent;
    // Préparer la structure évènementielle event
    // en générant le signal SIGRTMIN
    event.sigev_notify = SIGEV_SIGNAL;
    event.sigev_signo = signo;
    // Préparer le déroutement de SIGRTMIN
    actEvent.sa_handler = deroute;
    actEvent.sa_flags = 0;
    sigemptyset(&actEvent.sa_mask);
    sigaction(signo, &actEvent, NULL); // Signal TR
    // Création d’un timer POSIX
    timer_t timer;
    timer_create(CLOCK_REALTIME, &event, &timer);

    struct itimerspec period;
    struct itimerspec period_lent;
    // Préparer la structure temporelle period
    // un 1° déclenchement (it_value) dans 1s et
    // des déclenchements (it_interval) à 1s d’intervalle
    period.it_interval.tv_sec = timer_delay;
    period.it_interval.tv_nsec = nano_timer_delay;
    period.it_value = period.it_interval;
    // Armer le timer avec une périodicité de period
    printf("Test\n");
    timer_settime(timer, 0, &period, NULL);
    // le 2° argument indique que it_value désigne une durée
    // pour le premier déclenchement
}

int main(int argc, char * argv[]){
    int period_ns;
    if (argc < 2){
        printf("Use ./timer_jitter <period_ns>\n");
        exit(0);
    }
    else{
    period_ns = atoi(argv[1]);
    }
    int iterations = ((5E9 / period_ns) > 1E6) ? 1E6 : 5E9 / period_ns;
    my_function(SIGRTMAX, 0, period_ns);
    struct timespec current_time;
    struct timespec previous_time;
    int delta_s;
    int delta_us;
    int true_delta;
    int data_buffer[iterations];
    clock_gettime(CLOCK_REALTIME, &previous_time);

    for(int i = 0;i<iterations;i++){
        pause();
        clock_gettime(CLOCK_REALTIME, &current_time);
        delta_s = current_time.tv_sec - previous_time.tv_sec;
        delta_us = current_time.tv_nsec - previous_time.tv_nsec;
        true_delta = delta_us + 1E9*delta_s;

        // printf("Elapsed %d ns\n",true_delta);
        previous_time = current_time;
        data_buffer[i] = true_delta;
    }

    for(int i = 0;i<iterations;i++){
        printf("%d\n", data_buffer[i]);
    }
}