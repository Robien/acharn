/*
 * TacheSetAttaque.cpp
 *
 *  Created on: 30 oct. 2010
 *      Author: cephise
 */

#include "../include/TacheSetAttaque.h"
#include "../include/PersoManager.h"

TacheSetAttaque::TacheSetAttaque(int idD, string competence, int idS) :
	Tache(idD), idSource(idS), m_attaque(competence)
{
	// TODO Auto-generated constructor stub

}

TacheSetAttaque::~TacheSetAttaque()
{
	// TODO Auto-generated destructor stub
}

void TacheSetAttaque::execute()
{
	string rp = "";
	Interpreteur* interp =  NULL;
	if (idSource == 0) //main joueur est a l'orignine du piege
	{
		if (Tache::_id == 0)
		{
			interp = new Interpreteur(PersoManager::get()->getMainPerso()->getCaracteristique(), PersoManager::get()->getMainPerso()->getRandom(), PersoManager::get()->getMainPerso()->getCaracteristique(),
					m_attaque);
		}
		else
		{
			interp = new Interpreteur(PersoManager::get()->getMainPerso()->getCaracteristique(), PersoManager::get()->getMainPerso()->getRandom(),PersoManager::get()->getPersoById(Tache::_id)->getCaracteristique(), m_attaque);
		}
	}
	else if (idSource == -1)
	//source inconnu (l'attaque ne doit comporter ni caracteristique de la source ni de random
	{
		if (Tache::_id == 0)
		{
			interp = new Interpreteur(new Caracteristique(), NULL, PersoManager::get()->getMainPerso()->getCaracteristique(), m_attaque);
		}
		else
		{
			interp = new Interpreteur(new Caracteristique(), NULL, PersoManager::get()->getPersoById(Tache::_id)->getCaracteristique(), m_attaque);
		}
	}
	else
	{
		if (Tache::_id == 0)
		{
			interp = new Interpreteur(PersoManager::get()->getPersoById(idSource)->getCaracteristique(), PersoManager::get()->getPersoById(idSource)->getRandom(),PersoManager::get()->getMainPerso()->getCaracteristique(), m_attaque);
		}
		else
		{
			interp = new Interpreteur(PersoManager::get()->getPersoById(idSource)->getCaracteristique(), PersoManager::get()->getPersoById(idSource)->getRandom(), PersoManager::get()->getPersoById(Tache::_id)->getCaracteristique(), m_attaque);
		}
	}

	Attaque atk = (*(Attaque*) interp->analyse());
	rp = interp->getAttaqueString();

	if (rp != "")
	{
		cout << "PIEGE: " << endl;
		atk.afficheInfos();
		const float time = PersoManager::get()->getMainPerso()->getDevice()->getTimer()->getTime()/1000;

		if (Tache::_id == 0)
		{
			PersoManager::get()->getMainPerso()->affecte(atk, time);
		}
		else
		{
			PersoManager::get()->getPersoById(Tache::_id)->affecte(atk, time);
		}

		if (interp->isReverse())
		{
			cout << "Le piege a une attaque reverse" << endl;
			if (Tache::_id == 0)
			{
				PersoManager::get()->getMainPerso()->affecte((*(Attaque*) interp->getReverse()), time);
			}
			else
			{
				PersoManager::get()->getPersoById(Tache::_id)->affecte((*(Attaque*) interp->getReverse()), time);
			}
		}
	}

}
