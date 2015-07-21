/*
 * TacheStopAnim.h
 *
 *  Created on: 8 sept. 2010
 *      Author: romain
 */

#ifndef TACHEDECLANCHEURSETANIM_H_
#define TACHEDECLANCHEURSETANIM_H_

#include "Tache.h"
#include "Perso.h"

class TacheStopAnim : public Tache
{
public:
    TacheStopAnim(int id);
    virtual ~TacheStopAnim();
    void execute();
private:

};

#endif /* TACHEDECLANCHEURSETANIM_H_ */
