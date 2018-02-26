#include "Plateau.h"


Plateau::Plateau()
{
	srand(time(NULL));

	//arrière plan du plateau
	m_tOcean.loadFromFile("assets/bg_ocean.png", IntRect(0, 0, 384 * 6, 216 * 10));
	m_sOcean.setTexture(m_tOcean);
	m_sOcean.setScale(0.17, 0.1);
	m_sOcean.setPosition(0, 0);

	//création des cases du plateau
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			m_tabCase[i][j].SetPosition(j*m_tailleCase + 384 / 4, i*m_tailleCase + 5);
		}
	}
}


Plateau::~Plateau()
{
	vectPersonne.clear();
	vectObjet.clear();
}

void Plateau::AjouterPersonne(Personne * personne, Case* tile)
{
	vectPersonne.push_back(personne);
	personne->GetSprite()->setPosition(tile->GetSprite()->getPosition().x, tile->GetSprite()->getPosition().y - 8);
	tile->SetPersonne(personne);
}

void Plateau::AjouterObjet(Objet * objet, Case * tile)
{
	vectObjet.push_back(objet);
	objet->GetSprite()->setPosition(tile->GetSprite()->getPosition().x, tile->GetSprite()->getPosition().y - 8);
	tile->SetObjet(objet);
}

bool Plateau::DeplacerCorsaire(int id, Plateau::eDirection dir)
{
	int buffX = 0, buffY = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (m_tabCase[i][j].GetPersonne() == vectPersonne.at(id))
			{
				buffX = i;
				buffY = j;
				i = 12;
				j = 12;
			}
		}
	}


	//deplace le corsaire dans la direction demandé
	switch (dir)
	{
	case Plateau::HAUT:
		if (buffX > 0)
			return Deplacement(id, buffX, buffY, buffX - 1, buffY);
		break;
	case Plateau::BAS:
		if (buffX < 11)
			return Deplacement(id, buffX, buffY, buffX + 1, buffY);
		break;
	case Plateau::GAUCHE:
		if (buffY > 0)
			return Deplacement(id, buffX, buffY, buffX, buffY - 1);
		break;
	case Plateau::DROITE:
		if (buffY < 11)
			return Deplacement(id, buffX, buffY, buffX, buffY + 1);
		break;
	case Plateau::HG:
		if (buffX > 0 && buffY > 0)
			return Deplacement(id, buffX, buffY, buffX - 1, buffY - 1);
		break;
	case Plateau::HD:
		if (buffX > 0 && buffY < 11)
			return Deplacement(id, buffX, buffY, buffX - 1, buffY + 1);
		break;
	case Plateau::BG:
		if (buffX < 11 && buffY > 0)
			return Deplacement(id, buffX, buffY, buffX + 1, buffY - 1);
		break;
	case Plateau::BD:
		if (buffX < 11 && buffY < 11)
			return Deplacement(id, buffX, buffY, buffX + 1, buffY + 1);
		break;
	default:
		break;
	}
	return false;
}

bool Plateau::DeplacerPirate(int id)
{
	int buffX = 0, buffY = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (m_tabCase[i][j].GetPersonne() == vectPersonne.at(id))
			{
				buffX = i;
				buffY = j;
				i = 12;
				j = 12;
			}
		}
	}

	Plateau::eDirection dir = Plateau::eDirection(rand() % 8);


	//deplace le pirate dans une direction aléatoire
	switch (dir)
	{
	case Plateau::HAUT:
		if (buffX > 0)
			return Deplacement(id, buffX, buffY, buffX - 1, buffY);
		break;
	case Plateau::BAS:
		if (buffX < 11)
			return Deplacement(id, buffX, buffY, buffX + 1, buffY);
		break;
	case Plateau::GAUCHE:
		if (buffY > 0)
			return Deplacement(id, buffX, buffY, buffX, buffY - 1);
		break;
	case Plateau::DROITE:
		if (buffY < 11)
			return Deplacement(id, buffX, buffY, buffX, buffY + 1);
		break;
	case Plateau::HG:
		if (buffX > 0 && buffY > 0)
			return Deplacement(id, buffX, buffY, buffX - 1, buffY - 1);
		break;
	case Plateau::HD:
		if (buffX > 0 && buffY < 11)
			return Deplacement(id, buffX, buffY, buffX - 1, buffY + 1);
		break;
	case Plateau::BG:
		if (buffX < 11 && buffY > 0)
			return Deplacement(id, buffX, buffY, buffX + 1, buffY - 1);
		break;
	case Plateau::BD:
		if (buffX < 11 && buffY < 11)
			return Deplacement(id, buffX, buffY, buffX + 1, buffY + 1);
		break;
	default:
		break;
	}
	return false;
}

bool Plateau::Deplacement(int id, int buffX, int buffY, int moveX, int moveY)
{
	//déplacement corsaire
	if (m_tabCase[buffX][buffY].GetPersonne()->Type() == "Corsaire")
	{
		///si la case on l'on veut se déplacer est vide
		if (m_tabCase[moveX][moveY].GetPersonne() == NULL)
		{
			m_tabCase[buffX][buffY].SetPersonne(NULL);
			vectPersonne.at(id)->GetSprite()->setPosition(m_tabCase[moveX][moveY].GetSprite()->getPosition().x, m_tabCase[moveX][moveY].GetSprite()->getPosition().y - 8);
			m_tabCase[moveX][moveY].SetPersonne(vectPersonne.at(id));
			return true;
		}
		///si la case on l'on veut se déplacer contient un pirate
		else if (m_tabCase[moveX][moveY].GetPersonne()->Type() != "Corsaire")
		{
			Duel(false, id, buffX, buffY, moveX, moveY);
			return true;
		}
		///sinon on ne bouge pas
	}
	//déplacement pirate
	else
	{
		///si la case on l'on veut se déplacer est vide
		if (m_tabCase[moveX][moveY].GetPersonne() == NULL)
		{
			m_tabCase[buffX][buffY].SetPersonne(NULL);
			vectPersonne.at(id)->GetSprite()->setPosition(m_tabCase[moveX][moveY].GetSprite()->getPosition().x, m_tabCase[moveX][moveY].GetSprite()->getPosition().y - 8);
			m_tabCase[moveX][moveY].SetPersonne(vectPersonne.at(id));
			return true;
		}
		///si la case on l'on veut se déplacer contient un corsaire
		else if (m_tabCase[moveX][moveY].GetPersonne()->Type() != "Boucanier" && m_tabCase[moveX][moveY].GetPersonne()->Type() != "Flibustier")
		{
			Duel(false, id, buffX, buffY, moveX, moveY);
			return true;
		}
		///sinon on ne bouge pas
	}
	return false;
}

void Plateau::Duel(bool distance, int id, int buffX, int buffY, int moveX, int moveY)
{
	Personne* source = vectPersonne.at(id);
	Personne* cible = m_tabCase[moveX][moveY].GetPersonne();

	Corsaire* corsaire_source = (Corsaire*)source;
	Corsaire* corsaire_cible = (Corsaire*)cible;

	//si l'attaquant gagne
	if (source->Attaquer(cible->ChanceSurvie()))
	{
		if (!distance)
		{
			if (source->Type() == "Corsaire")
				m_str_info = corsaire_source->GetNom() + " attaque a courte portee " + cible->Type() + " et gagne le duel!";
			else if (cible->Type() == "Corsaire")
				m_str_info = source->Type() + " attaque a courte portee " + corsaire_cible->GetNom() + " et gagne le duel!";
		}
		else
		{
			if (source->Type() == "Corsaire")
				m_str_info = corsaire_source->GetNom() + " attaque a longue portee " + cible->Type() + " et gagne le duel!";
			else if (cible->Type() == "Corsaire")
				m_str_info = source->Type() + " attaque a longue portee " + corsaire_cible->GetNom() + " et gagne le duel!";
		}

		if (!distance)
		{
			m_tabCase[buffX][buffY].SetPersonne(NULL);
			source->GetSprite()->setPosition(m_tabCase[moveX][moveY].GetSprite()->getPosition().x, m_tabCase[moveX][moveY].GetSprite()->getPosition().y - 8);
		}

		for (int i = 0; i < vectPersonne.size(); i++)
		{
			if (vectPersonne.at(i) == cible)
			{
				vectPersonne.erase(vectPersonne.begin() + i);
				m_eraseIndex = i;
				i = vectPersonne.size();
			}
		}

		if (!distance)
			m_tabCase[moveX][moveY].SetPersonne(source);
		else
			m_tabCase[moveX][moveY].SetPersonne(NULL);

		m_attendre = true;
	}
	//si l'attaquant perd
	else
	{
		if (!distance)
		{
			if (source->Type() == "Corsaire")
				m_str_info = corsaire_source->GetNom() + " attaque a courte portee " + cible->Type() + " et perd le duel..";
			else if (cible->Type() == "Corsaire")
				m_str_info = source->Type() + " attaque a courte portee " + corsaire_cible->GetNom() + " et perd le duel..";
		}
		else
		{
			if (source->Type() == "Corsaire")
				m_str_info = corsaire_source->GetNom() + " attaque a longue portee " + cible->Type() + " et perd le duel..";
			else if (cible->Type() == "Corsaire")
				m_str_info = source->Type() + " attaque a longue portee " + corsaire_cible->GetNom() + " et perd le duel..";
		}

		m_tabCase[buffX][buffY].SetPersonne(NULL);
		vectPersonne.erase(vectPersonne.begin() + id);
		m_eraseIndex = id;
		m_attendre = true;
	}
	m_attendre = true;
}

bool Plateau::CheckCaseActuelle(int id)
{
	int buffX = 0, buffY = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (m_tabCase[i][j].GetPersonne() == vectPersonne.at(id))
			{
				buffX = i;
				buffY = j;
				i = 12;
				j = 12;
			}
		}
	}

	if (m_tabCase[buffX][buffY].GetPelle() != NULL)
	{
		Corsaire* corsaire = (Corsaire*)vectPersonne.at(id);

		if (corsaire->GetPelle() != NULL)
		{
			m_str_info = corsaire->GetNom() + " a trouve une autre pelle! Il la repose...";
		}
		else
		{
			corsaire->SetPelle(m_tabCase[buffX][buffY].GetPelle());
			m_tabCase[buffX][buffY].GetPelle()->SetDansUnCoffre(false);
			m_tabCase[buffX][buffY].SetPelle(NULL);
			m_str_info = corsaire->GetNom() + " a recupere une pelle!";
		}
		m_attendre = true;
	}

	if (m_tabCase[buffX][buffY].GetMousquet() != NULL)
	{
		Corsaire* corsaire = (Corsaire*)vectPersonne.at(id);

		if (corsaire->GetMousquet() != NULL)
		{
			m_str_info = corsaire->GetNom() + " a trouve un autre mousquet! Il le repose...";
		}
		else
		{
			corsaire->SetMousquet(m_tabCase[buffX][buffY].GetMousquet());
			m_tabCase[buffX][buffY].GetMousquet()->SetDansUnCoffre(false);
			m_tabCase[buffX][buffY].SetMousquet(NULL);
			m_str_info = corsaire->GetNom() + " a recupere un mousquet!";
		}
		m_attendre = true;
	}

	if (m_tabCase[buffX][buffY].GetArmure() != NULL)
	{
		Corsaire* corsaire = (Corsaire*)vectPersonne.at(id);

		if (corsaire->GetArmure() != NULL)
		{
			m_str_info = corsaire->GetNom() + " a trouve une autre armure! Il la repose...";
		}
		else
		{
			corsaire->SetArmure(m_tabCase[buffX][buffY].GetArmure());
			m_tabCase[buffX][buffY].GetArmure()->SetDansUnCoffre(false);
			m_tabCase[buffX][buffY].SetArmure(NULL);
			m_str_info = corsaire->GetNom() + " a recupere une armure!";
		}
		m_attendre = true;
	}
	return true;
}

bool Plateau::CheckCasesAutour(int id)
{
	int buffX = 0, buffY = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (m_tabCase[i][j].GetPersonne() == vectPersonne.at(id))
			{
				buffX = i;
				buffY = j;
				i = 12;
				j = 12;
			}
		}
	}

#pragma region /*definition d'une matrice en fonction de la position de la personne*/

	int nbCases = 8;
	int dataCases[8][2];

	dataCases[0][0] = buffX - 1;		//commence dans le coin haut gauche et tourne dans le sens horaire
	dataCases[0][1] = buffY - 1;
	dataCases[1][0] = buffX - 1;
	dataCases[1][1] = buffY;
	dataCases[2][0] = buffX - 1;
	dataCases[2][1] = buffY + 1;
	dataCases[3][0] = buffX;
	dataCases[3][1] = buffY + 1;
	dataCases[4][0] = buffX + 1;
	dataCases[4][1] = buffY + 1;
	dataCases[5][0] = buffX + 1;
	dataCases[5][1] = buffY;
	dataCases[6][0] = buffX + 1;
	dataCases[6][1] = buffY - 1;
	dataCases[7][0] = buffX;
	dataCases[7][1] = buffY - 1;

	int** cases;

	if (buffX == 0 && buffY == 0)
	{
		nbCases = 3;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[3][0];
		cases[0][1] = dataCases[3][1];
		cases[1][0] = dataCases[4][0];
		cases[1][1] = dataCases[4][1];
		cases[2][0] = dataCases[5][0];
		cases[2][1] = dataCases[5][1];
	}
	else if (buffX == 0 && buffY == 11)
	{
		nbCases = 3;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[5][0];
		cases[0][1] = dataCases[5][1];
		cases[1][0] = dataCases[6][0];
		cases[1][1] = dataCases[6][1];
		cases[2][0] = dataCases[7][0];
		cases[2][1] = dataCases[7][1];
	}
	else if (buffX == 11 && buffY == 0)
	{
		nbCases = 3;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[1][0];
		cases[0][1] = dataCases[1][1];
		cases[1][0] = dataCases[2][0];
		cases[1][1] = dataCases[2][1];
		cases[2][0] = dataCases[3][0];
		cases[2][1] = dataCases[3][1];
	}
	else if (buffX == 11 && buffY == 11)
	{
		nbCases = 3;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[7][0];
		cases[0][1] = dataCases[7][1];
		cases[1][0] = dataCases[0][0];
		cases[1][1] = dataCases[0][1];
		cases[2][0] = dataCases[1][0];
		cases[2][1] = dataCases[1][1];
	}
	else if (buffX == 0)
	{
		nbCases = 5;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[3][0];
		cases[0][1] = dataCases[3][1];
		cases[1][0] = dataCases[4][0];
		cases[1][1] = dataCases[4][1];
		cases[2][0] = dataCases[5][0];
		cases[2][1] = dataCases[5][1];
		cases[3][0] = dataCases[6][0];
		cases[3][1] = dataCases[6][1];
		cases[4][0] = dataCases[7][0];
		cases[4][1] = dataCases[7][1];
	}
	else if (buffX == 11)
	{
		nbCases = 5;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[7][0];
		cases[0][1] = dataCases[7][1];
		cases[1][0] = dataCases[0][0];
		cases[1][1] = dataCases[0][1];
		cases[2][0] = dataCases[1][0];
		cases[2][1] = dataCases[1][1];
		cases[3][0] = dataCases[2][0];
		cases[3][1] = dataCases[2][1];
		cases[4][0] = dataCases[3][0];
		cases[4][1] = dataCases[3][1];
	}
	else if (buffY == 0)
	{
		nbCases = 5;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[1][0];
		cases[0][1] = dataCases[1][1];
		cases[1][0] = dataCases[2][0];
		cases[1][1] = dataCases[2][1];
		cases[2][0] = dataCases[3][0];
		cases[2][1] = dataCases[3][1];
		cases[3][0] = dataCases[4][0];
		cases[3][1] = dataCases[4][1];
		cases[4][0] = dataCases[5][0];
		cases[4][1] = dataCases[5][1];
	}
	else if (buffY == 11)
	{
		nbCases = 5;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
			cases[i] = new int[2];
		cases[0][0] = dataCases[5][0];
		cases[0][1] = dataCases[5][1];
		cases[1][0] = dataCases[6][0];
		cases[1][1] = dataCases[6][1];
		cases[2][0] = dataCases[7][0];
		cases[2][1] = dataCases[7][1];
		cases[3][0] = dataCases[0][0];
		cases[3][1] = dataCases[0][1];
		cases[4][0] = dataCases[1][0];
		cases[4][1] = dataCases[1][1];
	}
	else
	{
		nbCases = 8;
		cases = new int*[nbCases];
		for (int i = 0; i < nbCases; i++)
		{
			cases[i] = new int[2];
			cases[i][0] = dataCases[i][0];
			cases[i][1] = dataCases[i][1];
		}
	}

#pragma endregion


	bool* casesCheck = new bool[nbCases];
	for (int i = 0; i < nbCases; i++)
		casesCheck[i] = false;
	int buffer = 0;
	int alea = 0;
	bool loop = true;

	//ici on va regarder toutes les cases autour de la personne de manière aléatoire et une seule et unique fois
	while (loop)
	{
		alea = rand() % nbCases;
		if (!casesCheck[alea])
		{
			if (m_tabCase[cases[alea][0]][cases[alea][1]].GetPersonne() != NULL)
			{
				//si la case qu'on a regardé contient un corsaire, on lui tire dessus et on sort de la boucle
				if (m_tabCase[cases[alea][0]][cases[alea][1]].GetPersonne()->Type() == "Corsaire")
				{
					int moveX = cases[alea][0];
					int moveY = cases[alea][1];

					Duel(true, id, buffX, buffY, moveX, moveY);

					return true;
				}
			}
			casesCheck[alea] = true;
		}

		buffer = 0;
		for (int i = 0; i < nbCases; i++)
		{
			if (casesCheck[i])
				buffer++;
		}

		if (buffer == nbCases)
			loop = false;
	}
	return false;
}

bool Plateau::Tirer(int id, Plateau::eDirection dir)
{
	int buffX = 0, buffY = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (m_tabCase[i][j].GetPersonne() == vectPersonne.at(id))
			{
				buffX = i;
				buffY = j;
				i = 12;
				j = 12;
			}
		}
	}

	//tire sur la position choisi par le corsaire
	switch (dir)
	{
	case Plateau::HAUT:
		if (buffX > 0)
		{
			if (m_tabCase[buffX - 1][buffY].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX - 1, buffY);
				return true;
			}
		}
		break;
	case Plateau::BAS:
		if (buffX < 11)
		{
			if (m_tabCase[buffX + 1][buffY].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX + 1, buffY);
				return true;
			}
		}
		break;
	case Plateau::GAUCHE:
		if (buffY > 0)
		{
			if (m_tabCase[buffX][buffY - 1].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX, buffY - 1);
				return true;
			}
		}
		break;
	case Plateau::DROITE:
		if (buffY < 11)
		{
			if (m_tabCase[buffX][buffY + 1].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX, buffY + 1);
				return true;
			}
		}
		break;
	case Plateau::HG:
		if (buffX > 0 && buffY > 0)
		{
			if (m_tabCase[buffX - 1][buffY - 1].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX - 1, buffY - 1);
				return true;
			}
		}
		break;
	case Plateau::HD:
		if (buffX > 0 && buffY < 11)
		{
			if (m_tabCase[buffX - 1][buffY + 1].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX - 1, buffY + 1);
				return true;
			}
		}
		break;
	case Plateau::BG:
		if (buffX < 11 && buffY > 0)
		{
			if (m_tabCase[buffX + 1][buffY - 1].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX + 1, buffY - 1);
				return true;
			}
		}
		break;
	case Plateau::BD:
		if (buffX < 11 && buffY < 11)
		{
			if (m_tabCase[buffX + 1][buffY + 1].GetPersonne() != NULL)
			{
				Duel(true, id, buffX, buffY, buffX + 1, buffY + 1);
				return true;
			}
		}
		break;
	default:
		break;
	}
	m_str_info = " il n'y a pas de cible a cette position...";
	m_attendre = true;
	return false;
}

void Plateau::CheckTresor(int id)
{
	int buffX = 0, buffY = 0;
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (m_tabCase[i][j].GetPersonne() == vectPersonne.at(id))
			{
				buffX = i;
				buffY = j;
				i = 12;
				j = 12;
			}
		}
	}

	Corsaire* corsaire = (Corsaire*)vectPersonne.at(id);

	//si le joueur a une pelle
	if (corsaire->GetPelle() != NULL)
	{
		//si la case contient un tresor, le corsaire le récupère
		if (m_tabCase[buffX][buffY].GetTresor() != NULL)
		{
			corsaire->SetTresor(m_tabCase[buffX][buffY].GetTresor());
			m_str_info = corsaire->GetNom() + " a trouve le tresor!";
		}
		else
		{
			m_str_info = corsaire->GetNom() + " n'a rien trouve ici..";
		}
		m_attendre = true;
	}
}

void Plateau::SetInfo(string str)
{
	m_str_info = str;
}

string Plateau::GetInfo()
{
	return m_str_info;
}

string Plateau::GetEquipement(int id)
{
	if (vectPersonne.at(id)->Type() == "Corsaire")
	{
		Corsaire* corsaire = (Corsaire*)vectPersonne.at(id);
		m_str_equipement = "<" + corsaire->GetNom() + ">\n";

		if (corsaire->GetPelle() == NULL)
			m_str_equipement += "Pelle : NON\n";
		else
			m_str_equipement += "Pelle : OUI\n";

		if (corsaire->GetMousquet() == NULL)
			m_str_equipement += "Mousquet : NON\n";
		else
			m_str_equipement += "Mousquet : OUI\n";

		if (corsaire->GetArmure() == NULL)
			m_str_equipement += "Armure : NON\n";
		else
			m_str_equipement += "Armure : OUI\n";
	}
	else
	{
		m_str_equipement = "<Pirate>";
	}

	return m_str_equipement;
}

void Plateau::SetAttendre(bool att)
{
	m_attendre = att;
}

bool Plateau::GetAttendre()
{
	return m_attendre;
}

void Plateau::SetEraseIndex(int id)
{
	m_eraseIndex = id;
}

int Plateau::GetEraseIndex()
{
	return m_eraseIndex;
}

Sprite * Plateau::GetOceanSprite()
{
	return &m_sOcean;
}

Case * Plateau::GetCase(int x, int y)
{
	return &m_tabCase[x][y];
}

vector<Personne*> Plateau::GetVectPersonne()
{
	return vectPersonne;
}

Personne * Plateau::GetPersonne(int id)
{
	return vectPersonne.at(id);
}
