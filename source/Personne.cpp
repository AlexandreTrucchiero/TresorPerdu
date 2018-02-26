#include "Personne.h"



Personne::Personne()
{
}


Personne::~Personne()
{
}


Sprite * Personne::GetSprite()
{
	return &m_sprite;
}

bool Personne::GetEnVie()
{
	return m_enVie;
}
