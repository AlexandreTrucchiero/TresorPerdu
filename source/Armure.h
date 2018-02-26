#pragma once
#include "Objet.h"
class Armure : public Objet
{
private:
	int m_chanceSurvie = 90;
public:
	Armure();
	~Armure();
	int GetChanceSurvie();

	virtual string Type();
};

