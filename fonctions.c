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
}/*
void INIT_ALEA_LAB(LABYRINTHE *LAB){
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			if(i==0&&j==0){
				int liste[]={11,13};
				int r =rand()%2;
				LAB->lab[i][j]=(unsigned short)liste[r];
			}
			else if(i==0){
				if(((LAB->lab[i][j-1]>>3)&1)==1){
					LAB->lab[i][j]=(unsigned short)(12+rand()%4);
				}
				else{
					int liste1 []={8,10,12,14};
					int r1=rand()%4;
					LAB->lab[i][j]=(unsigned short)(liste1[r1]);
				}
			}
			else if(i==0&&j==LAB->nbcol-1){
				if(((LAB->lab[i][j-1]>>3)&1)==1){
					int liste2 []={13, 15};
					int r2 =rand()%2;
					LAB->lab[i][j]=(unsigned short)liste2[r2];
				}
				else{
					int liste3 []={12,14};
					int r3=rand()%2;
					LAB->lab[i][j]=(unsigned short)(liste[r3]);
				}
			}
			else if(j==0){
				if(((LAB->lab[i-1][j]>>1)&1)==1){
					int liste4 []={11, 13, 15};
					int r4=rand()%3;
					LAB->lab[i][j]=(unsigned short)(liste[r4]);
				}
				else{
					int liste5 []={1,3,5,7};
					int r5=rand()%4;
					LAB->lab[i][j]=(unsigned short)(liste[r5]);
				}
			}
			else if(i==LAB->nbl-1){

			}
			}
			else if(j==LAB->nbcol-1){
				
			}
			else{
				if(((LAB->lab[i-1][j]>>1)&1)==1){
					int liste4 []={11, 13, 15};
					int r4=rand()%3;
					LAB->lab[i][j]=(unsigned short)(liste[r4]);
				}
				else{
					int liste5 []={1,3,5,7};
					int r5=rand()%4;
					LAB->lab[i][j]=(unsigned short)(liste[r5]);
				}
				

			}

		}
//Initialistation cellule 0-15
1111 : tous les murs ->15 
1000 : mur haut -> 8
0100 : mur droite->4
0010 : mur bas ->2
0001 : mur gauche ->1

1001
}*/
void INIT_ALEA_LAB(LABYRINTHE *LAB){
	int i,j;

	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			if(i==0&&j==0){
				unsigned short liste[]={2,4};
				int r =rand()%2;
				LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^liste[r]);
			}
			else if(i==0){
				unsigned short predroite = (LAB->lab[i][j-1]>>2)&1;
				unsigned short cegauche = 8^predroite;
				LAB->lab[i][j]=(unsigned short)(cegauche+rand()%7);

			}
			else if(i==0&&j==LAB->nbcol-1){
				unsigned short predroite1 = (LAB->lab[i][j-1]>>2)&1;
				unsigned short cegauche1 = 12^predroite1;
				LAB->lab[i][j]=(unsigned short)(cegauche1+rand()%4);
			}
			else if(j==0){
				unsigned short prebas = (LAB->lab[i-1][j]>>1)&1;
				unsigned short cehaut = 1^(prebas<<3);
				LAB->lab[i][j]=(unsigned short)(cehaut+rand()%7);
				
			}
			else{
				unsigned short liste1[]={4, 2};
				unsigned short prebas1 = (LAB->lab[i-1][j]>>1)&1;
				unsigned short predroite1 = (LAB->lab[i][j-1]>>2)&1;
				LAB->lab[i][j]=LAB->lab[i][j]^prebas1^predroite1^liste1[(rand()%2)];
			}
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
void AFFICHE_LAB(LABYRINTHE *LAB){
	int i,j;
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			if(i==0){
				printf("+---");
			}
			else{
				unsigned short top=(unsigned short)((LAB->lab[i][j]>>3)&1);
				if(top==1){
					printf("+---");
				}
				else{
					printf("+   ");
				}
			}
		}
		printf("+\n");
		
		for(j=0; j<LAB->nbcol; j++){
			if(j==0){
				printf("| %2hu", LAB->lab[i][j]);
			}
			else{
				unsigned short gauche=(LAB->lab[i][j]&1);
				unsigned short droite=((LAB->lab[i][j]>>2)&1);
				if(gauche==1||droite==1){
					printf("| %2hu", LAB->lab[i][j]);
				}
				else{
					printf("  %2hu", LAB->lab[i][j]);
				}
			}
		}
		printf("|\n");
	
		for(j=0; j<LAB->nbcol; j++){
			if(i==LAB->nbl-1){
			printf("+---");
			}
		}
	}
	printf("+\n");
}

