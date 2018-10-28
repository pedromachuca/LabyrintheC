#include "fonctions.h"
#include "librairies.h"

int main(int argc, char *argv[]){
	srand(time(NULL));
	LABYRINTHE *LAB =(LABYRINTHE *)malloc(sizeof(LABYRINTHE));
	FILE *FIC =NULL;
	int choix=MENU();
	if(choix==1){
		INIT_LAB(LAB, 10,10);
		INIT_ALEA_LAB(LAB);
		//FIC = fopen("Labyrinthe.txt","w+");
		//ECRIT_LAB_DS_FIC(LAB, FIC);
	}
	else{
		FIC = fopen("Labyrinthe.txt","r");
		INIT_LAB_VIA_FIC(LAB, FIC);
	}
	system("clear");
	printf("\033[1;1H");
	printf("LABYRINTHE :\n");
	AFFICHE_LAB(LAB);
	//CHEMINQCQ(LAB);
	//system("setterm --cursor off");
	int test=RP(LAB);
	if(test==0){
		printf("PAS DE CHEMIN");
	}
	else{
		printf("CHEMIN trouve\n");
	}
	LIB_LAB(LAB);
	if(choix!=1){
		fclose(FIC);
	}
}
