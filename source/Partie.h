#pragma once
#include "Affichage.h"
#include "Plateau.h"
#include <sstream>
#include <fstream>
#include "SFML\Audio.hpp"

class Partie
{
private:
	Affichage* Fenetre;

	Plateau m_ile;
	Font m_font;
	Text* m_txtInfo;
	Text* m_txtEquipement;
	Text* m_txtChoixAction;

	Music m_musique;

	int m_nombrePirate = 0;
	int m_nombreCorsaire = 0;
	int m_tourDeJeu = 0;
	float m_vitessePartie = 500.0;

	enum eChoixCorsaire
	{
		AUCUN, DEPLACER, CREUSER, TIRER
	};
	eChoixCorsaire m_choixCorsaire = eChoixCorsaire::AUCUN;

public:
	Partie(Affichage*);
	~Partie();

	bool MenuPrincipal();
	bool ChoixMode();
	void Informations();
	void InitJeu();
	void EnJeu();
	bool MiseAJourEnJeu(bool);
	void MiseAJourTourDeJeu( int);
	bool EvenementsClavier(Event*, int);
	int Clignotement(int);
	void AttendreChar();
	void Attendre(float);
	void Sauvegarder();
	void Charger();
};

