/*
 * TacheCreationPerso.h
 *
 *  Created on: 21 juil. 2010
 *      Author: romain
 */

#ifndef TACHECREATIONPERSO_H_
#define TACHECREATIONPERSO_H_
#include "Tache.h"
#include <iostream>

class TacheCreationPerso: public Tache
{
public:

	TacheCreationPerso(int id, float newx, float newy, float newz, int init, std::string infoJoueur);
	virtual ~TacheCreationPerso();
	virtual void execute();

private:

	float _x, _y, _z;
	int _init;
	std::string _infoJoueur;
};

#endif /* TACHECREATIONPERSO_H_ */
