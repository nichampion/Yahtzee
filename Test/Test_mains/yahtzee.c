#include <stdio.h>
#include <stdlib.h>

#include "../../src/commun.h"
#include "../../src/mains.h"
#include "../../src/fonctions_joueur.h"

int main(){
	t_joueur *j1 = malloc(sizeof(t_joueur));
	int tab[5]={2,2,2,2,2};
	int test;

  for(int i = 0;i<5;i++)
		j1->des[i] = tab[i];

	test = yahtzee(j1);
	if(test != -1)
		printf("Resultat : %d\n",test);
	else
		printf("Pas de yahtzee \n");

}
