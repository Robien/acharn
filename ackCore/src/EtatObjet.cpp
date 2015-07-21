/*
 * EtatObjet.cpp
 *
 *  Created on: 8 nov. 2010
 *      Author: romain
 */

#include "../include/EtatObjet.h"

EtatObjet::EtatObjet(int frame) :
    frameFixe(frame)
{

}

EtatObjet::~EtatObjet()
{

}

int EtatObjet::getFrame()
{
    return frameFixe;
}

ackCore::Animation* EtatObjet::factory(EtatObjet* etat1, EtatObjet* etat2)
{
    if (etat1->getFrame() > etat2->getFrame())
    {
        return (new ackCore::Animation(etat1->getFrame(), etat2->getFrame(), -50));
    }
    else
    {
        return (new ackCore::Animation(etat1->getFrame(), etat2->getFrame()));
    }
}
