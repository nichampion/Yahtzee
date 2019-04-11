#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "commun.h"
#include "fonctions_jeu.h"
#include "fonctions_joueur.h"
#include "mains.h"
#include "ordinateur.h"

int main(int argc, char** argv)
{
	srand(time(NULL));


	t_joueur * j1 = creer_joueur("J1");
	t_joueur * j2 = creer_joueur("Ordinateur");
	t_joueur * j_choix = creer_joueur("Choix");
	t_joueur ** ptj = &j1;

	int cpt_lancer = 0, de_pos[5] = {0,0,0,0,0}, clic_borneG_x, clic_borneD_x, clic_borneS_y, clic_borneI_y, coup, i, p;
	char  score[20], msg_fin[50];

	SDL_Window *pWindow = NULL;

  	SDL_Surface *j_courant=NULL, *msg=NULL, *tab_score=NULL, *de_courant=NULL, *de1=NULL, *de2=NULL, *de3=NULL, *de4=NULL, *de5=NULL, *de6=NULL, *img_btn_lancer=NULL, *caseJ=NULL;
	SDL_Renderer *renderer=NULL;
	SDL_Rect clearDestRect, j_courantDestRect, msgDestRect, imgDestRect, img2DestRect, scoreDestRect, caseDestRect;

	caseDestRect.w = 49;
	caseDestRect.h = 27;

	img2DestRect.w = 50;
	img2DestRect.h = 50;

	j_courantDestRect.y = 50;
	j_courantDestRect.w = 100;
	j_courantDestRect.h = 100;

	clearDestRect.x = 300;
	clearDestRect.y = 0;
	clearDestRect.w = 700;
	clearDestRect.w = 700;

	SDL_Texture *image_texde1, *image_texde2, *image_texde3, *image_texde4, *image_texde5, *caseJ_tex;
	SDL_Texture **pt_image_texde[5] = {&image_texde1,&image_texde2,&image_texde3,&image_texde4,&image_texde5};

	TTF_Font *police_jeu = NULL, *police_score = NULL;

	SDL_Color blanc = {255, 255, 255};
	SDL_Color noir = {0, 0, 0};
	SDL_Color rouge = {255, 0, 0};

 	/* Initialisation simple */
  if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
  	fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
    return -1;
  }

	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}


	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Yahtzee",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 750, SDL_WINDOW_SHOWN);

	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}


	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}


	if( (police_score = TTF_OpenFont("coolvetica rg.ttf", 20)) == NULL){
		fprintf(stderr, "Erreur au chargement de la police\n");
		exit(EXIT_FAILURE);
	}

	if( (police_jeu = TTF_OpenFont("coolvetica rg.ttf", 35)) == NULL){
		fprintf(stderr, "Erreur au chargement de la police\n");
		exit(EXIT_FAILURE);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// load sample.png into image
	SDL_RWops *rwopscore=SDL_RWFromFile("img/score.png", "rb");
	tab_score=IMG_LoadPNG_RW(rwopscore);
	if(!tab_score) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_Texture *tab_score_tex = SDL_CreateTextureFromSurface(renderer, tab_score);
	if(!tab_score_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_FreeSurface(tab_score); /* on a la texture, plus besoin de l'image */

	SDL_RWops *rwopde1=SDL_RWFromFile("img/de1.png", "rb");
	de1=IMG_LoadPNG_RW(rwopde1);
	if(!de1) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_RWops *rwopde2=SDL_RWFromFile("img/de2.png", "rb");
	de2=IMG_LoadPNG_RW(rwopde2);
	if(!de2) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_RWops *rwopde3=SDL_RWFromFile("img/de3.png", "rb");
	de3=IMG_LoadPNG_RW(rwopde3);
	if(!de3) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_RWops *rwopde4=SDL_RWFromFile("img/de4.png", "rb");
	de4=IMG_LoadPNG_RW(rwopde4);
	if(!de4) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_RWops *rwopde5=SDL_RWFromFile("img/de5.png", "rb");
	de5=IMG_LoadPNG_RW(rwopde5);
	if(!de5) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_RWops *rwopde6=SDL_RWFromFile("img/de6.png", "rb");
	de6=IMG_LoadPNG_RW(rwopde6);
	if(!de6) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_RWops *rwop_btn_lancer=SDL_RWFromFile("img/btn_lancer.png", "rb");
	img_btn_lancer=IMG_LoadPNG_RW(rwop_btn_lancer);
	if(!img_btn_lancer) {
		printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
	}

	SDL_Texture *btn_lancer_tex = SDL_CreateTextureFromSurface(renderer, img_btn_lancer);
	if(!btn_lancer_tex){
		fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_FreeSurface(img_btn_lancer); /* on a la texture, plus besoin de l'image */

	if(pWindow){
		int running = 1;
		while(running){
			SDL_Event e;
			while(SDL_PollEvent(&e)){
				switch(e.type) {
					case SDL_QUIT:
						running = 0;
					break;

					case SDL_WINDOWEVENT:
						switch(e.window.event){
							case SDL_WINDOWEVENT_SHOWN:
								/* Le fond de la fenêtre sera vert */
			        			SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
								SDL_RenderClear(renderer);

			        			/* Ajout du texte en noir */
			        			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

			      				imgDestRect.x = 10;
								imgDestRect.y = 50;

								SDL_QueryTexture(tab_score_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, tab_score_tex, NULL, &imgDestRect);

								imgDestRect.x = 575;
								imgDestRect.y = 500;

								SDL_QueryTexture(btn_lancer_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, btn_lancer_tex, NULL, &imgDestRect);

								/* On fait le rendu ! */
								SDL_RenderPresent(renderer);

							break;
						}
					break;

					case SDL_MOUSEBUTTONUP:

						if(ptj == &j2){
							if(tour_ordinateur(*ptj) >= 0){

								SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
								SDL_RenderFillRect(renderer,&clearDestRect);

								j_courantDestRect.x = 520;

								sprintf(score,"%s",(*ptj)->nom);
								j_courant = TTF_RenderUTF8_Blended(police_jeu, score, blanc);
								if(!j_courant){
									fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
									exit(EXIT_FAILURE);
								}

								SDL_Texture *j_courant_tex = SDL_CreateTextureFromSurface(renderer, j_courant);
								if(!j_courant_tex){
									fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
									exit(EXIT_FAILURE);
								}

								SDL_QueryTexture(j_courant_tex, NULL, NULL, &(j_courantDestRect.w), &(j_courantDestRect.h));
								SDL_RenderCopy(renderer, j_courant_tex, NULL, &j_courantDestRect);

								SDL_RenderPresent(renderer);

								sleep(1);

								scoreDestRect.x = 252;
								caseDestRect.x = 234;
								caseDestRect.y = scoreDestRect.y = 80;

								for(i = 0; i < 14; i++){

									if(i == 6){
										caseDestRect.y = (scoreDestRect.y += 48);
									}

									else{

										SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
										SDL_RenderFillRect(renderer,&caseDestRect);
										if((*ptj)->tab[i] != VAL_INIT){

											sprintf(score,"%d",(*ptj)->tab[i]);
											caseJ = TTF_RenderUTF8_Blended(police_score, score, noir);
											if(!caseJ){
												fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
												exit(EXIT_FAILURE);
											}

											caseJ_tex = SDL_CreateTextureFromSurface(renderer, caseJ);
											if(!caseJ_tex){
												fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
												exit(EXIT_FAILURE);
											}

											SDL_QueryTexture(caseJ_tex, NULL, NULL, &(scoreDestRect.w), &(scoreDestRect.h));
											SDL_RenderCopy(renderer, caseJ_tex, NULL, &(scoreDestRect));
										}
									}
									caseDestRect.y = (scoreDestRect.y += 29);

								}

								imgDestRect.x = 575;
								imgDestRect.y = 500;

								SDL_QueryTexture(btn_lancer_tex, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, btn_lancer_tex, NULL, &imgDestRect);

								SDL_RenderPresent(renderer);

								ptj = &j1;

							}
						}

						if(fin_de_partie(j1) && fin_de_partie(j2)){

							scoreDestRect.x = 202;
							caseDestRect.x = 184;
							caseDestRect.y = scoreDestRect.y = 254;
							i = 6;

							while(i < 17){

								SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderFillRect(renderer,&caseDestRect);
								sprintf(score,"%d",j1->tab[i]);
								caseJ = TTF_RenderUTF8_Blended(police_score, score, noir);
								if(!caseJ){
									fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
									exit(EXIT_FAILURE);
								}

								caseJ_tex = SDL_CreateTextureFromSurface(renderer, caseJ);
								if(!caseJ_tex){
									fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
									exit(EXIT_FAILURE);
								}

								SDL_QueryTexture(caseJ_tex, NULL, NULL, &(scoreDestRect.w), &(scoreDestRect.h));
								SDL_RenderCopy(renderer, caseJ_tex, NULL, &(scoreDestRect));

								caseDestRect.y = (scoreDestRect.y += 29);

								if(i == 14){
									caseDestRect.y = (scoreDestRect.y += 222);
								}

								if(i == 6)
									i = 14;
								else
									i++;
							}

							scoreDestRect.x = 252;
							caseDestRect.x = 234;
							caseDestRect.y = scoreDestRect.y = 254;
							i = 6;

							while(i < 17){

								SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderFillRect(renderer,&caseDestRect);
								sprintf(score,"%d",j2->tab[i]);
								caseJ = TTF_RenderUTF8_Blended(police_score, score, noir);
								if(!caseJ){
									fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
									exit(EXIT_FAILURE);
								}

								caseJ_tex = SDL_CreateTextureFromSurface(renderer, caseJ);
								if(!caseJ_tex){
									fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
									exit(EXIT_FAILURE);
								}

								SDL_QueryTexture(caseJ_tex, NULL, NULL, &(scoreDestRect.w), &(scoreDestRect.h));
								SDL_RenderCopy(renderer, caseJ_tex, NULL, &(scoreDestRect));

								caseDestRect.y = (scoreDestRect.y += 29);

								if(i == 14){
									caseDestRect.y = (scoreDestRect.y += 222);
								}

								if(i == 6)
									i = 14;
								else
									i++;
							}

							SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
							SDL_RenderFillRect(renderer,&clearDestRect);

							msgDestRect.x = 310;
							msgDestRect.y = 300;

							if(j1->tab[16] > j2->tab[16])
								sprintf(msg_fin,"Le joueur %s a gagné avec %d points !",j1->nom,j1->tab[16]);
							else if(j1->tab[16] < j2->tab[16])
								sprintf(msg_fin,"Le joueur %s a gagné avec %d points !",j2->nom,j2->tab[16]);
							else
								sprintf(msg_fin,"Egalité !");

							msg = TTF_RenderUTF8_Blended(police_jeu, msg_fin, blanc);
							if(!msg){
								fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
								exit(EXIT_FAILURE);
							}

							SDL_Texture *msg_tex = SDL_CreateTextureFromSurface(renderer, msg);
							if(!msg_tex){
								fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
								exit(EXIT_FAILURE);
							}

							SDL_QueryTexture(msg_tex, NULL, NULL, &(msgDestRect.w), &(msgDestRect.h));
							SDL_RenderCopy(renderer, msg_tex, NULL, &msgDestRect);

							SDL_RenderPresent(renderer);
						}
					break;

					case SDL_MOUSEBUTTONDOWN:

						if(!fin_de_partie(j1) || !fin_de_partie(j2)){

							if(ptj == &j1){

								if(e.motion.x > 575 && e.motion.x < 675 && e.motion.y > 500 && e.motion.y < 550 && cpt_lancer < 3){

									SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
									SDL_RenderFillRect(renderer,&j_courantDestRect);

									j_courantDestRect.x = 620;

									sprintf(score,"%s",(*ptj)->nom);
									j_courant = TTF_RenderUTF8_Blended(police_jeu, score, blanc);
									if(!j_courant){
										fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
										exit(EXIT_FAILURE);
									}

									SDL_Texture *j_courant_tex = SDL_CreateTextureFromSurface(renderer, j_courant);
									if(!j_courant_tex){
										fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
										exit(EXIT_FAILURE);
									}

									SDL_QueryTexture(j_courant_tex, NULL, NULL, &(j_courantDestRect.w), &(j_courantDestRect.h));
									SDL_RenderCopy(renderer, j_courant_tex, NULL, &j_courantDestRect);

									imgDestRect.x = img2DestRect.x = 400;
					 				imgDestRect.y = 300;
									img2DestRect.y = 600;

									for(i = 0; i < 5; i++){
										if(de_pos[i] == 0 || cpt_lancer == 0){
											lancer(*ptj,i);
											switch((*ptj)->des[i]){
												case 1:
													de_courant = de1;
												break;
												case 2:
													de_courant = de2;
												break;
												case 3:
													de_courant = de3;
												break;
												case 4:
													de_courant = de4;
												break;
												case 5:
													de_courant = de5;
												break;
												case 6:
													de_courant = de6;
												break;
											}
											switch(i){
												case 0:
													SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
													SDL_RenderFillRect(renderer,&img2DestRect);
								 					image_texde1 = SDL_CreateTextureFromSurface(renderer, de_courant);
													if(!image_texde1){
														fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
														exit(EXIT_FAILURE);
													}
								 					SDL_QueryTexture(image_texde1, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								 					SDL_RenderCopy(renderer, image_texde1, NULL, &imgDestRect);
													de_pos[i] = 0;
												break;
												case 1:
													SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
													SDL_RenderFillRect(renderer,&img2DestRect);
								 					image_texde2 = SDL_CreateTextureFromSurface(renderer, de_courant);
													if(!image_texde2){
														fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
														exit(EXIT_FAILURE);
													}
													SDL_QueryTexture(image_texde2, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								 					SDL_RenderCopy(renderer, image_texde2, NULL, &imgDestRect);
													de_pos[i] = 0;
												break;
												case 2:
													SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
													SDL_RenderFillRect(renderer,&img2DestRect);
								 					image_texde3 = SDL_CreateTextureFromSurface(renderer, de_courant);
													if(!image_texde3){
														fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
														exit(EXIT_FAILURE);
													}
													SDL_QueryTexture(image_texde3, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								 					SDL_RenderCopy(renderer, image_texde3, NULL, &imgDestRect);
													de_pos[i] = 0;
												break;
												case 3:
													SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
													SDL_RenderFillRect(renderer,&img2DestRect);
								 					image_texde4 = SDL_CreateTextureFromSurface(renderer, de_courant);
													if(!image_texde4){
														fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
														exit(EXIT_FAILURE);
													}
								 					SDL_QueryTexture(image_texde4, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								 					SDL_RenderCopy(renderer, image_texde4, NULL, &imgDestRect);
													de_pos[i] = 0;
												break;
												case 4:
													SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
													SDL_RenderFillRect(renderer,&img2DestRect);
								 					image_texde5 = SDL_CreateTextureFromSurface(renderer, de_courant);
													if(!image_texde5){
														fprintf(stderr, "Erreur à la création du rendu de l'image : %s\n", SDL_GetError());
														exit(EXIT_FAILURE);
													}
													SDL_QueryTexture(image_texde5, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								 					SDL_RenderCopy(renderer, image_texde5, NULL, &imgDestRect);
													de_pos[i] = 0;
												break;
											}
										}
										imgDestRect.x += 100;
										img2DestRect.x += 100;
									}
									msgDestRect.x = 375;
									msgDestRect.y = 200;

									msg = TTF_RenderUTF8_Blended(police_score, "Veuillez choisir une case a remplir ou selectionner les des a relancer", blanc);
									if(!msg){
										fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
										exit(EXIT_FAILURE);
									}

									SDL_Texture *msg_tex = SDL_CreateTextureFromSurface(renderer, msg);
									if(!msg_tex){
										fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
										exit(EXIT_FAILURE);
									}

									SDL_QueryTexture(msg_tex, NULL, NULL, &(msgDestRect.w), &(msgDestRect.h));
									SDL_RenderCopy(renderer, msg_tex, NULL, &msgDestRect);

									j_choix = test_mains(*ptj,j_choix);

									scoreDestRect.x = 202;
									caseDestRect.x = 184;
									caseDestRect.y = scoreDestRect.y = 80;

									for(i = 0; i < 14; i++){

										if(i == 6){
											caseDestRect.y = (scoreDestRect.y += 48);
										}

										else{

											if((*ptj)->tab[i] == VAL_INIT){
												SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
												SDL_RenderFillRect(renderer,&caseDestRect);
												if(j_choix->tab[i] != VAL_INIT){

													sprintf(score,"%d",j_choix->tab[i]);
													caseJ = TTF_RenderUTF8_Blended(police_score, score, rouge);
													if(!caseJ){
													fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
														exit(EXIT_FAILURE);
													}

													caseJ_tex = SDL_CreateTextureFromSurface(renderer, caseJ);
													if(!caseJ_tex){
														fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
														exit(EXIT_FAILURE);
													}

													SDL_QueryTexture(caseJ_tex, NULL, NULL, &(scoreDestRect.w), &(scoreDestRect.h));
													SDL_RenderCopy(renderer, caseJ_tex, NULL, &(scoreDestRect));
												}
											}
										}
										caseDestRect.y = (scoreDestRect.y += 29);
									}

									SDL_RenderPresent(renderer);
									cpt_lancer++;


								}

								clic_borneG_x = 400;
								clic_borneD_x = 450;

								for(i = 0; i < 5; i++){

									if(e.motion.x > clic_borneG_x && e.motion.x < clic_borneD_x && e.motion.y > 300 && e.motion.y < 350 && de_pos[i] == 0){

										imgDestRect.x = clic_borneG_x;
										imgDestRect.y = 300;

				          				SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
										SDL_RenderFillRect(renderer,&imgDestRect);

				 						imgDestRect.y = 600;

										SDL_QueryTexture(*pt_image_texde[i], NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
										SDL_RenderCopy(renderer, *pt_image_texde[i], NULL, &imgDestRect);
										SDL_RenderPresent(renderer);

										de_pos[i] = 1;
									}

									else if(e.motion.x > clic_borneG_x && e.motion.x < clic_borneD_x && e.motion.y > 600 && e.motion.y < 650 && de_pos[i] == 1){

										imgDestRect.x = clic_borneG_x;
										imgDestRect.y = 600;

				            			SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
										SDL_RenderFillRect(renderer,&imgDestRect);

				 						imgDestRect.y = 300;

										SDL_QueryTexture(*pt_image_texde[i], NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
										SDL_RenderCopy(renderer, *pt_image_texde[i], NULL, &imgDestRect);
										SDL_RenderPresent(renderer);

										de_pos[i] = 0;
									}

									clic_borneG_x += 100;
									clic_borneD_x += 100;
								}

								scoreDestRect.x = 202;
								caseDestRect.x = 184;
								caseDestRect.y = scoreDestRect.y = 80;

								clic_borneG_x = caseDestRect.x;
								clic_borneD_x = 233;
								clic_borneS_y = 80;
								clic_borneI_y = 107;

								coup = 0;
								p = 0;

								while(p < 14 && coup == 0){

									if(p == 6){
										clic_borneS_y += 48;
										clic_borneI_y += 48;
										scoreDestRect.y += 48;
									}
									else{

										if(e.motion.x > clic_borneG_x && e.motion.x < clic_borneD_x && e.motion.y > clic_borneS_y && e.motion.y < clic_borneI_y && cpt_lancer != 0 && j1->des[0] != 0 && (*ptj)->tab[p] == VAL_INIT){

											if(j_choix->tab[p] == VAL_INIT)
												(*ptj)->tab[p] = 0;
											else
												(*ptj)->tab[p] = j_choix->tab[p];

											for(int i = 0; i < 14; i++){
												if(i == 7)
													caseDestRect.y += 48;

												if((*ptj)->tab[i] == VAL_INIT){
													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderFillRect(renderer,&caseDestRect);
												}

												caseDestRect.y += 29;
											}

											sprintf(score,"%d",(*ptj)->tab[p]);
											caseJ = TTF_RenderUTF8_Blended(police_score, score, noir);
											if(!caseJ){
											fprintf(stderr, "Erreur à la création du texte : %s\n", SDL_GetError());
												exit(EXIT_FAILURE);
											}

											caseJ_tex = SDL_CreateTextureFromSurface(renderer, caseJ);
											if(!caseJ_tex){
												fprintf(stderr, "Erreur à la création du rendu du texte : %s\n", SDL_GetError());
												exit(EXIT_FAILURE);
											}

											SDL_QueryTexture(caseJ_tex, NULL, NULL, &(scoreDestRect.w), &(scoreDestRect.h));
											SDL_RenderCopy(renderer, caseJ_tex, NULL, &(scoreDestRect));

											SDL_SetRenderDrawColor(renderer, 55, 99, 78, 255);
											SDL_RenderFillRect(renderer,&clearDestRect);

											SDL_RenderPresent(renderer);

											cpt_lancer = 0;
											coup = 1;

											if(ptj == &j1)
												ptj = &j2;

										}
									}

									scoreDestRect.y += 29;
									clic_borneS_y += 29;
									clic_borneI_y += 29;
									p++;

								}
							}
						}

					break;

				}
			}
		}
	}
	else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}
	SDL_FreeSurface(caseJ);

	SDL_FreeSurface(de1); /* on a la texture, plus besoin de l'image */
	SDL_FreeSurface(de2); /* on a la texture, plus besoin de l'image */
	SDL_FreeSurface(de3); /* on a la texture, plus besoin de l'image */
	SDL_FreeSurface(de4); /* on a la texture, plus besoin de l'image */
	SDL_FreeSurface(de5); /* on a la texture, plus besoin de l'image */
	SDL_FreeSurface(de6); /* on a la texture, plus besoin de l'image */

	/* Destruction de la fenetre */
	SDL_DestroyWindow(pWindow);

	TTF_CloseFont(police_score); /* Doit être avant TTF_Quit() */
	TTF_CloseFont(police_jeu);
	TTF_Quit();
  	SDL_Quit();

    return 0;
}