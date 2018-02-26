#pragma once
#include <vector>
#include "Case.h"

class Plateau
{
private:
	Case m_tabCase[12][12];
	int m_tailleCase = 16;
	string m_str_info = "...";
	string m_str_equipement = "...";
	bool m_attendre = false;
	int m_eraseIndex = 666;

	Texture m_tOcean;
	Sprite m_sOcean;

	vector<Personne*> vectPersonne;
	vector<Objet*> vectObjet;
public:
	enum eDirection
	{
		HAUT, BAS, GAUCHE, DROITE, HG, HD, BG, BD
	};

	Plateau();
	~Plateau();

	void AjouterPersonne(Personne*, Case*);
	void AjouterObjet(Objet*, Case*);
	bool DeplacerCorsaire(int, Plateau::eDirection);
	bool DeplacerPirate(int);
	bool Deplacement(int, int, int, int, int);
	void Duel(bool, int, int, int, int, int);
	bool CheckCaseActuelle(int);
	bool CheckCasesAutour(int);
	bool Tirer(int, Plateau::eDirection);
	void CheckTresor(int);

	Sprite* GetOceanSprite();
	Case* GetCase(int, int);
	vector<Personne*> GetVectPersonne();
	Personne* GetPersonne(int);
	void SetInfo(string);
	string GetInfo();
	string GetEquipement(int);
	void SetAttendre(bool);
	bool GetAttendre();
	void SetEraseIndex(int);
	int GetEraseIndex();
};

