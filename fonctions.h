#include "librairies.h"
typedef struct labyrinthe{

	unsigned short int **lab;
	int nbl;
	int nbcol;
	int pentreeX;
	int pentreeY;
	int psortieX;
	int psortieY;
	int posXChercheur;
	int posYChercheur;

}LABYRINTHE;

void INIT_LAB(LABYRINTHE *LAB, int nbl, int nbcol);
void AFFICHE_LAB(LABYRINTHE *LAB);
void INIT_ALEA_LAB(LABYRINTHE *LAB);
void LIB_LAB(LABYRINTHE *LAB);
void ECRIT_LAB_DS_FIC(LABYRINTHE *LAB, FILE * FIC);
void INIT_LAB_VIA_FIC(LABYRINTHE *LAB, FILE * FIC);


/*typedef struct voiture{
         char marque[20];
         int puissance;
         int vitesse_max;
		 struct voiture * NXT;
}VEHICULE;
typedef VEHICULE *VPOINT;

typedef struct liste{
		int taille;
		VEHICULE *debut;
		VEHICULE *fin;
}LISTE;


VEHICULE INIT_VEHICULE_SANS_POINTEUR();
void AFFICHE_VEHICULE_SANS_POINTEUR(VEHICULE V);
void INIT_VEHICULE_AVEC_POINTEUR_1(VEHICULE *V);
void AFFICHE_VEHICULE_AVEC_POINTEUR(VEHICULE *V);
VEHICULE * INIT_VEHICULE_AVEC_POINTEUR_2();
VEHICULE * ALLOC_TAB_VEH_DYN(int N);
void TRI_A_BULLES(VEHICULE *mesvehicules, int N);
LISTE *CREATION_LISTE();
void INIT_LISTE(LISTE* L);*/

