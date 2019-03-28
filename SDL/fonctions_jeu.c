#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "commun.h"
#include "fonctions_jeu.h"
#include "fonctions_joueur.h"
#include "mains.h"

/**
	*\File : fonctions_jeu.c
	*\Brief : Fonctions du jeu
	*\version 1.0
	*\Author : Sunny BIARD
*/

/**
	*\Fn : void lancer(t_joueur * j, int i)
	*\Param : Un pointeur sur un joueur, un int correspondant au dé à lancer
	*\Brief : Affectation d'un nombre tiré aléatoirement entre 1 et 6 au dé n°i
	*\Author : Sunny BIARD
*/
void lancer(t_joueur * j, int i){

	j->des[i] = rand()%(7-1) + 1;

}

/**
	*\Fn : int relancer(t_joueur * j)
	*\Param : Un pointeur sur un joueur
	*\Brief : Choix du/des dé(s) à relancer, Relancement de ce(s) dé(s) par appel de "lancer"
	*\Author : Sunny BIARD
*/
int relancer(t_joueur * j){

	int i, relance, rep;

	printf("Voulez vous relancer ? (0 : Non, 1 : Oui) ");
	scanf("%d",&rep);

	if(rep == 1){
		for(i = 0; i < 5; i++){
			printf("Voulez vous relancer le dé n°%d ? (0 : Non, 1 : Oui) ", i+1);
			scanf("%d", &relance);

			if(relance == 1){
				lancer(j,i);
			}
		}
		return 1;
	}

	return 0;
}

/**
	*\Fn : t_joueur * test_mains(t_joueur * j)
	*\Param : Un pointeur sur un joueur
	*\Brief : Test de toutes les combinaisons possibles avec les dés du joueur j
	*\Author : Sunny BIARD
*/
t_joueur * test_mains(t_joueur *j){

	t_joueur * j_test = creer_joueur("Choix");

	if((j->tab.as) == VAL_INIT)
		j_test->tab.as = section_superieure(j,1);

	if((j->tab.deux) == VAL_INIT)
		j_test->tab.deux = section_superieure(j,2);

	if((j->tab.trois) == VAL_INIT)
		j_test->tab.trois = section_superieure(j,3);

	if((j->tab.quatres) == VAL_INIT)
		j_test->tab.quatres = section_superieure(j,4);

	if((j->tab.cinq) == VAL_INIT)
		j_test->tab.cinq = section_superieure(j,5);

	if((j->tab.six) == VAL_INIT)
		j_test->tab.six = section_superieure(j,6);

	if((j->tab.brelan) == VAL_INIT)
		j_test->tab.brelan = brelan(j);

	if((j->tab.carre) == VAL_INIT)
		j_test->tab.carre = carre(j);

	if((j->tab.full) == VAL_INIT)
		j_test->tab.full = full(j);

	if((j->tab.petite_Suite) == VAL_INIT)
		j_test->tab.petite_Suite = petite_suite(j);

	if((j->tab.grande_Suite) == VAL_INIT)
		j_test->tab.grande_Suite = grande_suite(j);

	if((j->tab.chance) == VAL_INIT)
		j_test->tab.chance = chance(j);

	if((j->tab.yahtzee) == VAL_INIT)
		j_test->tab.yahtzee = yahtzee(j);
	else if((j->tab.yahtzee) == 50)
		j_test->tab.prime_Yahtzee = 100;

	return j_test;

}

/**
	*\Fn : int choix_placement(t_joueur * j, t_joueur * j_test)
	*\Param : Un pointeur sur un joueur, un autre pointeur sur un joueur test
	*\Brief : Choix de remplissage d'une case du joueur courant
	*\Author : Sunny BIARD
*/
int choix_placement(t_joueur *j, t_joueur * j_test){
	int choix, placement = 0;
	printf("Choisir la case à remplir (1-14) : ");
	scanf("%d",&choix);
	while(choix < 1 || choix > 14){
		printf("Choisir la case à remplir (1-14) : ");
		scanf("%d",&choix);
	}

	switch(choix)
	{
		case 1 :
			if(j->tab.as == VAL_INIT){
				if(j_test->tab.as != VAL_INIT){
					j->tab.as = j_test->tab.as;
				}
				else{
					j->tab.as = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 2 :
			if(j->tab.deux == VAL_INIT){
				if(j_test->tab.deux != VAL_INIT){
					j->tab.deux = j_test->tab.deux;
				}
				else{
					j->tab.deux = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 3 :
			if(j->tab.trois == VAL_INIT){
				if(j_test->tab.trois != VAL_INIT){
					j->tab.trois = j_test->tab.trois;
				}
				else{
					j->tab.trois = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 4 :
			if(j->tab.quatres == VAL_INIT){
				if(j_test->tab.quatres != VAL_INIT){
					j->tab.quatres = j_test->tab.quatres;
				}
				else{
					j->tab.quatres = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 5 :
			if(j->tab.cinq == VAL_INIT){
				if(j_test->tab.cinq != VAL_INIT){
					j->tab.cinq = j_test->tab.cinq;
				}
				else{
					j->tab.cinq = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 6 :
			if(j->tab.six == VAL_INIT){
				if(j_test->tab.six != VAL_INIT){
					j->tab.six = j_test->tab.six;
				}
				else{
					j->tab.six = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 7 :
			if(j->tab.brelan == VAL_INIT){
				if(j_test->tab.brelan != VAL_INIT){
					j->tab.brelan = j_test->tab.brelan;
				}
				else{
					j->tab.brelan = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 8 :
			if(j->tab.carre == VAL_INIT){
				if(j_test->tab.carre != VAL_INIT){
					j->tab.carre = j_test->tab.carre;
				}
				else{
					j->tab.carre = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 9 :
			if(j->tab.full == VAL_INIT){
				if(j_test->tab.full != VAL_INIT){
					j->tab.full = j_test->tab.full;
				}
				else{
					j->tab.full = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 10 :
			if(j->tab.petite_Suite == VAL_INIT){
				if(j_test->tab.petite_Suite != VAL_INIT){
					j->tab.petite_Suite = j_test->tab.petite_Suite;
				}
				else{
					j->tab.petite_Suite = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 11 :
			if(j->tab.grande_Suite == VAL_INIT){
				if(j_test->tab.grande_Suite != VAL_INIT){
					j->tab.grande_Suite = j_test->tab.grande_Suite;
				}
				else{
					j->tab.grande_Suite = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 12 :
			if(j->tab.chance == VAL_INIT){
				if(j_test->tab.chance != VAL_INIT){
					j->tab.chance = j_test->tab.chance;
				}
				else{
					j->tab.chance = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 13 :
			if(j->tab.yahtzee == VAL_INIT){
				if(j_test->tab.yahtzee != VAL_INIT){
					j->tab.yahtzee = j_test->tab.yahtzee;
				}
				else{
					j->tab.yahtzee = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
		case 14 :
			if(j->tab.prime_Yahtzee == VAL_INIT){
				if(j_test->tab.prime_Yahtzee != VAL_INIT){
					j->tab.prime_Yahtzee = j_test->tab.prime_Yahtzee;
				}
				else{
					j->tab.prime_Yahtzee = 0;
				}
				placement = 1;
				break;
			}
			else{
				printf("Impossible de remplir cette case. Veuillez en choisir une autre.\n");
				break;
			}
	}

	return placement;

}

/**
	*\Fn : void affichage_possibilites(t_joueur * j, t_joueur * j_test)
	*\Param : Un pointeur sur un joueur, un pointeur sur un joueur test
	*\Brief : Affichage des combinaisons possibles et croix pour les cases déjà remplies pour le joueur j
	*\Author : Sunny BIARD
*/
void affichage_possibilites(t_joueur * j, t_joueur * j_test){

	printf("* * * * * * * * * * * * TOUR %s * * * * * * * * * * * * *\n",j->nom);
  printf("*\t\t\t\t\t\t\t*\n");
  printf("*\t._______________________________.\t\t*\n");
  printf("*\t|\t\t%s\t\t|\t\t*\n", j->nom);
  printf("*\t|-------------------------------|\t\t*\n");
	if(j_test->tab.as != VAL_INIT)
  	  printf("*\t| 1 As\t\t%d?\t\t|\t\t*\n", j_test->tab.as);
	else
  	  printf("*\t| 1 As\t\t%d\t\t|\t\t*\n", j->tab.as);
	if(j_test->tab.deux != VAL_INIT)
	  printf("*\t| 2 Deux\t%d?\t\t|\t\t*\n", j_test->tab.deux);
	else
  	  printf("*\t| 2 Deux\t%d\t\t|\t\t*\n", j->tab.deux);
	if(j_test->tab.trois != VAL_INIT)
	  printf("*\t| 3 Trois\t%d?\t\t|\t\t*\n", j_test->tab.trois);
	else
  	  printf("*\t| 3 Trois\t%d\t\t|\t\t*\n", j->tab.trois);
	if(j_test->tab.quatres != VAL_INIT)
	  printf("*\t| 4 Quatres\t%d?\t\t|\t\t*\n", j_test->tab.quatres);
	else
  	  printf("*\t| 4 Quatres\t%d\t\t|\t\t*\n", j->tab.quatres);
	if(j_test->tab.cinq != VAL_INIT)
	  printf("*\t| 5 Cinq\t%d?\t\t|\t\t*\n", j_test->tab.cinq);
	else
  	  printf("*\t| 5 Cinq\t%d\t\t|\t\t*\n", j->tab.cinq);
	if(j_test->tab.six != VAL_INIT)
	  printf("*\t| 6 Six\t\t%d?\t\t|\t\t*\n", j_test->tab.six);
	else
  	  printf("*\t| 6 Six\t\t%d\t\t|\t\t*\n", j->tab.six);

	printf("*\t| Total\t\t%d\t\t|\t\t*\n", j->tab.total_Sup);
	printf("*\t| Prime\t\t%d\t\t|\t\t*\n", j->tab.prime_35pts);
  printf("*\t|-------------------------------|\t\t*\n");

	if(j_test->tab.brelan != VAL_INIT)
	  printf("*\t| 7 Brelan\t%d?\t\t|\t\t*\n", j_test->tab.brelan);
	else
  	  printf("*\t| 7 Brelan\t%d\t\t|\t\t*\n", j->tab.brelan);
	if(j_test->tab.carre != VAL_INIT)
	  printf("*\t| 8 Carre\t%d?\t\t|\t\t*\n", j_test->tab.carre);
	else
  	  printf("*\t| 8 Carre\t%d\t\t|\t\t*\n", j->tab.carre);
	if(j_test->tab.full != VAL_INIT)
	  printf("*\t| 9 Full\t%d?\t\t|\t\t*\n", j_test->tab.full);
	else
  	  printf("*\t| 9 Full\t%d\t\t|\t\t*\n", j->tab.full);
	if(j_test->tab.petite_Suite != VAL_INIT)
	  printf("*\t| 10 P Suite\t%d?\t\t|\t\t*\n", j_test->tab.petite_Suite);
	else
  	  printf("*\t| 10 P Suite\t%d\t\t|\t\t*\n", j->tab.petite_Suite);
	if(j_test->tab.grande_Suite != VAL_INIT)
	  printf("*\t| 11 G Suite\t%d?\t\t|\t\t*\n", j_test->tab.grande_Suite);
	else
  	  printf("*\t| 11 G Suite\t%d\t\t|\t\t*\n", j->tab.grande_Suite);
	if(j_test->tab.chance != VAL_INIT)
	  printf("*\t| 12 Chance\t%d?\t\t|\t\t*\n", j_test->tab.chance);
	else
  	  printf("*\t| 12 Chance\t%d\t\t|\t\t*\n", j->tab.chance);
	if(j_test->tab.yahtzee != VAL_INIT)
	  printf("*\t| 13 Yahtzee\t%d?\t\t|\t\t*\n", j_test->tab.yahtzee);
	else
	  printf("*\t| 13 Yahtzee\t%d\t\t|\t\t*\n", j->tab.yahtzee);
	if(j_test->tab.prime_Yahtzee != VAL_INIT)
	  printf("*\t| 14 Prime\t%d?\t\t|\t\t*\n", j->tab.prime_Yahtzee);
	else
	  printf("*\t| 14 Prime\t%d\t\t|\t\t*\n", j_test->tab.prime_Yahtzee);

	printf("*\t| Total\t\t%d\t\t|\t\t*\n", j->tab.total_Inf);
  printf("*\t|-------------------------------|\t\t*\n");
  printf("*\t|TOTAL\t\t%d\t\t|\t\t*\n", j->tab.total_Gen);
  printf("*\t|_______________________________|\t\t*\n");
  printf("*\t\t\t\t\t\t\t*\n");
  printf("*\t.________________________________.\t\t*\n");
  printf("*\t|1\t2\t3\t4\t5|\t\t*\n");
  printf("*\t|%d\t%d\t%d\t%d\t%d|\t\t*\n", j->des[0], j->des[1], j->des[2], j->des[3], j->des[4]);
  printf("*\t.________________________________.\t\t*\n");
  printf("*\t\t\t\t\t\t\t*\n");
  printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");

}

/**
	*\Fn : int fin_de_partie(t_joueur * j)
	*\Param : Un pointeur sur un joueur
	*\Brief : Test si toutes les cases du joueur sont remplies, renvoie vrai si rempli
	*\Author : Sunny BIARD
*/
int fin_de_partie(t_joueur * j){
	if(j->tab.as != VAL_INIT && j->tab.deux != VAL_INIT && j->tab.trois != VAL_INIT && j->tab.quatres != VAL_INIT && j->tab.cinq != VAL_INIT && j->tab.six != VAL_INIT && j->tab.brelan != VAL_INIT && j->tab.carre != VAL_INIT && j->tab.full != VAL_INIT && j->tab.petite_Suite != VAL_INIT && j->tab.petite_Suite != VAL_INIT && j->tab.grande_Suite != VAL_INIT && j->tab.chance != VAL_INIT && j->tab.yahtzee != VAL_INIT && j->tab.prime_Yahtzee != VAL_INIT){
		calcul_totaux(j);
		prime_tab(j);
		return 1;
	}
	else
		return 0;



}