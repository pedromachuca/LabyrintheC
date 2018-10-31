#include "fonctions.h"
#include "librairies.h"

int main(int argc, char *argv[]){
	int valid=0;
	int cheminExiste=0;
	int coherence=0;
	int affichage=0;

	srand(time(NULL));
	LABYRINTHE *LAB =(LABYRINTHE *)malloc(sizeof(LABYRINTHE));
	FILE *FIC =NULL;

	int choix=MENU();
	if(choix==1){

		INIT_LAB(LAB);

		while(valid==0){	

			INIT_ALEA_LAB(LAB);
			valid=RP(LAB, affichage);
		}

		REINIT(LAB);
		FIC = fopen("Labyrinthe.txt","w+");
		ECRIT_LAB_DS_FIC(LAB, FIC);
	}
	else{
		FIC = fopen("Labyrinthe.txt","r");
		INIT_LAB_VIA_FIC(LAB, FIC);
		coherence=VERIF_COHERENCE(LAB);
		if(coherence!=0){
			printf("Labyrinthe non coherent !! \n");
			printf("Exiting the program \n");
			return EXIT_SUCCESS;
		}
	}
	system("clear");
	printf("\033[1;1H");
	AFFICHE_LAB(LAB);
	AFFICHE_ENTREE(LAB);
	AFFICHE_SORTIE(LAB);
	system("sleep 1");
	system("setterm --cursor off");
	affichage=1;
	cheminExiste=RP(LAB, affichage);
	if(cheminExiste==0){
   		printf("\033[%d;%dH", ((LAB->nbl*2)+4), 0);
		printf("PAS DE CHEMIN\n");
	}
	else{
   		printf("\033[%d;%dH", ((LAB->nbl*2)+4), 0);
		printf("CHEMIN TROUVEE\n");
	}
	LIB_LAB(LAB);
	fclose(FIC);
	system("setterm --cursor on");
	return EXIT_SUCCESS;
}
