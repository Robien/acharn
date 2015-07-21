/*
 * ObjetConsommable.cpp
 *
 *  Created on: 19 sept. 2010
 *      Author: cephise
 */

#include "../include/ObjetConsommable.h"

ObjetConsommable::ObjetConsommable():AbstractObjSimple(), m_effet()
{
	// TODO Auto-generated constructor stub

}

ObjetConsommable::ObjetConsommable(string infoObjet)
{
		vector<string> info =split(infoObjet.c_str(),':');
		m_effet = info[1];
		AbstractObjSimple("consommable",info[3]);
}

ObjetConsommable::~ObjetConsommable()
{
	// TODO Auto-generated destructor stub
}

std::string ObjetConsommable::toSave()
{
	string info= "10:" + m_effet;
	return info+ AbstractObjet::toSave();
}
