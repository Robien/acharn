/*
 * ObjetPorte.cpp
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#include "../include/ObjetPorte.h"
#include "../include/ObjetManager.h"

ackCore::ObjetPorte::ObjetPorte(std::string path, std::string diffuse, std::string normale, bool joueurCollision, bool cameraCollision)
{
    if (!joueurCollision && cameraCollision)
    {
        std::cout << "Erreur, un objet ne peux pas entrer en collision avec le joueur mais pas avec la camera" << std::endl;
        exit(0);
    }
    else
    {
        _node = ackCore::ObjetManager::get()->createMeshNode(path);
        _node->setScale(irr::core::vector3df(1, 1, 1));
        irr::video::ITexture* texture = ackCore::ObjetManager::get()->getDevice()->getVideoDriver()->getTexture(diffuse.c_str());
        if (normale != "")
        {

            irr::video::ITexture* normalMap = ackCore::ObjetManager::get()->getDevice()->getVideoDriver()->getTexture(normale.c_str());

            if (normalMap)
            {

                ackCore::ObjetManager::get()->getDevice()->getVideoDriver()->makeNormalMapTexture(normalMap, 2.5f);
                _node->setMaterialTexture(1, normalMap);

                _node->setMaterialType(irr::video::EMT_NORMAL_MAP_SOLID);

            }

        }
        _node->setMaterialType(irr::video::EMT_SOLID);
        _node->setMaterialTexture(0, texture);

        if (joueurCollision && cameraCollision)
        {
            irr::scene::ITriangleSelector* selector = ackCore::ObjetManager::get()->createAnimatedTriangleSelector(_node);
            _node->setTriangleSelector(selector);
        }
        else
        {
            _node->setTriangleSelector(NULL); // j'espère que ça va marcher :D
        }
    }
    ackCore::ObjetManager::get()->addObjet(this);
}

ackCore::ObjetPorte::~ObjetPorte()
{
}

