/*
 * PersoQuete.cpp
 *
 *  Created on: 31 oct. 2010
 *      Author: cephise
 */

#include "../include/PersoQuete.h"

PersoQuete::PersoQuete(IrrlichtDevice* device, int init) :
	PersoNonJoueur(device, init)
{
}

PersoQuete::PersoQuete(IrrlichtDevice* device, std::string nom, int init) :
	PersoNonJoueur(device, nom, init)
{
}

PersoQuete::PersoQuete(string infojoueur, IrrlichtDevice* device, int init) :
	PersoNonJoueur(infojoueur, device, init)
{
}

PersoQuete::~PersoQuete()
{
}

string PersoQuete::talk()
{
    return "Bonjour humble joueur, je n'ai aucune quete a te proposer";
}

vector<AbstractQuete> PersoQuete::getQuetes()
{
return quetes;
}

void PersoQuete::addQuetes(AbstractQuete quete)
{
	quetes.push_back(quete);
}
