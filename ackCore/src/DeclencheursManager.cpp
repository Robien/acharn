/*
 * DeclancheursManager.cpp
 *
 *  Created on: 7 sept. 2010
 *      Author: romain
 */

#include "../include/DeclencheursManager.h"
#include <iostream>

DeclencheursManager::DeclencheursManager() :
    boutonActionAppuye(false)
{
    init = false; // pour savoir si il a été initialisé
    _mutexTache.reset(new boost::mutex);
}
void DeclencheursManager::setJoueur(MainPerso* joueur)
{
    _joueur = joueur;
    init = true;
}
void DeclencheursManager::startDeclencheurs()
{
    threadDeclencheur = new boost::thread(&DeclencheursManager::lanceThread);
}
void DeclencheursManager::stopDeclencheurs()
{
    init = false;
    delete threadDeclencheur;
}
void* DeclencheursManager::lanceThread()
{
    for (;;)
    {
        DeclencheursManager::get()->testDeclencheur();
        usleep(20000);
    }
    return NULL;
}
DeclencheursManager::~DeclencheursManager()
{
}

void DeclencheursManager::addDeclancheur(Declencheurs* declancheur)
{
    if (init)
    {
        declancheur->setJoueur(_joueur);
        _declancheurs.push_back(declancheur);
    }
    else
    {
        std::cout << "(EE) Declencheur non pris en compte !" << std::endl;
    }
}
void DeclencheursManager::testDeclencheur()
{
    if (init)
    {
        for (unsigned int i = 0; i < _declancheurs.size(); ++i)
        {
            bool nothing = false;
            bool declenc = _declancheurs[i]->test(nothing);
            if (nothing)
            {
                //nothing else matters
            }
            else if (declenc)
            {
                std::cout << "declencheur executé" << std::endl;
                //ajouter l'execution!
                addTache(_declancheurs[i]->getTache());
                if (_declancheurs[i]->isActionneurEtat())
                {
                    addTache(_declancheurs[i]->getTacheEtat());
                }

            }
            else
            {
                std::cout << "declencheur fin" << std::endl;
                //ajouter l'execution
                TacheStopAnim* tache(new TacheStopAnim(0));
                addTache(tache);
                //_declancheurs[i]->stop(); // TODO: a lancer seulement quand on quitte le déclancheur
            }
        }
    }
}

bool DeclencheursManager::majJoueur()
{
    {
        if (_mutexTache->try_lock())
        {
            for (unsigned int i = 0; i < _aFaire.size(); ++i)
            {
                _aFaire[i]->execute();
            }
            _aFaire.clear();
            _mutexTache->unlock();
            return true;
        }
        else
        {
            return false;
        }

    }
}

void DeclencheursManager::addTache(Tache* tache)
{
    {
        boost::mutex::scoped_lock lock(*_mutexTache.get());
        _aFaire.push_back(tache);
    }

}

void DeclencheursManager::setBoutonActionOn()
{
    boutonActionAppuye = true;
}

void DeclencheursManager::setBoutonActionOff()
{
    boutonActionAppuye = false;
}

bool DeclencheursManager::getBoutonAction()
{
  return boutonActionAppuye;
}



