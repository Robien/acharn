/*
 * PersoNonJoueur.h
 *
 *  Created on:
 *      Author: cephise
 */

#include "PersoNonJoueur.h"

using namespace std;

PersoNonJoueur::PersoNonJoueur(IrrlichtDevice* device, int init) :
	AbstractPerso(device, init), m_elite(false)
{
}

PersoNonJoueur::PersoNonJoueur(IrrlichtDevice* device, std::string nom, int init) :
	AbstractPerso(device, nom, init), m_elite(false)
{
}

PersoNonJoueur::PersoNonJoueur(string infojoueur, IrrlichtDevice* device, int init) :
	AbstractPerso(infojoueur, device, init), m_elite(false)
{
}


std::string PersoNonJoueur::getNom()
{
	string nom = AbstractPerso::getNom();
	if (m_elite)
		nom += "*";

	return nom;
}

bool PersoNonJoueur::getElite()
{
	return m_elite;
}

