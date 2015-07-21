#include "ObjetEquipement.h"
#include <string>
#include "Caracteristique.h"
using namespace std;
#include "const.h"
#include "../include/ObjetEquipement.h"

ObjetEquipement::ObjetEquipement() :
	AbstractObjetEquipable()
{
	m_armure = 0;
	m_armureMagique = 0;
}

ObjetEquipement::ObjetEquipement(std::string nom, std::string descrip, std::string rare, float val, Caracteristique bon, e_Position tpequi) :
	AbstractObjetEquipable(nom, descrip, rare, val, bon), typeEquipe(tpequi)
{
	m_armure = 0;
	m_armureMagique = 0;

}

ObjetEquipement::ObjetEquipement(string infoObjet)

{
	vector<string> info = split(infoObjet.c_str(), ':');
	vector<string> infoequipe = split(info[1].c_str(), ',');
	typeEquipe = (ObjetEquipement::e_Position) converint(infoequipe[0].c_str());
	m_armure = converint(infoequipe[1].c_str());
	m_armureMagique = converint(infoequipe[2].c_str());
	string description = "Equipement (" + converstr((int) getTypeEquipe()) + ") Armure: " + converstr(m_armure) + "Armure Magique:" + converstr(m_armureMagique);
	AbstractObjetEquipable(info[2], info[3], description);

}

ObjetEquipement::e_Position ObjetEquipement::getTypeEquipe()
{
	return typeEquipe;
}

float ObjetEquipement::getArmure()
{
	return m_armure;
}
float ObjetEquipement::getArmureMagique()
{
	return m_armureMagique;
}

std::string ObjetEquipement::toSave()
{
	string info = "2";
	info = ":" + converstr((int) typeEquipe) + ",";
	info += converstr(m_armure) + ",";
	info += converstr(m_armureMagique);
	info = info + AbstractObjetEquipable::toSave();
	return info;
}
