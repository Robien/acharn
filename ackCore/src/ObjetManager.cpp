/*
 * ObjetManager.cpp
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#include "../include/ObjetManager.h"
#include "const.h"

ackCore::ObjetManager::ObjetManager()
{
    _device = NULL;
}

ackCore::ObjetManager::~ObjetManager()
{
}

void ackCore::ObjetManager::setDevice(irr::IrrlichtDevice* device)
{
    _device = device;
}

irr::IrrlichtDevice* ackCore::ObjetManager::getDevice()
{
    return _device;
}

irr::scene::IAnimatedMeshSceneNode* ackCore::ObjetManager::createMeshNode(std::string path)
{
    return _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh(irr::io::path(path.c_str())), 0, ID_IsNotPickable);
}

irr::scene::ITriangleSelector* ackCore::ObjetManager::createAnimatedTriangleSelector(irr::scene::IAnimatedMeshSceneNode* node)
{
    return _device->getSceneManager()->createTriangleSelector(node);
}

void ackCore::ObjetManager::addObjet(ObjetPhysique* objet)
{
    _listeObjets.push_back(objet);
}

void ackCore::ObjetManager::addObjet(ObjetPhysiqueAnimed* objet, std::string name)
{
    _dicoObjet[name] = objet;
}

void ackCore::ObjetManager::addToMeta(irr::scene::IMetaTriangleSelector * meta)
{
    for (unsigned int i = 0; i < _listeObjets.size(); ++i)
    {
        ObjetPhysique* objet = _listeObjets[i];
        if (!objet->isOnMeta() && objet->getSelector() != NULL)
        {
            meta->addTriangleSelector(objet->getSelector());
            objet->setIsOnMeta(true);
        }
    }
}

void ackCore::ObjetManager::majAll(float delta)
{
    for (unsigned int i = 0; i < _listeObjets.size(); ++i)
    {
        _listeObjets[i]->maj(delta);
    }
}

void ackCore::ObjetManager::setEtat(std::string name, int etat)
{
    _dicoObjet[name]->setEtat(etat, name);
}

void ackCore::ObjetManager::setProtocol(Protocole* protocole)
{
    _protocole = protocole;
}

void ackCore::ObjetManager::sendEtat(std::string name, int etat)
{
    _protocole->setEtat(name, etat);
}
