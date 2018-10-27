#include "fonctions.h"
#include "librairies.h"

int main(int argc, char *argv[]){
	srand(time(NULL));
	LABYRINTHE *LAB =(LABYRINTHE *)malloc(sizeof(LABYRINTHE));
	INIT_LAB(LAB, 4,4);
	//AFFICHE_LAB(LAB);
	//printf("TABLEAU ALEATOIRE :\n");
	INIT_ALEA_LAB(LAB);
	//AFFICHE_LAB(LAB);
	//FILE * FIC = fopen("Labyrinthe.txt","w+");
	//ECRIT_LAB_DS_FIC(LAB, FIC);
	//FILE * FIC = fopen("Labyrinthe.txt","r");
	//INIT_LAB_VIA_FIC(LAB, FIC);
	system("clear");
	printf("\033[1;1H");
	AFFICHE_LAB(LAB);
	//AFFICHE_CASE_HAUT(LAB);
	//AFFICHE_CASE_GAUCHE(LAB);
	//AFFICHE_CASE_DROITE(LAB);
	LIB_LAB(LAB);
	char c;
	scanf("%c", &c);
	while(c !='q'){
	}
//	fclose(FIC);
}
