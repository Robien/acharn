/*
 * EventInfoPerso.cpp
 *
 *  Created on: 18 sept. 2010
 *      Author: romain
 */

#include "../include/EventInfoPerso.h"

EventInfoPerso::EventInfoPerso(Interface* inter)
{
	_inter = inter;
}

EventInfoPerso::~EventInfoPerso()
{
}

void EventInfoPerso::isDead()
{
}

void EventInfoPerso::majRadiation(float rad)
{
	_inter->setPouvoir(rad);
}

void EventInfoPerso::majVie(float vie)
{
	_inter->setVie(vie);
}

void EventInfoPerso::majRadiationMax(float radm)
{
	_inter->setPouvoirMax(radm);
}

void EventInfoPerso::majVieMax(float viem)
{
	_inter->setVieMax(viem);
}

void EventInfoPerso::majNiveau(int lvl, float xpmax)
{
	_inter->setNiveau(lvl);
	_inter->setExperienceMax(xpmax);
}

void EventInfoPerso::majXp(float xp, float xpmax)
{
    _inter->setExperience(xp);
    _inter->setExperienceMax(xpmax);
}
