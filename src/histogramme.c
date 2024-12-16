#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>
#include <stdio.h>
#include <math.h>
#define CHECK(sts,err,msg) if ((sts)==err) { perror(msg); exit(EXIT_FAILURE); }

int main (int c, char **v) {
	char ligne[1024];
	long int noMesure = 0;
	long int mesure, min , max;
	long int nbEch, largEch, iEch;
	int * frequences;		// des échantillons

	if ((c<4)
		|| (sscanf(v[1], "%li", &nbEch) != 1)
		|| (sscanf(v[2], "%li", &min)   != 1)
		|| (sscanf(v[3], "%li", &max)  != 1)) {
		printf("usage: %s <nb_échantillons> <min> <max>\n", basename(v[0]));
		exit(EXIT_FAILURE);
	}
	if (nbEch <= 0) {
		printf("Nombre d'échantillons invalide [%li]\n", nbEch);
		exit(EXIT_FAILURE);
	}
	largEch = (max - min)/nbEch;
	// Allouer espace mémoire pour stocker les fréquences
	CHECK(frequences=(int *)calloc(nbEch, sizeof(int)),NULL,"PB-- calloc()");

	while (fgets(ligne, 1024, stdin) != NULL) {
		sscanf(ligne,"%li", &mesure);
		noMesure++;
		iEch = (mesure - min)/largEch;
		if (iEch<0 || iEch>=nbEch) continue;	// Normalement, on arrête
		frequences[iEch]++;
	}
	for (iEch=0; iEch<nbEch; iEch++)
		printf("%.0lf %i\n", min+(iEch+0.5)*largEch, frequences[iEch]); 


	return 0;
}