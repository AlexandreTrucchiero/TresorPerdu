#pragma once
#include "Personne.h"
class Boucanier : public Personne
{
public:
	Boucanier();
	~Boucanier();

	virtual bool Attaquer(int);
	virtual string Type();
	virtual int ChanceSurvie();
};

