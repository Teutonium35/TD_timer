#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char **argv) {
	char ligne[1024];
	long int noMesure = 0;
	long int mesure, min , max;
	double moy = .0 , var = .0;
	double delta, ecart;
	int target = atoi(argv[1]);
	FILE * input_file = fopen(("results/data/%s", argv[1]), "r");
	printf("Input file : %s\n", (("results/data/%s", argv[1])));

	while (fgets(ligne, 1024, input_file) != NULL) {
		sscanf(ligne,"%li", &mesure);
		if (mesure > 100*target){
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
