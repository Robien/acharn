/*
 * TacheDestructionPerso.cpp
 *
 *  Created on: 5 août 2010
 *      Author: romain
 */

#include "../include/TacheDestructionPerso.h"
#include "../include/PersoManager.h"

TacheDestructionPerso::TacheDestructionPerso(int id) : Tache(id)
{

}

TacheDestructionPerso::~TacheDestructionPerso()
{
}


void TacheDestructionPerso::execute()
{
	PersoManager::get()->NSTdeletePerso(Tache::_id);
}
