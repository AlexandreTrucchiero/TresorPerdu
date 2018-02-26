#pragma once
#include "Personne.h"

class Flibustier : public Personne
{
public:
	Flibustier();
	~Flibustier();

	virtual bool Attaquer(int);
	virtual string Type();
	virtual int ChanceSurvie();
};

