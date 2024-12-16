#include <unistd>
#include <stdlib>
#include <stdio>
#include <signal>

int main (int c, char ** v){
    if (c<=3){
        printf("usage : %s <pid> <sigNum> <value> \n", v[0]);
        exit(-1);
    }

    // Manque des trucs ici
}