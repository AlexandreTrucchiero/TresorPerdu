#pragma once
#include "Objet.h"
class Mousquet : public Objet
{
private:
	int m_chanceSurvie = 50;
public:
	Mousquet();
	~Mousquet();
	int GetChanceSurvie();

	virtual string Type();
};

