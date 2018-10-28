#include "librairies.h"
typedef struct labyrinthe{

	unsigned short **lab;
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
int menu();
