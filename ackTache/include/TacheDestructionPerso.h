/*
 * TacheDestructionPerso.h
 *
 *  Created on: 5 août 2010
 *      Author: romain
 */

#ifndef TACHEDESTRUCTIONPERSO_H_
#define TACHEDESTRUCTIONPERSO_H_

#include "Tache.h"

class TacheDestructionPerso: public Tache
{
public:
	TacheDestructionPerso(int id);
	virtual ~TacheDestructionPerso(); //destructeur du destructeur a ne pas confondre avec le constructeur du destructeur, ni avec le constructeur du constructeur et le destructeur du constructeur dans TacheCreationPerso :)
	void execute();
};

#endif /* TACHEDESTRUCTIONPERSO_H_ */
