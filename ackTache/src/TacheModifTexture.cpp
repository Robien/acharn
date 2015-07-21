/*
 * TacheModifTexture.cpp
 *
 *  Created on: 9 nov. 2010
 *      Author: romain
 */

#include "../include/TacheModifTexture.h"
#include "../../ackCore/include/PersoManager.h"

TacheModifTexture::TacheModifTexture(int id, std::vector<std::string>* textures) : Tache(id), _textures(textures)
{
}

TacheModifTexture::~TacheModifTexture()
{
}

void TacheModifTexture::execute()
{
    std::cout << "changement de textures pour le perso d'id : "<< _id << std::endl;
    PersoManager::get()->getPersoById(_id)->setTexture();
    PersoManager::get()->getPersoById(_id)->setTexture(_textures);
   // PersoManager::get()->getPersoById(_id)->setTexture((*_textures)[0]);
    PersoManager::get()->getPersoById(_id)->changeTexture();
}
