/*
 * EventInfoPerso.h
 *
 *  Created on: 18 sept. 2010
 *      Author: romain
 */

#ifndef EVENTINFOPERSO_H_
#define EVENTINFOPERSO_H_

#include "CallbackInfoPerso.h"
#include "Interface.h"
#include "../include/PointeurIntelligent.h"

class EventInfoPerso: public CallbackInfoPerso
{
public:
    EventInfoPerso(Interface* inter);
    virtual ~EventInfoPerso();

    void isDead();
    void majRadiation(float rad);
    void majVie(float vie);
    void majRadiationMax(float radm);
    void majVieMax(float viem);
    void majNiveau(int lvl, float xpmax);
    void majXp(float xp, float xpmax);

private:
    PointeurIntelligent<Interface> _inter;
};

#endif /* EVENTINFOPERSO_H_ */
