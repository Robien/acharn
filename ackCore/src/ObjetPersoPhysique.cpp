/*
 * ObjetPersoPhysique.cpp
 *
 *  Created on: 23 sept. 2010
 *      Author: romain
 */

#include "../include/ObjetPersoPhysique.h"

ackCore::ObjetPersoPhysique::ObjetPersoPhysique(irr::IrrlichtDevice* device) :
    irr::scene::ISceneNode(*device->getSceneManager()->addEmptySceneNode()), _device(device)
{

}

ackCore::ObjetPersoPhysique::~ObjetPersoPhysique()
{
}
