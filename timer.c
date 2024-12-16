#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
void deroute(int sigNum) {
    if (sigNum == 34){
        printf("1");
    } 
    else {
        printf("2");
    }
    fflush(stdout);
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
    timer_settime(timer, 0, &period, NULL);
    // le 2° argument indique que it_value désigne une durée
    // pour le premier déclenchement
}

int main(){
    my_function(SIGRTMIN, 1, 0);
    my_function(SIGRTMAX, 0, 250000000);

    while(1){
        pause();
    }
}