#pragma once
#include "Personne.h"
#include "Pelle.h"
#include "Mousquet.h"
#include "Armure.h"
#include "Tresor.h"

class Corsaire : public Personne
{
private:
	Pelle* PelleEnStock;
	Mousquet* MousquetEnStock;
	Armure* ArmureEnStock;
	Tresor* TresorEnStock;

	string m_nom = "?";

	Texture m_tObjets;
	Sprite m_sPelle;
	Sprite m_sMousquet;
	Sprite m_sArmure;

public:
	Corsaire();
	~Corsaire();

	virtual bool Attaquer(int);
	virtual string Type();

	void SetPelle(Pelle*);
	void SetMousquet(Mousquet*);
	void SetArmure(Armure*);
	void SetTresor(Tresor*);
	Pelle* GetPelle();
	Mousquet* GetMousquet();
	Armure* GetArmure();
	Tresor* GetTresor();
	Sprite* GetSpritePelle();
	Sprite* GetSpriteMousquet();
	Sprite* GetSpriteArmure();
	void SetNom(string);
	string GetNom();
	int ChanceSurvie();
};

