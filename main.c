#include "fonctions.h"
#include "librairies.h"

int main(int argc, char *argv[]){
	srand(time(NULL));
	LABYRINTHE *LAB =(LABYRINTHE *)malloc(sizeof(LABYRINTHE));
	INIT_LAB(LAB, 10, 10);
	AFFICHE_LAB(LAB);
	printf("TABLEAU ALEATOIRE :\n");
	INIT_ALEA_LAB(LAB);
	AFFICHE_LAB(LAB);
	FILE * FIC = fopen("Labyrinthe.txt","w+");
	AFFICHE_LAB_DS_FIC(LAB, FIC);
	LIB_LAB(LAB);
	fclose(FIC);
}
