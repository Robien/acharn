
/*
 * CallbackInfoPerso.h
 *
 *  Created on: 17 sept. 2010
 *      Author: cephise
 */

#ifndef CALLBACKINFOPERSO_H_
#define CALLBACKINFOPERSO_H_

#include "../include/Referenced.h"

using namespace std;
class CallbackInfoPerso: public Referenced
{
public:
	CallbackInfoPerso(){}
	virtual void isDead(){}
	virtual void majRadiation(float rad){}
	virtual void majVie(float vie){}
	virtual void majRadiationMax(float radm){}
	virtual void majVieMax(float viem){}
	virtual void majNiveau(int lvl){}
	virtual void majXp(float xp){}
	virtual void incantation(float temps, int type){}
};

#endif /* CALLBACKINFOPERSO_H_ */
