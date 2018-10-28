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
	LAB->psortieX=nbltmp-1;
	LAB->psortieY=nbcoltmp-1;
	LAB->posXChercheur=LAB->pentreeX;
	LAB->posYChercheur=LAB->pentreeY;
}
//Initialistation cellule 0-15
//1111 : tous les murs ->15 
//1000 : mur haut -> 8
//0100 : mur droite->4
//0010 : mur bas ->2
//0001 : mur gauche ->1
void INIT_ALEA_LAB(LABYRINTHE *LAB){
	int i,j;

	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			//xor posible sur mur bas et mur droite
			if(i==0&&j==0){
				unsigned short liste[]={2,4};
				LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^liste[0]);
				LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^liste[1]);
			}
			//xor possible sur mur bas
			//mur gauche a checker avec le mur droit précédent
			else if(i==0&&j==(LAB->nbcol-1)){
				int r1 =rand()%2;
				unsigned short predroite = (LAB->lab[i][j-1]>>2)&1;
				//si la case précédente n'a pas de mur à droite
				//alors on enlève le mur gauche de la case courante 
				if(predroite==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^1);
				}
				//on enlève le mur bas aléatoirement
				if(r1==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^2);
				}
			}
			//xor possible mur bas, mur droite
			//checker mur gauche par rapport au précédent
			else if(i==0){
				unsigned short predroite1 = (LAB->lab[i][j-1]>>2)&1;
				if(predroite1==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^1);
				}
				unsigned short liste1[]={2,4};
				int r2 =rand()%2;
				if(r2==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^liste1[r2]);
				}
				else{
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^4);
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^2);
				}

			}
			//xor possible mur droit
			//mur haut a checker avec le précédent
			else if(i==(LAB->nbl-1)&&j==0){
				unsigned short prebas = (LAB->lab[i-1][j]>>1)&1;
				if(prebas==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^8);
				}
				int r3=rand()%2;
				if(r3==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^4);
				}
			}
			//aucun xor possible
			//checker mur gauche (mur droit précédent)
			//cheker mur haut (mur bas précédent)
			else if(i==(LAB->nbl-1)&&j==(LAB->nbcol-1)){
				unsigned short predroit2 = (LAB->lab[i][j-1]>>2)&1;
				unsigned short prebas1 = (LAB->lab[i-1][j]>>1)&1;
				if(predroit2==1){
					LAB->lab[i][j-1]=(unsigned short)(LAB->lab[i][j]^4);
				}
				if(prebas1==1){
					LAB->lab[i-1][j]=(unsigned short)(LAB->lab[i][j]^2);
				}
				LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^8);
				LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^1);
			}
			//xor possible mur droit, mur bas
			//checker mur haut (mur bas précédent)
			else if(j==0){
				unsigned short prebas2 = (LAB->lab[i-1][j]>>1)&1;
				if(prebas2==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^8);
				}
				unsigned short liste2[]={2,4};
				int r4 =rand()%2;
				LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^liste2[r4]);
			}
			//xor possible mur droit mur bas
			//checker mur haut (mur bas précédent)
			//checker mur gauche (mur droit précédent)
			else{
				unsigned short liste3[]={2,4};
				unsigned short prebas3 = (LAB->lab[i-1][j]>>1)&1;
				unsigned short predroite3 = (LAB->lab[i][j-1]>>2)&1;
				if(prebas3==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^8);
				}
				if(predroite3==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^1);
				}
				int r5 =rand()%2;
				LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^liste3[r5]);
				if(predroite3==1&&prebas3==1){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^2);
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^2);
				}
			}
		}
	}
}/*
void INIT_ALEA_LAB(LABYRINTHE *LAB){
	for(i=0; i<LAB->nbl; i++){
		for(j=0; j<LAB->nbcol; j++){
			
		}
	}

}*/
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
	LAB->posXChercheur=LAB->pentreeX;
	LAB->posYChercheur=LAB->pentreeY;
	LAB->lab=malloc((LAB->nbl)*sizeof(unsigned short *));
	for(i=0; i<LAB->nbl; i++){
		LAB->lab[i]=malloc((LAB->nbcol)*sizeof(unsigned short));
	}
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
				unsigned short droite=((LAB->lab[i][j-1]>>2)&1);
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
int MENU(){
	int choix=0;
	printf("*************************************************\n");
	printf("* Bienvenue dans ce labyrinthe!                 *\n");
	printf("*                                               *\n");
	printf("* Veuillez choisir une option ci dessous:       *\n");
	printf("*                                               *\n");
	printf("* 1- Generation aléatoire d'un labyrinthe       *\n");
	printf("* 2- Chargement du labyrinthe depuis un fichier *\n");
	printf("*                                               *\n");
	printf("*************************************************\n");
 	
	printf("Veuillez entrer votre choix : ");
	scanf("%d", &choix);

	return choix;
}
/*
void verificationCoherenceFichier(){

}
 */

void CHEMINQCQ(LABYRINTHE *LAB){
	char *emot ="😀";
	printf("\033[%d;%dH", (LAB->pentreeX+3), (LAB->pentreeY+2));
	printf("\e[38;2;255;0;0m %s\e[0m",emot);
	printf("\n");
	int goX=3;
	int goY=2;
	int i,j;
	system("sleep 1");
	while(LAB->posXChercheur!=LAB->psortieX&&LAB->posYChercheur!=LAB->psortieY){
		for(i=0; i<LAB->nbl; i++){
			for(j=0; j<LAB->nbcol; j++){
				if(((LAB->lab[i][j]>>2)&1)==0){
					goY+=4;
					printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
					printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
					goY-=4;
					printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
					printf("\e[38;2;255;0;0m *\e[0m\n");
				}
				
			}

system("sleep 1");
		}	
		LAB->posXChercheur++;
		LAB->posYChercheur++;
		/*
		goX++;
		goY+=3;
		printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
		printf("\e[38;2;255;0;0m %s\e[0m",emot);
		printf("\033[35;40H");*/
	}

}

int RP(LABYRINTHE *LAB){
	if((LAB->posXChercheur==LAB->psortieX)&&(LAB->posYChercheur==LAB->psortieY)){
		return 1;
	}
	//ICI on va faire si pas de mur case du bas on la marqe comme chemin on increment le chercheurX
	//Si il y a un mur on regarde la case de droite si pas de mur on la marque comme chemin on
	//increment chercheurY de 1
	LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<4);
	if(LAB->posXChercheur<LAB->nbl-1){
		if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>4)&1)==1){
			LAB->posXChercheur=LAB->posXChercheur+1;
			RP(LAB);
			return 1;
		}
	}
	else{
		LAB->posXChercheur=LAB->pentreeX;
		if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>4)&1)==1){
			LAB->posYChercheur=LAB->posYChercheur+1;
			RP(LAB);
			return 1;
		}
	}
	return 0;
}/*
		explorer(graphe G, sommet s)
	      marquer le sommet s
		        afficher(s)
	      pour tout sommet t fils du sommet s
		              si t n'est pas marqué alors
					                     explorer(G, t);*/
	/*
	if(LAB->posXChercheur==LAB->psortieX&&LAB->posYChercheur==LAB->psortieY){
		return 1;
	}
	if(LAB->posXChercheur!=LAB->psortieX||LAB->posYChercheur!=LAB->psortieY){
		if(RP(LAB)){
			LAB->posXChercheur = LAB->posXChercheur+1;
			return 1;
		}
		if(RP(LAB)){
			LAB->posYChercheur = LAB->posYChercheur+1;
			return 1;
		}
	}*/

//}
