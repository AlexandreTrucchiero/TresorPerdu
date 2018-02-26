#include "Objet.h"



Objet::Objet()
{
	m_x = 0;
	m_y = 0;

	m_texture.loadFromFile("assets/tiles.png", IntRect(0, 80, 64, 32));
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(0,0,32,32));
	m_sprite.setPosition(m_x, m_y);
	m_sprite.setScale(0.5, 0.5);
}


Objet::~Objet()
{
}

void Objet::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
	m_sprite.setPosition(m_x, m_y);
}

Sprite * Objet::GetSprite()
{
	return &m_sprite;
}

void Objet::SetDansUnCoffre(bool coffre)
{
	m_dansUnCoffre = coffre;

	if (m_dansUnCoffre)
		m_sprite.setTextureRect(IntRect(0, 0, 32, 32));
	else
		m_sprite.setTextureRect(IntRect(32, 0, 32, 32));
}

bool Objet::GetDansUnCoffre()
{
	return m_dansUnCoffre;
}
