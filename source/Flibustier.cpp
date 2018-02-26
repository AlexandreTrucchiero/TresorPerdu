#include "Flibustier.h"



Flibustier::Flibustier()
{
	if (!m_texture.loadFromFile("assets/characters.png", IntRect(32 * 1, 0, 32, 32)))
		exit(1);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
	m_sprite.setScale(0.5, 0.5);
}


Flibustier::~Flibustier()
{
}

bool Flibustier::Attaquer(int chance_cible)
{
	int roll = 0;

	roll = rand() % 101;

	if (chance_cible >= roll)
		m_enVie = false;
	else
		m_enVie = true;

	return m_enVie;
}

string Flibustier::Type()
{
	return "Flibustier";
}

int Flibustier::ChanceSurvie()
{
	return NULL;
}
