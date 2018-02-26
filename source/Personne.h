#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Personne
{
protected:
	bool m_enVie = true;
	Texture m_texture;
	Sprite m_sprite;

public:
	enum eDirection
	{
		HAUT, BAS, GAUCHE, DROITE
	};

	Personne();
	~Personne();
	
	virtual bool Attaquer(int) = 0;
	virtual string Type() = 0;
	virtual int ChanceSurvie() = 0;

	Sprite* GetSprite();
	bool GetEnVie();
};
