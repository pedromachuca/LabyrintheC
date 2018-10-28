#include "fonctions.h"
#include "librairies.h"

int main(int argc, char *argv[]){
	srand(time(NULL));
	LABYRINTHE *LAB =(LABYRINTHE *)malloc(sizeof(LABYRINTHE));
	FILE *FIC =NULL;
	int choix=MENU();
	if(choix==1){
		INIT_LAB(LAB, 4,4);
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
	LIB_LAB(LAB);
	CHEMINQCQ(LAB);
	system("setterm --cursor off");
	//char c;
	//scanf("%c", &c);
	//while(c !='q'){
	//}
	fclose(FIC);
}
