/*
 * EventIncantation.cpp
 *
 *  Created on: 6 oct. 2010
 *      Author: céphise
 */

#include "../include/EventIncantation.h"
#include "../include/Perso.h"
#include "../include/PersoManager.h"

EventIncantation::EventIncantation(int id)
{
    _id = id;
}

EventIncantation::~EventIncantation()
{
}

void EventIncantation::incantation(float temps, int type, float portee)
{
//    PersoManager::get()->getPersoById(_id)->setDead();
}
