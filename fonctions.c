#include "librairies.h"
#include "fonctions.h"

void INIT_LAB(LABYRINTHE * LAB, int nbltmp, int nbcoltmp){
	LAB->nbl=nbltmp;
	LAB->nbcol=nbcoltmp;
	//Allocation tab 2D:
	int i, j;
	LAB->lab=malloc((LAB->nbl)*sizeof(unsigned short *));
	for(i=0; i<LAB->nbl; i++){
		LAB->lab[i]=malloc((LAB->nbcol)*sizeof(unsigned short));
	}
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			LAB->lab[i][j]=15;
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
			printf("▏%2hu ", LAB->lab[i][j]);
		}
		printf("▏\n");
		printf("────────────────────────────────────────\n");
	}
}
void INIT_ALEA_LAB(LABYRINTHE *LAB){
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			LAB->lab[i][j]=(unsigned short)(rand()%15)+1;
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
void ECRIT_LAB_DS_FIC(LABYRINTHE *LAB, FILE * FIC){
	fprintf(FIC, "%d %d %d %d %d %d\n", LAB->nbl, LAB->nbcol, LAB->pentreeX, LAB->pentreeY, LAB->psortieX, LAB->psortieY);
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			fprintf(FIC, "%hu ", LAB->lab[i][j]);
		}
		fprintf(FIC, "\n");
	}
}
void INIT_LAB_VIA_FIC(LABYRINTHE *LAB, FILE * FIC){
	fscanf(FIC, "%d %d %d %d %d %d", &LAB->nbl, &LAB->nbcol, &LAB->pentreeX, &LAB->pentreeY, &LAB->psortieX, &LAB->psortieY);

	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			fscanf(FIC, "%hu ", &LAB->lab[i][j]);
		}
	}
}
void AFFICHE_CASE_HAUT(LABYRINTHE *LAB){
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			unsigned short haut =((LAB->lab[i][j]>>3)&1);
			if(haut == 1){
			printf("────");
			}
		}
		printf("\n");
		printf("\n");
	}
}
void AFFICHE_CASE_GAUCHE(LABYRINTHE *LAB){
	char barre[] ="▏";
	int indice = 0;
	int indice1 = 2;
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			unsigned short gauche=(LAB->lab[i][j]&1);
			printf("\033[%d;%dH",indice1, indice);
			if(gauche == 1){
				printf("%s", barre);
			}
			indice+=4;
		}
		indice1 +=2;
		indice=0;
	}
}
void AFFICHE_CASE_DROITE(LABYRINTHE *LAB){
	char barre[] ="▏";
	int indice = 4;
	int indice1 = 2;
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			unsigned short right=((LAB->lab[0][0]>>2)&1);
			printf("\033[%d;%dH",indice1, indice);
			if(right== 1){
				printf("%s", barre);
			}
			indice+=4;
		}
		indice1 +=2;
		indice=0;
	}
}
void AFFICHE_LAB2(LABYRINTHE *LAB){
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			if(i==0){
				printf("────");
			}
			else{
				unsigned short bottom=(unsigned short)((LAB->lab[i][j]>>1)&1);
				if(bottom==1){
					printf(" ── ");
				}
			}
		}
		printf("\n");
		
		for(j=0; j<LAB->nbcol; j++){
			if(j==0){
				printf("▏%2hu ", LAB->lab[i][j]);
			}
			else{
				unsigned short gauche=(LAB->lab[i][j]&1);
				if(gauche==1){
					printf("▏%2hu ", LAB->lab[i][j]);
				}
				else{
					printf(" %2hu ", LAB->lab[i][j]);
				}
			}
		}
		printf("▏\n");
		for(j=0; j<LAB->nbcol; j++){
			if(i==LAB->nbl-1){
				printf("────");
			}
		}
	}
}
/*
		printf("▏  ");
	}
	if(right==1){
		printf("▏");
	}
	if(bottom==1){
		printf("\n───");
	}*/
//Initialistation cellule 0-15
/*
1111 : tous les murs ->15 
1000 : mur haut -> 8
0100 : mur droite->4
0010 : mur bas ->2
0001 : mur gauche ->1
		
 */	  

