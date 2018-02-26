#include "Corsaire.h"



Corsaire::Corsaire()
{
	srand(time(NULL));

	if (!m_texture.loadFromFile("assets/characters.png", IntRect(0, 0, 32, 32)))
		exit(1);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);
	m_sprite.setScale(0.5, 0.5);
	
	if (!m_tObjets.loadFromFile("assets/objets.png", IntRect(0, 0, 96, 32)))
		exit(1);

	m_sPelle.setTexture(m_tObjets);
	m_sPelle.setPosition(0, 0);
	m_sPelle.setTextureRect(IntRect(32, 0, 32, 32));
	m_sPelle.setScale(0.5, 0.5);

	m_sMousquet.setTexture(m_tObjets);
	m_sMousquet.setPosition(0, 0);
	m_sMousquet.setTextureRect(IntRect(0, 0, 32, 32));
	m_sMousquet.setScale(0.5, 0.5);

	m_sArmure.setTexture(m_tObjets);
	m_sArmure.setPosition(0, 0);
	m_sArmure.setTextureRect(IntRect(64, 0, 32, 32));
	m_sArmure.setScale(0.5, 0.5);
}


Corsaire::~Corsaire()
{
	delete PelleEnStock;
	delete MousquetEnStock;
	delete ArmureEnStock;
	delete TresorEnStock;
}

bool Corsaire::Attaquer(int chance_cible)
{
	int chanceGagner = 0;
	int roll = 0;

	if (MousquetEnStock != NULL && ArmureEnStock != NULL)
		chanceGagner = 100;
	else if (MousquetEnStock != NULL)
		chanceGagner = MousquetEnStock->GetChanceSurvie();
	else if (ArmureEnStock != NULL)
		chanceGagner = ArmureEnStock->GetChanceSurvie();

	roll = rand() % 101;

	if (chanceGagner >= roll)
		m_enVie = true;
	else
		m_enVie = false;

	return m_enVie;
}

string Corsaire::Type()
{
	return "Corsaire";
}

void Corsaire::SetPelle(Pelle * pelle)
{
	PelleEnStock = pelle;
}

void Corsaire::SetMousquet(Mousquet * mousquet)
{
	MousquetEnStock = mousquet;
}

void Corsaire::SetArmure(Armure * armure)
{
	ArmureEnStock = armure;
}

void Corsaire::SetTresor(Tresor * tresor)
{
	TresorEnStock = tresor;
}

Pelle * Corsaire::GetPelle()
{
	return PelleEnStock;
}

Mousquet * Corsaire::GetMousquet()
{
	return MousquetEnStock;
}

Armure * Corsaire::GetArmure()
{
	return ArmureEnStock;
}

Tresor * Corsaire::GetTresor()
{
	return TresorEnStock;
}

Sprite * Corsaire::GetSpritePelle()
{
	m_sPelle.setPosition(m_sprite.getPosition());
	return& m_sPelle;
}

Sprite * Corsaire::GetSpriteMousquet()
{
	m_sMousquet.setPosition(m_sprite.getPosition());
	return &m_sMousquet;
}

Sprite * Corsaire::GetSpriteArmure()
{
	m_sArmure.setPosition(m_sprite.getPosition());
	return &m_sArmure;
}

void Corsaire::SetNom(string nom)
{
	m_nom = nom;
}

string Corsaire::GetNom()
{
	return m_nom;
}

int Corsaire::ChanceSurvie()
{
	int chanceGagner = 0;

	if (MousquetEnStock != NULL && ArmureEnStock != NULL)
		chanceGagner = 100;
	else if (MousquetEnStock != NULL)
		chanceGagner = MousquetEnStock->GetChanceSurvie();
	else if (ArmureEnStock != NULL)
		chanceGagner = ArmureEnStock->GetChanceSurvie();

	return chanceGagner;
}
