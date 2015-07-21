/*
 * TacheSetAttaque.h
 *
 *  Created on: 30 oct. 2010
 *      Author: cephise
 */

#ifndef TACHESETATTAQUE_H_
#define TACHESETATTAQUE_H_

#include "Tache.h"
#include "Interpreteur.h"
#include "Attaque.h"
#include "string"

using namespace std;

class TacheSetAttaque: public Tache
{

public:
	TacheSetAttaque(int idD, string Competence, int idS = -1);
	virtual ~TacheSetAttaque();
	void execute();

private:
	int idSource;
	string m_attaque;

};

#endif /* TACHESETATTAQUE_H_ */
