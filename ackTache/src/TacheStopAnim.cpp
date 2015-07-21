/*
 * TacheStopAnim.cpp
 *
 *  Created on: 8 sept. 2010
 *      Author: romain
 */

#include "../include/TacheStopAnim.h"
#include "../include/PersoManager.h"

TacheStopAnim::TacheStopAnim(int id) :
    Tache(id)
{

}

TacheStopAnim::~TacheStopAnim()
{
}

void TacheStopAnim::execute()
{
    if (Tache::_id == 0)
    {
        PersoManager::get()->getMainPerso()->unLockAnim();
    }
    else
    {
        PersoManager::get()->getPersoById(Tache::_id)->unLockAnim();
    }
}
