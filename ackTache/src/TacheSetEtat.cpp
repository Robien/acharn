/*
 * TacheSetEtat.cpp
 *
 *  Created on: 8 nov. 2010
 *      Author: romain
 */

#include "../include/TacheSetEtat.h"
#include "../../ackCore/include/ObjetManager.h"

TacheSetEtat::TacheSetEtat(std::string name, int etat) :
    _name(name), _etat(etat)
{
}

TacheSetEtat::~TacheSetEtat()
{
}

void TacheSetEtat::execute()
{
    ackCore::ObjetManager::get()->setEtat(_name, _etat);
}
