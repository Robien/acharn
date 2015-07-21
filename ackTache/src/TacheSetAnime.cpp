/*
 * TacheSetAnime.cpp
 *
 *  Created on: 5 août 2010
 *      Author: romain
 */

#include "../include/TacheSetAnime.h"
#include "../include/PersoManager.h"

TacheSetAnime::TacheSetAnime(int id, Perso::typeAnim typeAnim, bool lock) :
    Tache(id), _typeAnim(typeAnim), _lock(lock)
{
}

TacheSetAnime::~TacheSetAnime()
{
}

void TacheSetAnime::execute()
{
    if (_lock)
    {
        if (Tache::_id == 0)
        {
            PersoManager::get()->getMainPerso()->setAnimHolded(_typeAnim);
        }
        else
        {
            PersoManager::get()->getPersoById(Tache::_id)->setAnimHolded(_typeAnim);
        }
    }
    else
    {
        if (Tache::_id == 0)
        {
            PersoManager::get()->getMainPerso()->setAnim(_typeAnim);
        }
        else
        {
            PersoManager::get()->getPersoById(Tache::_id)->setAnim(_typeAnim);
        }
    }

}
