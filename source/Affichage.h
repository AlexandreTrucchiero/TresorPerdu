#pragma once
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Affichage
{
private:
	ContextSettings m_settings;
	VideoMode* m_vmode;
	RenderWindow* m_window;
	string m_windowName;
	Image* m_icon;
	View m_view;

	int ResX = 384, ResY = 216;

	vector<Sprite*> vectMap;
	vector<Sprite*> vectChest;
	vector<Sprite*> vectEntity;
	vector<Sprite*> vectObjet;
	vector<Text*> vectText;

public:
	Affichage();
	~Affichage();
	void Display();

	void SetResolution(int);
	void AddDrawableMap(Sprite*);
	void AddDrawableChest(Sprite*);
	void AddDrawableEntity(Sprite*);
	void AddDrawableObjet(Sprite*);
	void AddDrawableText(Text*);
	int RemovePersonneDrawable(int);
	void RemoveAllDrawableObjet();

	RenderWindow* GetWindow();
};

