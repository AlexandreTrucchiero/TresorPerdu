#include "Partie.h"



Partie::Partie(Affichage* affichage)
{
	Fenetre = affichage;

	srand(time(NULL));

	if (!m_font.loadFromFile("assets/wendy.ttf"))
		exit(1);

	//on lance le menu principal
	bool reprendrePartie = MenuPrincipal();

	//soit on charge une ancienne partie, soit on crée une nouvelle
	if (reprendrePartie)
		Charger();
	else
		InitJeu();
}


Partie::~Partie()
{
	delete m_txtInfo;
	delete m_txtEquipement;
}

bool Partie::MenuPrincipal()
{
	Event event;
	bool choix = false;

	bool anciennePartie = false;
	ifstream file("partie.sav");
	if (file)
		anciennePartie = true;
	file.close();

	Text txtMenu;
	txtMenu.setFont(m_font);
	txtMenu.setFillColor(Color::Black);
	txtMenu.setStyle(Text::Bold);
	txtMenu.setScale(0.5, 0.5);
	txtMenu.setCharacterSize(60);
	txtMenu.setString("Tresor Perdu");
	txtMenu.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 2);

	Text txtNouveauJeu;
	txtNouveauJeu.setFont(m_font);
	txtNouveauJeu.setScale(0.5, 0.5);
	txtNouveauJeu.setCharacterSize(40);
	txtNouveauJeu.setString("Nouvelle Partie");
	txtNouveauJeu.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 4);

	Text txtReprendreJeu;
	txtReprendreJeu.setFont(m_font);
	txtReprendreJeu.setScale(0.5, 0.5);
	txtReprendreJeu.setCharacterSize(40);
	txtReprendreJeu.setString("Reprendre Partie");
	txtReprendreJeu.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 4 + 20);

	Text txtParam;
	txtParam.setFont(m_font);
	txtParam.setScale(0.5, 0.5);
	txtParam.setCharacterSize(40);
	txtParam.setString("Informations");
	txtParam.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 4 + 40);

	Text txtQuitter;
	txtQuitter.setFont(m_font);
	txtQuitter.setScale(0.5, 0.5);
	txtQuitter.setCharacterSize(40);
	txtQuitter.setString("Quitter");
	txtQuitter.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 4 + 60);


	Texture tBackground;
	if (!tBackground.loadFromFile("assets/bg_menu.png", IntRect(0, 0, 384, 216)))
		exit(1);
	Sprite sBackground;
	sBackground.setTexture(tBackground);
	sBackground.setPosition(0, 0);

	int curseurMenu = 0;

	while (!choix)
	{
		while (Fenetre->GetWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				exit(1);
			case Event::KeyReleased:

				if (event.key.code == Keyboard::F11)
					Fenetre->SetResolution(0);
				if (event.key.code == Keyboard::Num1)
					Fenetre->SetResolution(1);
				if (event.key.code == Keyboard::Num2)
					Fenetre->SetResolution(2);
				if (event.key.code == Keyboard::Num3)
					Fenetre->SetResolution(3);

				if (event.key.code == Keyboard::Return)
				{
					switch (curseurMenu)
					{
					case 0:
						choix = ChoixMode();
						break;
					case 1:
						if (anciennePartie)
							return true;
						break;
					case 2:
						Informations();
						break;
					case 3:
						exit(1);
						break;
					default:
						break;
					}
				}
				else if (event.key.code == Keyboard::Up)
				{
					curseurMenu--;
					if (curseurMenu < 0)
						curseurMenu = 0;
				}
				else if (event.key.code == Keyboard::Down)
				{
					curseurMenu++;
					if (curseurMenu > 3)
						curseurMenu = 3;
				}
				break;
			default:
				break;
			}
		}

		txtNouveauJeu.setFillColor(Color::Black);
		txtReprendreJeu.setFillColor(Color::Black);
		txtParam.setFillColor(Color::Black);
		txtQuitter.setFillColor(Color::Black);
		switch (curseurMenu)
		{
		case 0:
			txtNouveauJeu.setFillColor(Color::Red);
			break;
		case 1:
			txtReprendreJeu.setFillColor(Color::Red);
			if (!anciennePartie)
				txtReprendreJeu.setFillColor(Color::Color(100,100,100));
			break;
		case 2:
			txtParam.setFillColor(Color::Red);
			break;
		case 3:
			txtQuitter.setFillColor(Color::Red);
			break;
		default:
			break;
		}

		if (!choix)
		{
			Fenetre->GetWindow()->clear(Color::Black);
			Fenetre->GetWindow()->draw(sBackground);
			Fenetre->GetWindow()->draw(txtMenu);
			Fenetre->GetWindow()->draw(txtNouveauJeu);
			Fenetre->GetWindow()->draw(txtReprendreJeu);
			Fenetre->GetWindow()->draw(txtParam);
			Fenetre->GetWindow()->draw(txtQuitter);
			Fenetre->GetWindow()->display();
		}
	}
	return false;
}

bool Partie::ChoixMode()
{
	Event event;
	bool choix = false;

	Text txtMenu;
	txtMenu.setFont(m_font);
	txtMenu.setFillColor(Color::Black);
	txtMenu.setStyle(Text::Bold);
	txtMenu.setScale(0.5, 0.5);
	txtMenu.setCharacterSize(60);
	txtMenu.setString("Choix du Mode:");
	txtMenu.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 2);


	Text txtCorsaire;
	txtCorsaire.setFont(m_font);
	txtCorsaire.setScale(0.5, 0.5);
	txtCorsaire.setCharacterSize(40);
	txtCorsaire.setString("Nombre de joueur :   1 >");
	txtCorsaire.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 3);

	Text txtPirate;
	txtPirate.setFont(m_font);
	txtPirate.setScale(0.5, 0.5);
	txtPirate.setCharacterSize(40);
	txtPirate.setString("Nombre de pirate :   1 >");
	txtPirate.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 4);

	Text txtValider;
	txtValider.setFont(m_font);
	txtValider.setStyle(Text::Bold);
	txtValider.setScale(0.5, 0.5);
	txtValider.setCharacterSize(40);
	txtValider.setString("Valider");
	txtValider.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 6);


	Texture tBackground;
	if (!tBackground.loadFromFile("assets/bg_menu.png", IntRect(0, 0, 384, 216)))
		exit(1);
	Sprite sBackground;
	sBackground.setTexture(tBackground);
	sBackground.setPosition(0, 0);

	int curseurMenu = 0;
	int curseurCorsaire = 1, curseurPirate = 4;

	while (!choix)
	{
		while (Fenetre->GetWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				exit(1);
			case Event::KeyReleased:

				if (event.key.code == Keyboard::F11)
					Fenetre->SetResolution(0);
				if (event.key.code == Keyboard::Num1)
					Fenetre->SetResolution(1);
				if (event.key.code == Keyboard::Num2)
					Fenetre->SetResolution(2);
				if (event.key.code == Keyboard::Num3)
					Fenetre->SetResolution(3);

				if (event.key.code == Keyboard::Return)
				{
					if (curseurMenu == 2)
						choix = true;
				}
				else if (event.key.code == Keyboard::Escape)
				{
					return false;
				}
				else if (event.key.code == Keyboard::Up)
				{
					curseurMenu--;
					if (curseurMenu < 0)
						curseurMenu = 0;
				}
				else if (event.key.code == Keyboard::Down)
				{
					curseurMenu++;
					if (curseurMenu > 2)
						curseurMenu = 2;
				}
				else if (event.key.code == Keyboard::Left)
				{
					switch (curseurMenu)
					{
					case 0:
						curseurCorsaire--;
						if (curseurCorsaire < 1)
							curseurCorsaire = 1;
						break;
					case 1:
						curseurPirate--;
						if (curseurPirate < 1)
							curseurPirate = 1;
						break;
					default:
						break;
					}
				}
				else if (event.key.code == Keyboard::Right)
				{
					switch (curseurMenu)
					{
					case 0:
						curseurCorsaire++;
						if (curseurCorsaire > 4)
							curseurCorsaire = 4;
						break;
					case 1:
						curseurPirate++;
						if (curseurPirate > 20)
							curseurPirate = 20;
						break;
					default:
						break;
					}
				}
				break;
			default:
				break;
			}
		}

		txtCorsaire.setFillColor(Color::Black);
		txtPirate.setFillColor(Color::Black);
		txtValider.setFillColor(Color::Black);
		switch (curseurMenu)
		{
		case 0:
			txtCorsaire.setFillColor(Color::Red);
			break;
		case 1:
			txtPirate.setFillColor(Color::Red);
			break;
		case 2:
			txtValider.setFillColor(Color::Red);
			break;
		default:
			break;
		}

		if (curseurCorsaire == 1)
			txtCorsaire.setString("Nombre de joueur :   " + to_string(curseurCorsaire) + " >");
		else if (curseurCorsaire == 4)
			txtCorsaire.setString("Nombre de joueur : < " + to_string(curseurCorsaire));
		else
			txtCorsaire.setString("Nombre de joueur : < " + to_string(curseurCorsaire) + " >");

		if (curseurPirate == 1)
			txtPirate.setString("Nombre de pirate :   " + to_string(curseurPirate) + " >");
		else if (curseurPirate == 20)
			txtPirate.setString("Nombre de pirate : < " + to_string(curseurPirate));
		else
			txtPirate.setString("Nombre de pirate : < " + to_string(curseurPirate) + " >");

		Fenetre->GetWindow()->clear(Color::Black);
		Fenetre->GetWindow()->draw(sBackground);
		Fenetre->GetWindow()->draw(txtMenu);
		Fenetre->GetWindow()->draw(txtCorsaire);
		Fenetre->GetWindow()->draw(txtPirate);
		Fenetre->GetWindow()->draw(txtValider);
		Fenetre->GetWindow()->display();
	}

	m_nombreCorsaire = curseurCorsaire;
	m_nombrePirate = curseurPirate;

	return true;
}

void Partie::Informations()
{
	Event event;
	bool loop = true;

	Text txtMenu;
	txtMenu.setFont(m_font);
	txtMenu.setFillColor(Color::Black);
	txtMenu.setStyle(Text::Bold);
	txtMenu.setScale(0.5, 0.5);
	txtMenu.setCharacterSize(60);
	txtMenu.setString("Informations:");
	txtMenu.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 2);


	Text txtInstruction;
	txtInstruction.setFont(m_font);
	txtInstruction.setFillColor(Color::Black);
	txtInstruction.setScale(0.5, 0.5);
	txtInstruction.setCharacterSize(20);
	txtInstruction.setString("Instructions :\n  Le but du jeu est de trouver le tresor enterre sur l'ile. Les coffres presents sur l'ile contiennent\n des pelles, des mousquets ainsi que des armures pour survivre. Bonne chance!");
	txtInstruction.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 208 / 3);

	Text txtControles;
	txtControles.setFont(m_font);
	txtControles.setFillColor(Color::Black);
	txtControles.setScale(0.5, 0.5);
	txtControles.setCharacterSize(20);
	txtControles.setString("Controles :\n\n Valider				 Retour				 Sauvegarde			  Vitesse de Jeu			Deplacement / Choix de cible\n\n\n\n			   Naviguer\n\n\n\n															Resolution Fenetre		 Plein Ecran");
	txtControles.setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 10, Fenetre->GetWindow()->getView().getCenter().y - 35);



	Texture tBackground;
	if (!tBackground.loadFromFile("assets/bg_param.png", IntRect(0, 0, 384, 216)))
		exit(1);
	Sprite sBackground;
	sBackground.setTexture(tBackground);
	sBackground.setPosition(0, 0);

	while (loop)
	{
		while (Fenetre->GetWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				exit(1);
			case Event::KeyReleased:

				if (event.key.code == Keyboard::F11)
					Fenetre->SetResolution(0);
				if (event.key.code == Keyboard::Num1)
					Fenetre->SetResolution(1);
				if (event.key.code == Keyboard::Num2)
					Fenetre->SetResolution(2);
				if (event.key.code == Keyboard::Num3)
					Fenetre->SetResolution(3);

				if (event.key.code == Keyboard::Return || event.key.code == Keyboard::Escape)
				{
					loop = false;
				}
				break;
			default:
				break;
			}
		}

		Fenetre->GetWindow()->clear(Color::Black);
		Fenetre->GetWindow()->draw(sBackground);
		Fenetre->GetWindow()->draw(txtMenu);
		Fenetre->GetWindow()->draw(txtInstruction);
		Fenetre->GetWindow()->draw(txtControles);
		Fenetre->GetWindow()->display();
	}
}

void Partie::InitJeu()
{
	Fenetre->AddDrawableMap(m_ile.GetOceanSprite());

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 12; j++)
			Fenetre->AddDrawableMap(m_ile.GetCase(i, j)->GetSprite());

	int rollX = 0, rollY = 0;

	for (int i = 0; i < m_nombreCorsaire; i++)
	{
		Corsaire* corsaire = new Corsaire;
		corsaire->SetNom("Joueur " + to_string(i + 1));

		do
		{
			rollX = rand() % 12;
			rollY = rand() % 12;
		} while (m_ile.GetCase(rollX, rollY)->GetPersonne() != NULL);

		m_ile.AjouterPersonne(corsaire, m_ile.GetCase(rollX, rollY));
		Fenetre->AddDrawableEntity(corsaire->GetSprite());
	}

	int rollNum = 0;

	for (int i = 0; i < m_nombrePirate; i++)
	{
		rollNum = rand() % 2;
		if (rollNum == 0)
		{
			Boucanier* boucanier = new Boucanier;

			do
			{
				rollX = rand() % 12;
				rollY = rand() % 12;
			} while (m_ile.GetCase(rollX, rollY)->GetPersonne() != NULL);

			m_ile.AjouterPersonne(boucanier, m_ile.GetCase(rollX, rollY));
			Fenetre->AddDrawableEntity(boucanier->GetSprite());
		}
		else
		{
			Flibustier* flibustier = new Flibustier;

			do
			{
				rollX = rand() % 12;
				rollY = rand() % 12;
			} while (m_ile.GetCase(rollX, rollY)->GetPersonne() != NULL);

			m_ile.AjouterPersonne(flibustier, m_ile.GetCase(rollX, rollY));
			Fenetre->AddDrawableEntity(flibustier->GetSprite());
		}
	}

	for (int i = 0; i < m_nombreCorsaire * 3; i += 3)
	{
		Pelle* pelle = new Pelle;

		do
		{
			rollX = rand() % 12;
			rollY = rand() % 12;
		} while (m_ile.GetCase(rollX, rollY)->GetPersonne() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetPelle() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetMousquet() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetArmure() != NULL);

		m_ile.AjouterObjet(pelle, m_ile.GetCase(rollX, rollY));
		Fenetre->AddDrawableChest(pelle->GetSprite());

		Mousquet* mousquet = new Mousquet;

		do
		{
			rollX = rand() % 12;
			rollY = rand() % 12;
		} while (m_ile.GetCase(rollX, rollY)->GetPersonne() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetPelle() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetMousquet() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetArmure() != NULL);

		m_ile.AjouterObjet(mousquet, m_ile.GetCase(rollX, rollY));
		Fenetre->AddDrawableChest(mousquet->GetSprite());

		Armure* armure = new Armure;

		do
		{
			rollX = rand() % 12;
			rollY = rand() % 12;
		} while (m_ile.GetCase(rollX, rollY)->GetPersonne() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetPelle() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetMousquet() != NULL
			&& m_ile.GetCase(rollX, rollY)->GetArmure() != NULL);

		m_ile.AjouterObjet(armure, m_ile.GetCase(rollX, rollY));
		Fenetre->AddDrawableChest(armure->GetSprite());
	}

	do
	{
		rollX = rand() % 12;
		rollY = rand() % 12;
	} while (m_ile.GetCase(rollX, rollY)->GetPersonne() != NULL
		&& m_ile.GetCase(rollX, rollY)->GetPelle() != NULL
		&& m_ile.GetCase(rollX, rollY)->GetMousquet() != NULL
		&& m_ile.GetCase(rollX, rollY)->GetArmure() != NULL);

	m_ile.GetCase(rollX, rollY)->AddTresor();

	m_txtInfo = new Text;
	m_txtInfo->setFont(m_font);
	m_txtInfo->setScale(0.5, 0.5);
	m_txtInfo->setCharacterSize(25);
	m_txtInfo->setFillColor(Color::Black);
	m_txtInfo->setString("?");
	m_txtInfo->setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 5, Fenetre->GetWindow()->getView().getCenter().y + 178 / 2);
	Fenetre->AddDrawableText(m_txtInfo);

	m_txtEquipement = new Text;
	m_txtEquipement->setFont(m_font);
	m_txtEquipement->setScale(0.5, 0.5);
	m_txtEquipement->setCharacterSize(30);
	m_txtEquipement->setFillColor(Color::Black);
	m_txtEquipement->setString("?");
	m_txtEquipement->setPosition(Fenetre->GetWindow()->getView().getCenter().x + 192 / 2 + 5, Fenetre->GetWindow()->getView().getCenter().y + 24);
	Fenetre->AddDrawableText(m_txtEquipement);

	m_txtChoixAction = new Text[4];
	for (int i = 0; i < 4; i++)
	{
		m_txtChoixAction[i].setFont(m_font);
		m_txtChoixAction[i].setScale(0.5, 0.5);
		m_txtChoixAction[i].setCharacterSize(30);
		m_txtChoixAction[i].setFillColor(Color::Black);
		m_txtChoixAction[i].setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 5, Fenetre->GetWindow()->getView().getCenter().y + 24 + (14 * i));
		Fenetre->AddDrawableText(&m_txtChoixAction[i]);
	}

	m_txtChoixAction[0].setStyle(Text::Bold);
	m_txtChoixAction[0].setString("Choix Action:");
	m_txtChoixAction[1].setString("> Deplacer");
	m_txtChoixAction[2].setString("> Creuser");
	m_txtChoixAction[3].setString("> Tirer");

	if (!m_musique.openFromFile("assets/music.wav")) { exit(1); }
	m_musique.setLoop(true);
}

void Partie::EnJeu()
{
	Event event;

	bool enJeu = true;
	bool finDeTour = false;
	int curseurJoueur = 0;

	int alea = 0;
	int buffBoucanier = 0;
	int buffCligno = 0;
	int buffAntiblocage = 0;
	bool coffreDejaVu = false;

	m_musique.play();

	while (enJeu)
	{
		//Boucle d'evenements
		while (Fenetre->GetWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				m_musique.stop();
				exit(1);
			case Event::KeyReleased:

				if (m_ile.GetPersonne(m_tourDeJeu)->Type() == "Corsaire")
				{
					if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Numpad8 || event.key.code == Keyboard::Z)
					{
						curseurJoueur--;
						if (curseurJoueur < 0)
							curseurJoueur = 0;
					}
					else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::Numpad2 || event.key.code == Keyboard::X)
					{
						curseurJoueur++;
						if (curseurJoueur > 2)
							curseurJoueur = 2;
					}
				}

				finDeTour = EvenementsClavier(&event, curseurJoueur);

				break;
			default:
				break;
			}
		}

		//Tour d'un Boucanier
		if (m_ile.GetPersonne(m_tourDeJeu)->Type() == "Boucanier")
		{
			AttendreChar();
			buffAntiblocage++;

			m_ile.SetInfo(m_ile.GetPersonne(m_tourDeJeu)->Type() + " se deplace...");

			Attendre(m_vitessePartie);

			if (buffBoucanier == 0)
				alea = rand() % 2;

			finDeTour = m_ile.DeplacerPirate(m_tourDeJeu);

			if (finDeTour)
			{
				if (m_ile.GetEraseIndex() != 666)
				{
					if (m_ile.GetEraseIndex() < m_tourDeJeu)
						m_tourDeJeu--;
					m_ile.SetEraseIndex(Fenetre->RemovePersonneDrawable(m_ile.GetEraseIndex()));
				}
				AttendreChar();
				finDeTour = false;
				if (buffBoucanier >= alea)
				{
					buffBoucanier = 0;
					buffCligno = 0;
					buffAntiblocage = 0;
					m_choixCorsaire = eChoixCorsaire::AUCUN;
					curseurJoueur = 0;
					coffreDejaVu = false;
					m_tourDeJeu++;
					Attendre(m_vitessePartie / 2);
				}
				else
					buffBoucanier++;
			}
		}
		//Tour d'un Flibustier
		else if (m_ile.GetPersonne(m_tourDeJeu)->Type() == "Flibustier")
		{
			AttendreChar();
			buffAntiblocage++;

			m_ile.SetInfo(m_ile.GetPersonne(m_tourDeJeu)->Type() + " se deplace...");

			Attendre(m_vitessePartie);

			finDeTour = m_ile.CheckCasesAutour(m_tourDeJeu);

			if (!finDeTour)
				finDeTour = m_ile.DeplacerPirate(m_tourDeJeu);

			if (finDeTour)
			{
				if (m_ile.GetEraseIndex() != 666)
				{
					if (m_ile.GetEraseIndex() < m_tourDeJeu)
						m_tourDeJeu--;
					m_ile.SetEraseIndex(Fenetre->RemovePersonneDrawable(m_ile.GetEraseIndex()));
				}
				AttendreChar();
				finDeTour = false;
				buffCligno = 0;
				buffAntiblocage = 0;
				m_choixCorsaire = eChoixCorsaire::AUCUN;
				curseurJoueur = 0;
				coffreDejaVu = false;
				m_tourDeJeu++;
				Attendre(m_vitessePartie / 2);
			}
		}
		//Tour d'un Corsaire
		else if (m_ile.GetPersonne(m_tourDeJeu)->Type() == "Corsaire")
		{
			Corsaire* corsaire = (Corsaire*)m_ile.GetPersonne(m_tourDeJeu);

			AttendreChar();
			if (!coffreDejaVu)
				coffreDejaVu = m_ile.CheckCaseActuelle(m_tourDeJeu);
			AttendreChar();

			switch (m_choixCorsaire)
			{
			case Partie::AUCUN:
				m_ile.SetInfo(corsaire->GetNom() + " doit choisir une action...");
				break;
			case Partie::DEPLACER:
				m_ile.SetInfo(corsaire->GetNom() + " doit se deplacer...");
				break;
			case Partie::CREUSER:
				m_ile.CheckTresor(m_tourDeJeu);
				finDeTour = true;
				break;
			case Partie::TIRER:
				m_ile.SetInfo(corsaire->GetNom() + " doit choisir une cible...");
				break;
			default:
				break;
			}

			if (finDeTour)
			{
				int eraseBuffer = m_ile.GetEraseIndex();

				if (m_ile.GetEraseIndex() != 666)
				{
					if (m_ile.GetEraseIndex() < m_tourDeJeu)
					{
						eraseBuffer--;
						m_tourDeJeu--;
					}
					m_ile.SetEraseIndex(Fenetre->RemovePersonneDrawable(m_ile.GetEraseIndex()));
				}

				if (eraseBuffer != m_tourDeJeu)
				{
					coffreDejaVu = m_ile.CheckCaseActuelle(m_tourDeJeu);
					AttendreChar();
					m_ile.SetInfo("...");

					Corsaire* corsaire = (Corsaire*)m_ile.GetPersonne(m_tourDeJeu);

					if (corsaire->GetTresor() != NULL)
						enJeu = false;
				}

				AttendreChar();
				m_ile.SetInfo("...");
				finDeTour = false;
				m_tourDeJeu++;
				buffCligno = 0;
				m_choixCorsaire = eChoixCorsaire::AUCUN;
				curseurJoueur = 0;
				coffreDejaVu = false;
			}
		}

		//Gestion d'impossibilite de deplacement
		if (buffAntiblocage > 100)
		{
			buffBoucanier = 0;
			buffCligno = 0;
			buffAntiblocage = 0;
			m_tourDeJeu++;
		}

		//Mise en jour des informations de jeu
		enJeu = MiseAJourEnJeu(enJeu);
		MiseAJourTourDeJeu(curseurJoueur);

		buffCligno = Clignotement(buffCligno);

		//Affichage de la frame en cours
		Fenetre->Display();
	}
}

bool Partie::MiseAJourEnJeu(bool enjeu)
{
	m_nombreCorsaire = 0;
	m_nombrePirate = 0;

	Fenetre->RemoveAllDrawableObjet();
	for (int i = 0; i < m_ile.GetVectPersonne().size(); i++)
	{
		if (m_ile.GetPersonne(i)->Type() == "Corsaire")
		{
			m_nombreCorsaire++;
			Corsaire* corsaire = (Corsaire*)m_ile.GetPersonne(i);
			if (corsaire->GetPelle() != NULL)
				Fenetre->AddDrawableObjet(corsaire->GetSpritePelle());
			if (corsaire->GetMousquet() != NULL)
				Fenetre->AddDrawableObjet(corsaire->GetSpriteMousquet());
			if (corsaire->GetArmure() != NULL)
				Fenetre->AddDrawableObjet(corsaire->GetSpriteArmure());
		}
		if (m_ile.GetPersonne(i)->Type() == "Boucanier" || m_ile.GetPersonne(i)->Type() == "Flibustier")
			m_nombrePirate++;
	}

	if (m_nombreCorsaire == 0)
		enjeu = false;

	return enjeu;
}

void Partie::MiseAJourTourDeJeu(int curseurJoueur)
{
	if (m_nombreCorsaire == 0)
	{
		m_ile.SetInfo("Tout les corsaires sont morts..");
		m_ile.SetAttendre(true);
		AttendreChar();
	}

	if (m_tourDeJeu > (m_nombrePirate + m_nombreCorsaire - 1))
		m_tourDeJeu = 0;
	else if (m_tourDeJeu < 0)
		m_tourDeJeu = m_nombrePirate + m_nombreCorsaire - 1;

	if (m_ile.GetPersonne(m_tourDeJeu)->Type() == "Corsaire" && m_choixCorsaire == eChoixCorsaire::AUCUN)
	{
		for (int i = 0; i < 4; i++)
			m_txtChoixAction[i].setFillColor(Color::Color(0, 0, 0, 255));
		m_txtChoixAction[curseurJoueur + 1].setFillColor(Color::Color(255, 0, 0, 255));
	}
	else
	{
		for (int i = 0; i < 4; i++)
			m_txtChoixAction[i].setFillColor(Color::Color(0, 0, 0, 0));
	}

	m_txtInfo->setString(m_ile.GetInfo());
	m_txtEquipement->setString(m_ile.GetEquipement(m_tourDeJeu));
}

bool Partie::EvenementsClavier(Event * ev, int curseurJoueur)
{
	if (ev->key.code == Keyboard::F11)
		Fenetre->SetResolution(0);
	if (ev->key.code == Keyboard::Num1)
		Fenetre->SetResolution(1);
	if (ev->key.code == Keyboard::Num2)
		Fenetre->SetResolution(2);
	if (ev->key.code == Keyboard::Num3)
		Fenetre->SetResolution(3);
	if (ev->key.code == Keyboard::F5)
		Sauvegarder();

	if (ev->key.code == Keyboard::Subtract)
	{
		m_vitessePartie -= 250;
		if (m_vitessePartie < 250)
			m_vitessePartie = 250;
	}
	else if (ev->key.code == Keyboard::Add)
	{
		m_vitessePartie += 250;
		if (m_vitessePartie > 1000)
			m_vitessePartie = 1000;
	}

	if (m_ile.GetPersonne(m_tourDeJeu)->Type() == "Corsaire")
	{

		if (ev->key.code == Keyboard::P)
		{
			return true;
		}

		if (m_choixCorsaire == eChoixCorsaire::DEPLACER)
		{
			if (ev->key.code == Keyboard::Up || ev->key.code == Keyboard::Numpad8 || ev->key.code == Keyboard::Z)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::HAUT);
			}
			else if (ev->key.code == Keyboard::Down || ev->key.code == Keyboard::Numpad2 || ev->key.code == Keyboard::X)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::BAS);
			}
			else if (ev->key.code == Keyboard::Left || ev->key.code == Keyboard::Numpad4 || ev->key.code == Keyboard::Q)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::GAUCHE);
			}
			else if (ev->key.code == Keyboard::Right || ev->key.code == Keyboard::Numpad6 || ev->key.code == Keyboard::D)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::DROITE);
			}
			else if (ev->key.code == Keyboard::Numpad7 || ev->key.code == Keyboard::A)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::HG);
			}
			else if (ev->key.code == Keyboard::Numpad9 || ev->key.code == Keyboard::E)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::HD);
			}
			else if (ev->key.code == Keyboard::Numpad1 || ev->key.code == Keyboard::W)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::BG);
			}
			else if (ev->key.code == Keyboard::Numpad3 || ev->key.code == Keyboard::C)
			{
				return m_ile.DeplacerCorsaire(m_tourDeJeu, Plateau::BD);
			}
		}
		else if (m_choixCorsaire == eChoixCorsaire::TIRER)
		{
			if (ev->key.code == Keyboard::Up || ev->key.code == Keyboard::Numpad8 || ev->key.code == Keyboard::Z)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::HAUT);
			}
			else if (ev->key.code == Keyboard::Down || ev->key.code == Keyboard::Numpad2 || ev->key.code == Keyboard::X)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::BAS);
			}
			else if (ev->key.code == Keyboard::Left || ev->key.code == Keyboard::Numpad4 || ev->key.code == Keyboard::Q)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::GAUCHE);
			}
			else if (ev->key.code == Keyboard::Right || ev->key.code == Keyboard::Numpad6 || ev->key.code == Keyboard::D)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::DROITE);
			}
			else if (ev->key.code == Keyboard::Numpad7 || ev->key.code == Keyboard::A)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::HG);
			}
			else if (ev->key.code == Keyboard::Numpad9 || ev->key.code == Keyboard::E)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::HD);
			}
			else if (ev->key.code == Keyboard::Numpad1 || ev->key.code == Keyboard::W)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::BG);
			}
			else if (ev->key.code == Keyboard::Numpad3 || ev->key.code == Keyboard::C)
			{
				return m_ile.Tirer(m_tourDeJeu, Plateau::BD);
			}
		}

		if (ev->key.code == Keyboard::Return)
		{
			Corsaire* corsaire = (Corsaire*)m_ile.GetPersonne(m_tourDeJeu);

			switch (curseurJoueur)
			{
			case 0:
				m_choixCorsaire = eChoixCorsaire::DEPLACER;
				break;
			case 1:
				if (corsaire->GetPelle() != NULL)
					m_choixCorsaire = eChoixCorsaire::CREUSER;
				else
				{
					m_ile.SetInfo(corsaire->GetNom() + " n'a pas de pelle...");
					m_ile.SetAttendre(true);
					AttendreChar();
				}
				break;
			case 2:
				if (corsaire->GetMousquet() != NULL)
				{
					m_choixCorsaire = eChoixCorsaire::TIRER;
				}
				else
				{
					m_ile.SetInfo(corsaire->GetNom() + " n'a pas de mousquet...");
					m_ile.SetAttendre(true);
					AttendreChar();
				}
				break;
			default:
				break;
			}
		}
		else if (ev->key.code == Keyboard::Escape)
		{
			m_choixCorsaire = eChoixCorsaire::AUCUN;
		}
	}
	return false;
}

int Partie::Clignotement(int clign)
{
	for (int i = 0; i < (m_nombrePirate + m_nombreCorsaire); i++)
		m_ile.GetPersonne(i)->GetSprite()->setColor(Color(255, 255, 255));

	if (clign < 10)
	{
		m_ile.GetPersonne(m_tourDeJeu)->GetSprite()->setColor(Color(255, 50, 50));
		clign++;
	}
	else if (clign < 20)
	{
		m_ile.GetPersonne(m_tourDeJeu)->GetSprite()->setColor(Color(255, 255, 255));
		clign++;
	}
	else
		clign = 0;

	return clign;
}

void Partie::AttendreChar()
{
	Event event;

	m_nombreCorsaire = 0;
	m_nombrePirate = 0;
	for (int i = 0; i < m_ile.GetVectPersonne().size(); i++)
	{
		if (m_ile.GetPersonne(i)->Type() == "Corsaire")
			m_nombreCorsaire++;
		if (m_ile.GetPersonne(i)->Type() == "Boucanier" || m_ile.GetPersonne(i)->Type() == "Flibustier")
			m_nombrePirate++;
	}

	if (m_tourDeJeu > (m_nombrePirate + m_nombreCorsaire - 1))
		m_tourDeJeu = 0;
	else if (m_tourDeJeu < 0)
		m_tourDeJeu = m_nombrePirate + m_nombreCorsaire - 1;

	while (m_ile.GetAttendre())
	{
		while (Fenetre->GetWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				m_musique.stop();
				exit(1);
				break;
			case Event::KeyReleased:
				if (event.key.code == Keyboard::Return)
					m_ile.SetAttendre(false);

				if (event.key.code == Keyboard::F11)
					Fenetre->SetResolution(0);
				if (event.key.code == Keyboard::Num1)
					Fenetre->SetResolution(1);
				if (event.key.code == Keyboard::Num2)
					Fenetre->SetResolution(2);
				if (event.key.code == Keyboard::Num3)
					Fenetre->SetResolution(3);
				if (event.key.code == Keyboard::F5)
					Sauvegarder();

				if (event.key.code == Keyboard::Subtract)
				{
					m_vitessePartie -= 250;
					if (m_vitessePartie < 250)
						m_vitessePartie = 250;
				}
				else if (event.key.code == Keyboard::Add)
				{
					m_vitessePartie += 250;
					if (m_vitessePartie > 1000)
						m_vitessePartie = 1000;
				}
				break;
			default:
				break;
			}
		}

		Fenetre->RemoveAllDrawableObjet();
		for (int i = 0; i < m_ile.GetVectPersonne().size(); i++)
		{
			if (m_ile.GetPersonne(i)->Type() == "Corsaire")
			{
				Corsaire* corsaire = (Corsaire*)m_ile.GetPersonne(i);
				if (corsaire->GetPelle() != NULL)
					Fenetre->AddDrawableObjet(corsaire->GetSpritePelle());
				if (corsaire->GetMousquet() != NULL)
					Fenetre->AddDrawableObjet(corsaire->GetSpriteMousquet());
				if (corsaire->GetArmure() != NULL)
					Fenetre->AddDrawableObjet(corsaire->GetSpriteArmure());
			}
		}

		m_txtInfo->setString(m_ile.GetInfo() + " (Valider)");
		m_txtEquipement->setString(m_ile.GetEquipement(m_tourDeJeu));
		Fenetre->Display();
	}
}

void Partie::Attendre(float millisec)
{
	float compute = ((float)millisec / (float)1000) * 30;
	int frames = (int)compute;
	int clock = 0;
	Event event;

	while (clock < frames)
	{
		while (Fenetre->GetWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				m_musique.stop();
				exit(1);
				break;
			case Event::KeyReleased:

				if (event.key.code == Keyboard::F11)
					Fenetre->SetResolution(0);
				if (event.key.code == Keyboard::Num1)
					Fenetre->SetResolution(1);
				if (event.key.code == Keyboard::Num2)
					Fenetre->SetResolution(2);
				if (event.key.code == Keyboard::Num3)
					Fenetre->SetResolution(3);
				if (event.key.code == Keyboard::F5)
					Sauvegarder();

				break;
			default:
				break;
			}
		}

		clock++;

		Fenetre->Display();
	}
}

void Partie::Sauvegarder()
{
	ofstream file;
	file.open("partie.sav");

	if (file.is_open())
	{
		file << m_nombreCorsaire << " "
			<< m_nombrePirate << " "
			<< m_tourDeJeu << " "
			<< m_vitessePartie << " " << endl;

		for (int i = 0; i < m_nombreCorsaire; i++)
		{
			Corsaire* corsaire = (Corsaire*)m_ile.GetVectPersonne().at(i);

			for (int j = 0; j < 12; j++)
			{
				for (int k = 0; k < 12; k++)
				{
					if (corsaire == m_ile.GetCase(j, k)->GetPersonne())
					{
						file << corsaire->GetNom() << " "
							<< j << " "
							<< k << " ";
						if (corsaire->GetPelle() != NULL)
							file << "OUI" << " ";
						else
							file << "NON" << " ";
						if (corsaire->GetMousquet() != NULL)
							file << "OUI" << " ";
						else
							file << "NON" << " ";
						if (corsaire->GetArmure() != NULL)
							file << "OUI" << " ";
						else
							file << "NON" << " ";
						file << endl;
						j = 12;
						k = 12;
					}
				}
			}

		}

		for (int i = 0; i < m_nombrePirate; i++)
		{
			Personne* pirate = m_ile.GetVectPersonne().at(m_nombreCorsaire + i);

			for (int j = 0; j < 12; j++)
			{
				for (int k = 0; k < 12; k++)
				{
					if (pirate == m_ile.GetCase(j, k)->GetPersonne())
					{
						file << pirate->Type() << " "
							<< j << " "
							<< k << " " << endl;
						j = 12;
						k = 12;
					}
				}
			}

		}

		for (int j = 0; j < 12; j++)
		{
			for (int k = 0; k < 12; k++)
			{
				if (m_ile.GetCase(j, k)->GetPelle() != NULL)
				{
					file << "PELLE" << " "
						<< j << " "
						<< k << " " << endl;
				}
				else if (m_ile.GetCase(j, k)->GetMousquet() != NULL)
				{
					file << "MOUSQUET" << " "
						<< j << " "
						<< k << " " << endl;
				}
				else if (m_ile.GetCase(j, k)->GetArmure() != NULL)
				{
					file << "ARMURE" << " "
						<< j << " "
						<< k << " " << endl;
				}
				else if (m_ile.GetCase(j, k)->GetTresor() != NULL)
				{
					file << "TRESOR" << " "
						<< j << " "
						<< k << " " << endl;
				}
			}
		}
	}
	else
		exit(1);

	file.close();
}

void Partie::Charger()
{
	string strBuffer;
	int intBuffer, intBuffer2;
	ifstream file("partie.sav");
	if (file.is_open())
	{
		Fenetre->AddDrawableMap(m_ile.GetOceanSprite());

		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 12; j++)
				Fenetre->AddDrawableMap(m_ile.GetCase(i, j)->GetSprite());
		
		file >> m_nombreCorsaire >> m_nombrePirate >> m_tourDeJeu >> m_vitessePartie;

		for (int i = 0; i < m_nombreCorsaire; i++)
		{
			Corsaire* corsaire = new Corsaire;
			file >> strBuffer >> intBuffer;
			corsaire->SetNom(strBuffer + " " + to_string(intBuffer));

			file >> intBuffer >> intBuffer2;
			m_ile.AjouterPersonne(corsaire, m_ile.GetCase(intBuffer, intBuffer2));
			Fenetre->AddDrawableEntity(corsaire->GetSprite());

			file >> strBuffer;
			if (strBuffer == "OUI")
				corsaire->SetPelle(new Pelle);
			file >> strBuffer;
			if (strBuffer == "OUI")
				corsaire->SetMousquet(new Mousquet);
			file >> strBuffer;
			if (strBuffer == "OUI")
				corsaire->SetArmure(new Armure);
		}

		for (int i = 0; i < m_nombrePirate; i++)
		{
			file >> strBuffer;
			if (strBuffer == "Boucanier")
			{
				Boucanier* boucanier = new Boucanier;

				file >> intBuffer >> intBuffer2;
				m_ile.AjouterPersonne(boucanier, m_ile.GetCase(intBuffer, intBuffer2));
				Fenetre->AddDrawableEntity(boucanier->GetSprite());
			}
			else
			{
				Flibustier* flibustier = new Flibustier;

				file >> intBuffer >> intBuffer2;
				m_ile.AjouterPersonne(flibustier, m_ile.GetCase(intBuffer, intBuffer2));
				Fenetre->AddDrawableEntity(flibustier->GetSprite());
			}
		}

		while (!file.eof())
		{
			file >> strBuffer >> intBuffer >> intBuffer2;
			
			if (strBuffer == "PELLE")
			{
				Pelle* pelle = new Pelle;
				m_ile.AjouterObjet(pelle, m_ile.GetCase(intBuffer, intBuffer2));
				Fenetre->AddDrawableChest(pelle->GetSprite());
			}
			else if(strBuffer == "MOUSQUET")
			{
				Mousquet* mousquet = new Mousquet;
				m_ile.AjouterObjet(mousquet, m_ile.GetCase(intBuffer, intBuffer2));
				Fenetre->AddDrawableChest(mousquet->GetSprite());
			}
			else if (strBuffer == "ARMURE")
			{
				Armure* armure = new Armure;
				m_ile.AjouterObjet(armure, m_ile.GetCase(intBuffer, intBuffer2));
				Fenetre->AddDrawableChest(armure->GetSprite());
			}
			else if (strBuffer == "TRESOR")
			{
				m_ile.GetCase(intBuffer, intBuffer2)->AddTresor();
			}
		}

		m_txtInfo = new Text;
		m_txtInfo->setFont(m_font);
		m_txtInfo->setScale(0.5, 0.5);
		m_txtInfo->setCharacterSize(25);
		m_txtInfo->setFillColor(Color::Black);
		m_txtInfo->setString("?");
		m_txtInfo->setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 5, Fenetre->GetWindow()->getView().getCenter().y + 178 / 2);
		Fenetre->AddDrawableText(m_txtInfo);

		m_txtEquipement = new Text;
		m_txtEquipement->setFont(m_font);
		m_txtEquipement->setScale(0.5, 0.5);
		m_txtEquipement->setCharacterSize(30);
		m_txtEquipement->setFillColor(Color::Black);
		m_txtEquipement->setString("?");
		m_txtEquipement->setPosition(Fenetre->GetWindow()->getView().getCenter().x + 192 / 2 + 5, Fenetre->GetWindow()->getView().getCenter().y + 24);
		Fenetre->AddDrawableText(m_txtEquipement);

		m_txtChoixAction = new Text[4];
		for (int i = 0; i < 4; i++)
		{
			m_txtChoixAction[i].setFont(m_font);
			m_txtChoixAction[i].setScale(0.5, 0.5);
			m_txtChoixAction[i].setCharacterSize(30);
			m_txtChoixAction[i].setFillColor(Color::Black);
			m_txtChoixAction[i].setPosition(Fenetre->GetWindow()->getView().getCenter().x - 192 + 5, Fenetre->GetWindow()->getView().getCenter().y + 24 + (14 * i));
			Fenetre->AddDrawableText(&m_txtChoixAction[i]);
		}

		m_txtChoixAction[0].setStyle(Text::Bold);
		m_txtChoixAction[0].setString("Choix Action:");
		m_txtChoixAction[1].setString("> Deplacer");
		m_txtChoixAction[2].setString("> Creuser");
		m_txtChoixAction[3].setString("> Tirer");

		if (!m_musique.openFromFile("assets/music.wav")) { exit(1); }
		m_musique.setLoop(true);

		file.seekg(0,file.beg);
	}
	else
		exit(1);

	file.close();
}
