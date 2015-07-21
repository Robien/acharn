/*
 * PersoQuete.h
 *
 *  Created on: 31 oct. 2010
 *      Author: cephise
 */

#ifndef PERSOQUETE_H_
#define PERSOQUETE_H_

#include "PersoNonJoueur.h"
#include "AbstractQuete.h"

class PersoQuete: public PersoNonJoueur
{

public:

	PersoQuete(IrrlichtDevice* device, int init = 0);
	PersoQuete(IrrlichtDevice* device, std::string nom, int init = 0);
	PersoQuete(string infojoueur, IrrlichtDevice* device, int init= 0);
	string talk();

	virtual ~PersoQuete();

	vector<AbstractQuete> getQuetes();
	void addQuetes(AbstractQuete quete);

	private:

	vector<AbstractQuete> quetes;

};

#endif /* PERSOQUETE_H_ */
