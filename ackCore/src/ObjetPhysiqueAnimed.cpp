/*
 * ObjetPhysiqueAnimed.cpp
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#include "../include/ObjetPhysiqueAnimed.h"
#include <iostream>
#include "../include/EtatObjet.h"
#include "../include/ObjetManager.h"

ackCore::ObjetPhysiqueAnimed::ObjetPhysiqueAnimed() :
    _animCourrente(0), _tempsAvantFinAnim(0), _isAnimSet(false), _withEtat(false)
{
    _etatCourent.reset(NULL);
    _listeEtat = new std::map<int, PointeurIntelligent<EtatObjet> >;
}

ackCore::ObjetPhysiqueAnimed::~ObjetPhysiqueAnimed()
{
}

void ackCore::ObjetPhysiqueAnimed::setSuiteAnimation(SuiteAnimations* suiteAnim)
{
    if (suiteAnim != NULL && suiteAnim->size() > 0)
    {
        _anim = suiteAnim;
        _animCourrente = 0;
        _tempsAvantFinAnim = calculTempsAvantFin();
        ((irr::scene::IAnimatedMeshSceneNode*) _node)->setFrameLoop((*_anim)[_animCourrente]->getDebut(), (*_anim)[_animCourrente]->getFin());
        ((irr::scene::IAnimatedMeshSceneNode*) _node)->setAnimationSpeed((*_anim)[_animCourrente]->getFps());
        _isAnimSet = true;
    }
}

float ackCore::ObjetPhysiqueAnimed::calculTempsAvantFin()
{
    return valeurAbsolue(((*_anim)[_animCourrente]->getFin() - (*_anim)[_animCourrente]->getDebut()) / (*_anim)[_animCourrente]->getFps());
}
void ackCore::ObjetPhysiqueAnimed::maj(float delta)
{
    if (_isAnimSet)
    {
        _tempsAvantFinAnim -= delta;
        if (_tempsAvantFinAnim <= 0)
        {
            ++_animCourrente;
            if (_animCourrente > _anim->size() - 1)
            {
                if (_anim->getLoop())
                {
                    _animCourrente = 0;
                }
                else
                {
                    _isAnimSet = false;
                }
            }
            if (_isAnimSet)
            {
                _tempsAvantFinAnim += calculTempsAvantFin();
                if ((*_anim)[_animCourrente]->getFps() > 0)
                {
                    ((irr::scene::IAnimatedMeshSceneNode*) _node)->setFrameLoop((*_anim)[_animCourrente]->getDebut(), (*_anim)[_animCourrente]->getFin());
                }
                else
                {
                    ((irr::scene::IAnimatedMeshSceneNode*) _node)->setFrameLoop((*_anim)[_animCourrente]->getFin(), (*_anim)[_animCourrente]->getDebut());
                }
                ((irr::scene::IAnimatedMeshSceneNode*) _node)->setAnimationSpeed((*_anim)[_animCourrente]->getFps());
            }
        }
    }
}
float ackCore::ObjetPhysiqueAnimed::valeurAbsolue(float x)
{
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}

void ackCore::ObjetPhysiqueAnimed::setListeEtat(std::map<int, PointeurIntelligent<EtatObjet> >* listeEtat)
{
    _listeEtat = listeEtat;
    _etatCourent = (*listeEtat)[0];
    _withEtat = true;
    SuiteAnimations* anims = new SuiteAnimations(false);
    anims->push_back(new ackCore::Animation(_etatCourent->getFrame(), _etatCourent->getFrame()));
    setSuiteAnimation(anims);
}
void ackCore::ObjetPhysiqueAnimed::setEtat(int i, std::string name)
{
    if (_withEtat)
    {
        if (_etatCourent.get() == NULL)
        {
            _etatCourent = (*_listeEtat)[i];
        }
        if (_etatCourent != (*_listeEtat)[i])
        {

            SuiteAnimations* anims = new SuiteAnimations(false);
            anims->push_back(EtatObjet::factory(_etatCourent, (*_listeEtat)[i]));
            _etatCourent = (*_listeEtat)[i];
            anims->push_back(new ackCore::Animation(_etatCourent->getFrame(), _etatCourent->getFrame()));
            setSuiteAnimation(anims);
            ObjetManager::get()->sendEtat(name, i);
        }
    }
    else
    {
        std::cout << "_withetat = false" << std::endl;
    }
}

void ackCore::ObjetPhysiqueAnimed::addEtat(int num, EtatObjet* etat)
{
    _withEtat = true;
    (*_listeEtat)[num] = etat;
    std::cout << "num = " << num;
}

