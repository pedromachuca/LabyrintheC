#include "librairies.h"
#include "fonctions.h"
//TO DO//ALLOC_LAB_DYN(){
//}

void INIT_LAB(LABYRINTHE * LAB, int nbltmp, int nbcoltmp){
	LAB->nbl=nbltmp;
	LAB->nbcol=nbcoltmp;
	//Allocation tab 2D:
	int i, j;
	LAB->lab=malloc((LAB->nbl)*sizeof(unsigned short int *));
	for(i=0; i<LAB->nbl; i++){
		LAB->lab[i]=malloc((LAB->nbcol)*sizeof(unsigned short int));
	}
	int count = 0;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			LAB->lab[i][j]=count;
			count++;
		}
	}
	LAB->pentreeX =0;
	LAB->pentreeY=0;
	LAB->psortieX=9;
	LAB->psortieY=9;
	LAB->posXChercheur=LAB->pentreeX;
	LAB->posYChercheur=LAB->pentreeY;
}

void AFFICHE_LAB(LABYRINTHE *LAB){
	int i,j;
	printf("────────────────────────────────────────\n");
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			printf("▏%2d ", LAB->lab[i][j]);
		}
		printf("▏\n");
		printf("────────────────────────────────────────\n");
	}
}
void INIT_ALEA_LAB(LABYRINTHE *LAB){
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			LAB->lab[i][j]=(rand()%15)+1;
		}
	}
}
void LIB_LAB(LABYRINTHE *LAB){
	int i;
	for(i=0; i<LAB->nbl; i++){
		free(LAB->lab[i]);
		LAB->lab[i]=NULL;
	}
	free(LAB->lab);
	LAB->lab=NULL;
	free(LAB);
	LAB=NULL;
}
void AFFICHE_LAB_DS_FIC(LABYRINTHE *LAB, FILE * FIC){
	fprintf(FIC, "%d %d %d %d %d %d\n", LAB->nbl, LAB->nbcol, LAB->pentreeX, LAB->pentreeY, LAB->psortieX, LAB->psortieY);
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			fprintf(FIC, "%d ", LAB->lab[i][j]);
		}
		fprintf(FIC, "\n");
	}
}


//Initialistation cellule 0-15
/*
1111 : tous les murs ->15 
0001 : mur droit ->1
0010 : mur haut ->2
0100 : mur bas ->4
1000 : mur gauche ->8
	   
*/
/*
VEHICULE * INIT_VEHICULE_AVEC_POINTEUR_2(){
	VPOINT V =(VPOINT)malloc(sizeof(VEHICULE));
	int randomInt = (rand() % (5 - 1)) + 1;
	switch(randomInt){
		case 1:
			strcpy((*V).marque, "tata");
			break;
		case 2:
			strcpy((*V).marque, "toyota");
			break;
		case 3:
			strcpy((*V).marque, "lada");
			break;
		case 4:
			strcpy((*V).marque, "peugot");
			break;
		case 5:
			strcpy((*V).marque, "bmw");
			break;
		default:
			break;
	}	
	int randomInt2 = (rand() % (700 - 100)) + 100;
	(*V).puissance = randomInt2;
	int randomInt3 = (rand() % (400 - 180)) + 180;
	(*V).vitesse_max= randomInt3;
	return V;
}
void AFFICHE_VEHICULE_AVEC_POINTEUR(VEHICULE *V){
	printf("Marque : %s \nPuissance : %d CH\nVitesse_Max :%d km\\h\n\n", (*V).marque,(*V).puissance,(*V).vitesse_max);
}
//Partie C : Tri a bulle
VEHICULE *ALLOC_TAB_VEH_DYN(int N){
	VPOINT V =(VPOINT)malloc(N*sizeof(VEHICULE));
	return V;
}
void TRI_A_BULLES(VEHICULE *mesvehicules, int N){
	VPOINT temp=ALLOC_TAB_VEH_DYN(1);
	int estTriee=0;
	do{
		estTriee=1;
		for(int i=0; i<10; i++){
			if(mesvehicules[i].puissance >mesvehicules[i+1].puissance){
				temp[i] = mesvehicules[i];
				mesvehicules[i] = mesvehicules[i+1];
				mesvehicules[i+1] = temp[i];
				estTriee=0;
			}
		}
	}while(estTriee==0);
		//printf("vehicule 1 :%d, 2:%d\n ",mesvehicules[0].puissance, mesvehicules[1].puissance);
		printf("vehicule 1 :%d, 2:%d\n ",mesvehicules->puissance,(mesvehicules+1)->puissance);
}
//Partie D : Liste chainée de véhicule
LISTE * CREATION_LISTE(){
	LISTE *l1=(LISTE*)malloc(sizeof(LISTE));
	return l1;
}
void INIT_LISTE(LISTE *L){
	L->taille=0;
	L->debut=NULL;
	L->fin=NULL;
}
*/
