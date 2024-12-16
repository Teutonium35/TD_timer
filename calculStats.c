#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int c, char **v) {
	char ligne[1024];
	long int noMesure = 0;
	long int mesure, min , max;
	double moy = .0 , var = .0;
	double delta, ecart;
	while (fgets(ligne, 1024, stdin) != NULL) {
		sscanf(ligne,"%li", &mesure);
		if ((c >= 2) && (mesure > 100*atoi(v[1]))){
			continue;
		}
		noMesure++;
		if ((noMesure==1) || (min > mesure)) min = mesure;
		if ((noMesure==1) || (max < mesure)) max = mesure;
		delta = mesure - moy;
		moy += delta/noMesure;
		var += delta * (mesure - moy);
	}
	if (noMesure > 1)
		var /= noMesure - 1;
	ecart = sqrt(var);
	printf("Nb mesures = [%li]\n", noMesure);
	printf("Minimum = [%li]\nMoyenne = [%.01lf]\nMaximum = [%li]\n", min, moy, max);
	printf("Ecart-type = [%.01lf]\n", ecart);
	return 0;
}
