#include "Case.h"



Case::Case()
{
	m_x = 0;
	m_y = 0;

	m_texture.loadFromFile("assets/tiles.png",IntRect(32,32,16,16));
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_x, m_y);
}


Case::~Case()
{
	delete PersonneActuelle;
	delete TresorDeLile;
	delete PelleParTerre;
	delete MousquetParTerre;
	delete ArmureParTerre;
}

void Case::SetX(int x)
{
	m_x = x;
	m_sprite.setPosition(m_x, m_y);
}

int Case::GetX()
{
	return m_x;
}

void Case::SetY(int y)
{
	m_y = y;
	m_sprite.setPosition(m_x, m_y);
}

int Case::GetY()
{
	return m_y;
}

void Case::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
	m_sprite.setPosition(m_x, m_y);
}

Sprite * Case::GetSprite()
{
	return &m_sprite;
}

void Case::SetPersonne(Personne* personne_actuelle)
{
	PersonneActuelle = personne_actuelle;
}

void Case::SetObjet(Objet * objet)
{
	if (objet->Type() == "Pelle")
		PelleParTerre = (Pelle*)objet;
	else if (objet->Type() == "Mousquet")
		MousquetParTerre = (Mousquet*)objet;
	else if (objet->Type() == "Armure")
		ArmureParTerre = (Armure*)objet;
}

void Case::SetPelle(Pelle * pelle)
{
	PelleParTerre = pelle;
}

void Case::SetMousquet(Mousquet * mousquet)
{
	MousquetParTerre = mousquet;
}

void Case::SetArmure(Armure * armure)
{
	ArmureParTerre = armure;
}

Pelle * Case::GetPelle()
{
	return PelleParTerre;
}

Mousquet * Case::GetMousquet()
{
	return MousquetParTerre;
}

Armure * Case::GetArmure()
{
	return ArmureParTerre;
}

Personne * Case::GetPersonne()
{
	return PersonneActuelle;
}

void Case::AddTresor()
{
	TresorDeLile = new Tresor;
}

Tresor * Case::GetTresor()
{
	return TresorDeLile;
}
