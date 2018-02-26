#include "Partie.h"

int main(int argc, char* argv)
{
	Affichage* Fenetre; 

	Partie* Jeu;

	while (true)
	{
		Fenetre = new Affichage; //instance fenetre d'affichage
		Jeu = new  Partie(Fenetre); //instance jeu
		Jeu->EnJeu();	//on lance le jeu
		delete Jeu;
		delete Fenetre;
	}
}

