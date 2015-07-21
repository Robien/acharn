/*
 * PersoVendeur.h
 *
 *  Created on: 31 oct. 2010
 *      Author: cephise
 */

#ifndef PERSOVENDEUR_H_
#define PERSOVENDEUR_H_

#include "PersoNonJoueur.h"
#include <vector>
#include "string"

using namespace std;

class PersoVendeur: public PersoNonJoueur
{

public:

	PersoVendeur(IrrlichtDevice* device, vector<std::string> lesobjets, int init = 0);
	PersoVendeur(IrrlichtDevice* device, std::string nom, vector<std::string> lesobjets, int init = 0);
	PersoVendeur(string infojoueur, IrrlichtDevice* device, vector<std::string> lesobjets, int init=0);
	PersoVendeur(string infojoueur, IrrlichtDevice* device, int init=0);
	string talk();
	virtual ~PersoVendeur();

	vector<string> getObjet();

private:

	vector<string> objets;

};

#endif /* PERSOVENDEUR_H_ */
