#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
#include "Corsaire.h"
#include "Boucanier.h"
#include "Flibustier.h"
#include "Tresor.h"

using namespace std;
using namespace sf;

class Case
{
private:
	Personne* PersonneActuelle;
	Tresor* TresorDeLile;
	Pelle* PelleParTerre;
	Mousquet* MousquetParTerre;
	Armure* ArmureParTerre;

	int m_x, m_y;
	Texture m_texture;
	Sprite m_sprite;

public:

	Case();
	~Case();

	void SetX(int);
	int GetX();
	void SetY(int);
	int GetY();
	void SetPosition(int, int);
	Sprite* GetSprite();
	void SetPersonne(Personne*);
	void SetObjet(Objet*);
	void SetPelle(Pelle*);
	void SetMousquet(Mousquet*);
	void SetArmure(Armure*);
	Pelle* GetPelle();
	Mousquet* GetMousquet();
	Armure* GetArmure();
	Personne* GetPersonne();
	void AddTresor();
	Tresor* GetTresor();
};

