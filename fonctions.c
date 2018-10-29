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
			else if(j==LAB->nbcol-1){
				unsigned short prebas=((LAB->lab[i-1][j]>>1)&1);
				unsigned short predroite=((LAB->lab[i][j-1]>>2)&1);
				if(prebas==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^8);
				}
				if(predroite==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^1);
				}
				int r1 =rand()%2;
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
			else if(i==(LAB->nbl-1)){
				unsigned short predroite = (LAB->lab[i][j-1]>>2)&1;
				unsigned short prebas = (LAB->lab[i-1][j]>>1)&1;
				if(predroite==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^1);
				}
				if(prebas==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^8);
				}
				int r3=rand()%2;
				if(r3==0){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^4);
				}
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
				if(predroite3==1||prebas3==1){
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^2);
					LAB->lab[i][j]=(unsigned short)(LAB->lab[i][j]^4);
				}
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
explorer(graphe G, sommet s)
	marquer le sommet s
		afficher(s)
	pour tout sommet t fils du sommet s
		si t n'est pas marqué alors
			explorer(G, t);
*/
int RP(LABYRINTHE *LAB){

	int ret=0;
	if((LAB->posXChercheur==LAB->psortieX)&&(LAB->posYChercheur==LAB->psortieY)){
		return 1;
	}
	LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<4);
		positionEtoile(LAB->posXChercheur, LAB->posYChercheur);

	positionCurseur(LAB->pentreeX, LAB->pentreeY);
	system("sleep 1");

	//mur en bas
	if((((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>1)&1)==0)&&(((LAB->lab[LAB->posXChercheur+1][LAB->posYChercheur]>>4)&1)==0)){
		positionEtoile(LAB->posXChercheur, LAB->posYChercheur);
		LAB->posXChercheur+=1;
		positionCurseur(LAB->posXChercheur, LAB->posYChercheur);
		system("sleep 1");
		ret=RP(LAB);
		LAB->posXChercheur-=1;
		if(ret==1){
			return 1;
		}
	}
	//mur a droite
	if((((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>2)&1)==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur+1]>>4)&1)==0)){
		positionEtoile(LAB->posXChercheur, LAB->posYChercheur);
		LAB->posYChercheur+=1;
		positionCurseur(LAB->posXChercheur, LAB->posYChercheur);
		system("sleep 1");
		ret=RP(LAB);
		LAB->posYChercheur-=1;
		if(ret==1){
			return 1;
		}
	}
	//mur en haut
	if((((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>3)&1)==0)&&(((LAB->lab[LAB->posXChercheur-1][LAB->posYChercheur]>>4)&1)==0)){
		positionEtoile(LAB->posXChercheur, LAB->posYChercheur);
		LAB->posXChercheur-=1;
		positionCurseur(LAB->posXChercheur, LAB->posYChercheur);
		system("sleep 1");
		ret=RP(LAB);
		LAB->posXChercheur+=1;
		if(ret==1){
			return 1;
		}
	}
	//mur a gauche
	if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&1)==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur-1]>>4)&1)==0)){
		LAB->posYChercheur-=1;
		positionCurseur(LAB->posXChercheur, LAB->posYChercheur);
		system("sleep 1");
		ret=RP(LAB);
		LAB->posYChercheur+=1;
		if(ret==1){
			return 1;
		}
	}
	return 0;
}
void positionCurseur(int l, int col){
	l = (l*2)+2;
	col =(col*4)+2;
	char *emot ="😀";

	printf("\033[%d;%dH", l, col);
	printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
	fflush(stdout);
}
void positionEtoile(int l, int col){
	l = (l*2)+2;
	col =(col*4)+2;
	printf("\033[%d;%dH", l, col);
	printf("\e[38;2;255;0;0m *\e[0m");
	fflush(stdout);
}
/*
void CHEMINQCQ(LABYRINTHE *LAB){
	char *emot ="😀";
	int goX=2;
	int goY=2;
	int godroite=0;
	while((LAB->posXChercheur!=LAB->psortieX)||(LAB->posYChercheur!=LAB->psortieY)){
		if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<1))==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0)){
			LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<4);
			system("sleep 1");
			printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
			printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		}
		else if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<2))==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0)){
			godroite=0;
			LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<5);
	if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>4)&1)==0){
		system("sleep 1");
		printf("\033[%d;%dH", (LAB->posXChercheur), (LAB->posYChercheur));
		printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		RP(LAB);
		return 1;
	}
	printf("\033[40;40H");
	printf("posX1 %d\n",LAB->posXChercheur);
	printf("posY1 %d\n",LAB->posYChercheur);
	return 0;
}

void CHEMINQCQ(LABYRINTHE *LAB){
	char *emot ="😀";
	int goX=2;
	int goY=2;
	int godroite=0;
	while((LAB->posXChercheur!=LAB->psortieX)||(LAB->posYChercheur!=LAB->psortieY)){
		if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<1))==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0)){
			LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<4);
			system("sleep 1");
			printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
			printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		}
		else if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<2))==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0)){
			godroite=0;
			LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<5);
	if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>4)&1)==0){
		system("sleep 1");
		printf("\033[%d;%dH", (LAB->posXChercheur), (LAB->posYChercheur));
		printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		RP(LAB);
		return 1;
	}
	printf("\033[40;40H");
	printf("posX1 %d\n",LAB->posXChercheur);
	printf("posY1 %d\n",LAB->posYChercheur);
	return 0;
}
void CHEMINQCQ(LABYRINTHE *LAB){
	char *emot ="😀";
	int goX=2;
	int goY=2;
	int godroite=0;
	while((LAB->posXChercheur!=LAB->psortieX)||(LAB->posYChercheur!=LAB->psortieY)){
		if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<1))==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0)){
			LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<4);
			system("sleep 1");
			printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
			printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		}
		else if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<2))==0)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0)){
			godroite=0;
			LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<5);
			system("sleep 1");
			printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
			printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		}
		else{
			LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<6);
			system("sleep 1");
			printf("\033[%d;%dH", (LAB->posXChercheur+goX), (LAB->posYChercheur+goY));
			printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		}
		if((((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>4)&1)==1)&&((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0){
			goX+=1;
			LAB->posXChercheur=LAB->posXChercheur+1;
		}
		else if((((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>5)&1)==1)&&(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>6)&1)==0)){
			goY+=3;
			LAB->posYChercheur=LAB->posYChercheur+1;
		}
		else{
			godroite=1;
			goX-=1;
			goY+=3;
			LAB->posXChercheur=LAB->posXChercheur-1;
			LAB->posYChercheur=LAB->posYChercheur+1;
		}
		printf("posX %d", LAB->posXChercheur);
		printf("posY %d", LAB->posYChercheur);
	}
}


int RP(LABYRINTHE *LAB){
	char *emot ="😀";
//	printf("\033[%d;%dH", (LAB->pentreeX+3), (LAB->pentreeY+2));
//	printf("\e[38;2;255;0;0m %s\e[0m",emot);
//	printf("\n");
	int initX=2;
	int initY=2;
	if((LAB->posXChercheur==LAB->psortieX)&&(LAB->posYChercheur==LAB->psortieY)){
		return 1;
	}
	//ICI on va faire si pas de mur case du bas on la marqe comme chemin on increment le chercheurX
	//Si il y a un mur on regarde la case de droite si pas de mur on la marque comme chemin on
	//increment chercheurY de 1
	if((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<1))==0){
	LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<4);
		system("sleep 1");
		printf("\033[%d;%dH", (LAB->posXChercheur+(*goX)), (LAB->posYChercheur+(*goY)));
		printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		printf("\033[27;27H");
		printf("posX :%d",LAB->posXChercheur);
	}
	else if((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]&(1<<2))==0){
		LAB->lab[LAB->posXChercheur][LAB->posYChercheur]=LAB->lab[LAB->posXChercheur][LAB->posYChercheur]^(1<<5);
		system("sleep 1");
		printf("\033[%d;%dH", (LAB->posXChercheur+(*goX)), (LAB->posYChercheur+(*goY)));
		printf("\e[38;2;255;0;0m %s\e[0m\n",emot);
		printf("\033[29;29H");
		printf("posY :%d",LAB->posYChercheur);
	}
	if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>4)&1)==1){
		LAB->posXChercheur=LAB->posXChercheur+1;
		printf("\033[30;30H");
		printf("posX1 :%d",LAB->posXChercheur);
		RP(LAB);
		return 1;
	}
	else if(((LAB->lab[LAB->posXChercheur][LAB->posYChercheur]>>5)&1)==1){
		LAB->posYChercheur=LAB->posYChercheur+1;
		printf("\033[33;33H");
		printf("posY1 :%d",LAB->posYChercheur);
		RP(LAB);
		return 1;
	}
	return 0;
}*/
/*
		explorer(graphe G, sommet s)
	      marquer le sommet s
		        afficher(s)
	      pour tout sommet t fils du sommet s
		              si t n'est pas marqué alors
					                     explorer(G, t);*/
	/*
/Initialistation cellule 0-15
//1111 : tous les murs ->15 
//1000 : mur haut -> 8
//0100 : mur droite->4
//0010 : mur bas ->2
//0001 : mur gauche ->1*/

