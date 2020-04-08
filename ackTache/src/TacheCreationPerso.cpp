/*
 * TacheCreationPerso.cpp
 *
 *  Created on: 21 juil. 2010
 *      Author: romain
 */

#include "../include/TacheCreationPerso.h"
#include "../include/Perso.h"
#include "../include/PersoManager.h"
#include "../../ackCore/include/EventIncantation.h"

TacheCreationPerso::TacheCreationPerso(int id, float newx, float newy, float newz, int init, std::string infoJoueur) :
	Tache(id), _x(newx), _y(newy), _z(newz), _init(init), _infoJoueur(infoJoueur)
{

}
void TacheCreationPerso::execute()
{
	PersoJoueur* perso(PersoManager::get()->newPerso(_infoJoueur));
	perso->afficher(_x, _y, _z, perso->getNom());
	perso->setInfo(_infoJoueur, _init);
	string nom = perso->getNom();
	PersoManager::get()->addPersoByID(_id, perso);
    perso->setCallbackIncantation(new EventIncantation(_id));
}

TacheCreationPerso::~TacheCreationPerso()
{

}
