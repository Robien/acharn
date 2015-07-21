/*
 * AbstractObjetEquipable.cpp
 *
 *  Created on: 17 sept. 2010
 *      Author: cephise
 */

#include "../include/AbstractObjetEquipable.h"

AbstractObjetEquipable::AbstractObjetEquipable() :
	AbstractObjet()
{
	m_solidite = 0;
	m_usure = m_solidite;
}

AbstractObjetEquipable::AbstractObjetEquipable(std::string nom, std::string descrip, std::string rare, float val, Caracteristique bon) :
	AbstractObjet(nom, descrip, rare, val), m_bonus(bon)
{
	m_solidite = 0;
	m_usure = m_solidite;
}

AbstractObjetEquipable::AbstractObjetEquipable(std::string infoObjetequi, std::string infoobj, std::string description) :
	m_bonus()
{
	std::vector<std::string> info = split(infoObjetequi.c_str(), ',');
	m_usure = converfl(info[0].c_str());
	m_solidite = converfl(info[1].c_str());
	description += "[" + converstr(m_usure) + "/" + converstr(m_solidite) + "]";
	if (info.size() >= 16)
	{
		info.erase(info.begin());//supprime usure
		info[0] = ""; //change solidité en nom vide
		m_bonus.setAttribut(info);
	}
	else
	{
		//		m_bonus();
	}
	AbstractObjet(infoobj, description);
}

AbstractObjetEquipable::~AbstractObjetEquipable()
{
}

std::string AbstractObjetEquipable::toString()
{
	return AbstractObjet::toString() + "\nBonus:\n" + m_bonus.toString();
}

void AbstractObjetEquipable::setBonus(std::string attri, float valeur)
{
	m_bonus.setAttribut(attri, valeur);
}

Caracteristique AbstractObjetEquipable::getCaracteristique()
{
	return m_bonus;
}

float AbstractObjetEquipable::getUsure()
{
	return m_usure;
}

float AbstractObjetEquipable::getSolidite()
{
	return m_solidite;
}

std::string AbstractObjetEquipable::toSave()
{
	string info = "";
	info = ":" + converstr(m_usure) + ",";
	info += converstr(m_solidite);
	if (m_bonus.isInitialised())
	{
		info += "," + m_bonus.enChaine(true);
	}
	info = info + AbstractObjet::toSave();
	return info;
}
