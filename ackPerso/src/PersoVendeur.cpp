/*
 * PersoVendeur.cpp
 *
 *  Created on: 31 oct. 2010
 *      Author: cephise
 */

#include "../include/PersoVendeur.h"
using namespace irr;

PersoVendeur::PersoVendeur(IrrlichtDevice* device, vector<std::string> lesobjets, int init) :
	PersoNonJoueur(device, init)
{
	objets = lesobjets;
}

PersoVendeur::PersoVendeur(IrrlichtDevice* device, std::string nom, vector<std::string> lesobjets, int init) :
	PersoNonJoueur(device, nom, init)
{
	objets = lesobjets;
}

PersoVendeur::PersoVendeur(string infojoueur, IrrlichtDevice* device, vector<std::string> lesobjets, int init) :
	PersoNonJoueur(infojoueur, device, init)
{
	objets = lesobjets;
}

PersoVendeur::PersoVendeur(string infojoueur, IrrlichtDevice* device, int init) :
	PersoNonJoueur(infojoueur, device, init)
{

}

PersoVendeur::~PersoVendeur()
{
}

string PersoVendeur::talk()
{
    return "Bonjour humble joueur, je n'ai rien à te vendre";
}

vector<string> PersoVendeur::getObjet()
{
	return objets;
}
