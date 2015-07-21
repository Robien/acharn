/*
 * Objet.cpp
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#include "../include/ObjetPhysique.h"

ackCore::ObjetPhysique::ObjetPhysique() : _isOnMeta(false)
{
}

ackCore::ObjetPhysique::~ObjetPhysique()
{
}

irr::scene::ITriangleSelector* ackCore::ObjetPhysique::getSelector()
{
    return _node->getTriangleSelector();
}

void ackCore::ObjetPhysique::setIsOnMeta(bool isOnMeta)
{
    _isOnMeta = isOnMeta;
}

bool ackCore::ObjetPhysique::isOnMeta()
{
    return _isOnMeta;
}

