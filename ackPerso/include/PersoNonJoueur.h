/*
 * PersoNonJoueur.h
 *
 *  Created on:
 *      Author: cephise
 */

#ifndef PERSONONJOUEUR_H_INCLUDED
#define PERSONONJOUEUR_H_INCLUDED

#include <iostream>
#include "AbstractPerso.h"

class PersoNonJoueur: public AbstractPerso
{

public:

	PersoNonJoueur(IrrlichtDevice* device, int init = 0);
	PersoNonJoueur(IrrlichtDevice* device, std::string nom, int init = 0);
	PersoNonJoueur(string infojoueur, IrrlichtDevice* device, int init);
	virtual string talk() {return "";}
	std::string getNom();
	bool getElite();

private:

	bool m_elite; //si le pnj est un élite ou non
	std::string m_Agressivite; //agressivité du pnj
	std::string m_recompense; //objet de récompense par le personnage

};

#endif // PERSONONJOUEUR_H_INCLUDED
