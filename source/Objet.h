#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Objet
{
protected:
	int m_x, m_y;
	Texture m_texture;
	Sprite m_sprite;
	bool m_dansUnCoffre = true;

public:
	Objet();
	~Objet();

	virtual string Type() = 0;
	void SetPosition(int, int);
	Sprite* GetSprite();
	void SetDansUnCoffre(bool);
	bool GetDansUnCoffre();
	void SetEnBonEtat(bool);
	bool GetEnBonEtat();
};

