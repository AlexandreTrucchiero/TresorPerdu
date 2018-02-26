#include "Affichage.h"



Affichage::Affichage()
{
	m_settings.antialiasingLevel = 1;
	m_windowName = "Trésor Perdu";

	m_vmode = new VideoMode(ResX*2, ResY*2);
	m_window = new RenderWindow(*m_vmode, m_windowName, Style::Close, m_settings);
	m_window->setVerticalSyncEnabled(true);
	m_window->setFramerateLimit(30);
	m_window->clear(Color::Black);
	m_window->display();

	m_icon = new Image;
	if (!m_icon->loadFromFile("assets/icon.png")) { exit(1); }
	m_window->setIcon(32, 32, m_icon->getPixelsPtr());

	m_view.setSize(ResX *2, ResY *2);
	m_view.zoom(0.5);
	m_view.setCenter(ResX /2, ResY /2);
	m_window->setView(m_view);
}


Affichage::~Affichage()
{
	vectMap.clear();
	vectChest.clear();
	vectEntity.clear();
	vectObjet.clear();
	vectText.clear();

	delete m_window;
	delete m_vmode;
	delete m_icon;
}

void Affichage::SetResolution(int resolution)
{
	switch (resolution)
	{
	case 0:
		m_window->create(*m_vmode, m_windowName, Style::Fullscreen, m_settings);
		m_window->setVerticalSyncEnabled(true);
		m_window->setFramerateLimit(30);
		m_window->clear(Color::Black);
		m_window->display();
		break;
	case 1:
		m_window->create(*m_vmode, m_windowName, Style::Close, m_settings);
		m_window->setSize(Vector2u(ResX * 1, ResY * 1));
		m_window->setVerticalSyncEnabled(true);
		m_window->setFramerateLimit(30);
		m_window->clear(Color::Black);
		m_window->display();
		break;
	case 2:
		m_window->create(*m_vmode, m_windowName, Style::Close, m_settings);
		m_window->setSize(Vector2u(ResX * 2, ResY * 2));
		m_window->setVerticalSyncEnabled(true);
		m_window->setFramerateLimit(30);
		m_window->clear(Color::Black);
		m_window->display();
		break;
	case 3:
		m_window->create(*m_vmode, m_windowName, Style::Close, m_settings);
		m_window->setSize(Vector2u(ResX * 3, ResY * 3));
		m_window->setVerticalSyncEnabled(true);
		m_window->setFramerateLimit(30);
		m_window->clear(Color::Black);
		m_window->display();
		break;
	default:
		break;
	}
	m_window->setIcon(32, 32, m_icon->getPixelsPtr());
	m_window->setView(m_view);
}

void Affichage::AddDrawableMap(Sprite * sprite)
{
	vectMap.push_back(sprite);
}

void Affichage::AddDrawableChest(Sprite *sprite)
{
	vectChest.push_back(sprite);
}

void Affichage::AddDrawableEntity(Sprite *sprite)
{
	vectEntity.push_back(sprite);
}

void Affichage::AddDrawableObjet(Sprite * sprite)
{
	vectObjet.push_back(sprite);
}

void Affichage::AddDrawableText(Text * text)
{
	vectText.push_back(text);
}

int Affichage::RemovePersonneDrawable(int id)
{
	vectEntity.erase(vectEntity.begin() + id);
	return 666;
}

void Affichage::RemoveAllDrawableObjet()
{
	vectObjet.clear();
}

RenderWindow* Affichage::GetWindow()
{
	return m_window;
}

void Affichage::Display()
{
	m_window->clear(Color::Color(50,120,190));

	for (int i = 0; i < vectMap.size(); i++)
		m_window->draw(*vectMap.at(i));

	for (int i = 0; i < vectChest.size(); i++)
		m_window->draw(*vectChest.at(i));

	for (int i = 0; i < vectEntity.size(); i++)
		m_window->draw(*vectEntity.at(i));

	for (int i = 0; i < vectObjet.size(); i++)
		m_window->draw(*vectObjet.at(i));

	for (int i = 0; i < vectText.size(); i++)
		m_window->draw(*vectText.at(i));

	m_window->display();
}
