#include <iostream>
#include "AbstractObjet.h"
#include "const.h"

using namespace std;

AbstractObjet::AbstractObjet() :
	m_nom("Objet inconnu"), m_description(""), m_rarete(""), m_valeur(0)
{
}

AbstractObjet::AbstractObjet(std::string nom, std::string descrip, std::string rare, float val) :
	m_nom(nom), m_description(descrip), m_rarete(rare), m_valeur(val)
{
}

AbstractObjet::AbstractObjet(string info, string description)
{
	vector<string> infoob = split(info.c_str(), ',');
	m_nom = infoob[0];
	m_description = m_nom + " " + description;
	m_rarete = infoob[1].c_str();
	m_valeur = converfl(infoob[2].c_str());
}

std::string AbstractObjet::toString()
{
	return getNom() + " (" + getRarete() + ")\n" + getDescription() + "\nprix:" + converstr(getValeur());
	//return getNom() + " ("+getRarete()+")\n" + getDescription() +"\nprix:";
}

std::string AbstractObjet::getNom()
{
	return m_nom;
}

std::string AbstractObjet::getDescription()
{
	return m_description;
}

std::string AbstractObjet::getRarete()
{
	return m_rarete;
}

float AbstractObjet::getValeur()
{
	return m_valeur;
}

std::string AbstractObjet::toSave()
{
	string info = "";
	info = ":" + m_nom + ",";
	info += m_rarete + ",";
	info += converstr(m_valeur);
	return info;
}
