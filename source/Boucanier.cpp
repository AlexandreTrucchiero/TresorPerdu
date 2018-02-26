#include "Boucanier.h"



Boucanier::Boucanier()
{
	srand(time(NULL));

	if (!m_texture.loadFromFile("assets/characters.png", IntRect(32 * 2, 0, 32, 32)))
		exit(1);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
	m_sprite.setScale(0.5, 0.5);
}


Boucanier::~Boucanier()
{
}

bool Boucanier::Attaquer(int chance_cible)
{
	int roll = 0;

	roll = rand() % 101;

	if (chance_cible >= roll)
		m_enVie = false;
	else
		m_enVie = true;

	return m_enVie;
}

string Boucanier::Type()
{
	return "Boucanier";
}

int Boucanier::ChanceSurvie()
{
	return NULL;
}
