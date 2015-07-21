#include <iostream>
#include "AbstractArme.h"

using namespace std;

//constructeur
AbstractArme::AbstractArme() :
	AbstractObjetEquipable(), m_type(AbstractArme::COUTEAU), m_puissance(0), m_recharge(1), m_portee(1), m_poids(1)
{

}

AbstractArme::AbstractArme(string nom, Caracteristique carac, e_Type type, float degats, float rechg, float portee)
{
	m_type = type;
	m_puissance = degats;
	m_recharge = rechg;
	m_portee = portee;

	string descrip = "Arme : " + nom + " (" + getTypeStr() + ")";
	AbstractObjetEquipable(nom, descrip, "", 0, carac);

}

AbstractArme::AbstractArme(string infoArme, string infoObjetequi, string infoObjet)
{
	vector<string> info = split(infoArme.c_str(), ',');
	m_type=(AbstractArme::e_Type) converint(info[0].c_str());
	m_puissance = converfl(info[1].c_str());
	m_recharge = converfl(info[2].c_str());
	m_portee = converfl(info[3].c_str());
	m_poids = converfl(info[4].c_str());
	string description = "Arme (" + getTypeStr() + ") puissance: " + converstr(m_puissance);
	AbstractObjetEquipable(infoObjetequi, infoObjet, description);
}

//methode de AbstractArme

void AbstractArme::afficher()
{
	cout << "Arme : " << getNom() << " (" << getTypeStr() << ")(puissance : " << m_puissance << ")" << endl;
	cout << AbstractObjetEquipable::toString() << endl;
}

string AbstractArme::getTypeStr()
{
	string retour;
	switch (m_type)
	{
	case EPEE:
		retour = "epee";
		break;
	case HACHE:
		retour = "hache";
		break;
	case BATON:
		retour = "baton";
		break;
	case COUTEAU:
		retour = "couteau";
		break;
	case ARC:
		retour = "arc";
		break;
	case ARBALETTE:
		retour = "arbalette";
		break;
	case FUSIL:
		retour = "fusil";
		break;
	default:
		retour = "inconnu";
		break;
	}
	return retour;
}

AbstractArme::~AbstractArme()
{
}

//setter


float AbstractArme::getPuissance()
{
	return m_puissance;
}

float AbstractArme::getRecharge()
{
	return m_recharge;
}

float AbstractArme::getPortee()
{
	return m_portee;
}

float AbstractArme::getPoids()
{
	return m_poids;
}

AbstractArme::e_Type AbstractArme::getType()
{
	return m_type;
}


std::string AbstractArme::toSave()
{
	string info = "";
	info = ":" + converstr((int)m_type) + ",";
	info += converstr(m_puissance) + ",";
	info += converstr(m_recharge) + ",";
	info += converstr(m_portee) + ",";
	info += converstr(m_poids);
	info = info + AbstractObjetEquipable::toSave();
	return info;
}
