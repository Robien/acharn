/*
 * PersoManager.cpp
 *
 *  Created on: 19 juil. 2010
 *      Author: romain
 */

#include "../include/PersoManager.h"
#include "../include/TacheDeplacement.h"
#include "../include/TacheCreationPerso.h"
#include "../include/TacheDestructionPerso.h"
#include "../include/TacheSetAnime.h"

#include <boost/thread/thread.hpp>
#include "boost/lexical_cast.hpp"
#include "../../ackTache/include/TacheModifTexture.h"

PersoJoueur* PersoManager::newPerso(std::string infoPerso)// Pas thread safe !
{
    if (!_isDeviceDefine)
    {
        std::cout << "Demande interdite de création de Perso avant la création de la fenetre" << std::endl;
    }

    return new PersoJoueur(infoPerso, _device);

}

PersoNonJoueur* PersoManager::newPersoNJ(std::string infoPerso, int typePerso)// Pas thread safe !
{
    if (!_isDeviceDefine)
    {
        std::cout << "Demande interdite de création de Perso avant la création de la fenetre" << std::endl;
    }

    if (typePerso == 1)
    {
        return new PersoQuete(infoPerso, _device);
    }
    else
    {
        return new PersoVendeur(infoPerso, _device);
    }

}

void PersoManager::createPerso(int id, float x, float y, float z, int init, std::string infoPerso)
{
    TacheCreationPerso* tache = new TacheCreationPerso(id, x, y, z, init, infoPerso);
    addTache(tache);
}
void PersoManager::createPerso(int id, core::vector3df position, int init, std::string infoPerso)
{
    createPerso(id, position.X, position.Y, position.Z, init, infoPerso);
}

void PersoManager::teleportPerso(int id, float x, float y, float z, float rx, float ry, float rz)
{
    TacheDeplacement* tache(new TacheDeplacement(id, x, y, z, rx, ry, rz));
    addTache(tache);
}
void PersoManager::teleportPerso(int id, irr::core::vector3df position, irr::core::vector3df rotation)
{
    TacheDeplacement* tache(new TacheDeplacement(id, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z));
    addTache(tache);
}
PersoJoueur* PersoManager::getPersoById(int id)// Pas thread safe !
{
    if (id == 0)
    {
        return _joueur;
    }
    else
    {
        return _lesAutres[id];
    }
}
void PersoManager::addPersoByID(int id, PersoJoueur* perso)
{
    if (_lesAutres.count(id) != 0)
    {
        std::cout << "(--) suppression de perso*" << std::endl;
    }
    _lesAutres[id] = perso;
}
void PersoManager::maj()
{
    {
        boost::mutex::scoped_lock lock(*_mutexTache.get());
        for (unsigned int i = 0; i < _aFaire.size(); ++i)
        {
            _aFaire[i]->execute();
        }
        _aFaire.clear();
    }
}
void PersoManager::addTache(Tache* tache)
{
    {
        boost::mutex::scoped_lock lock(*_mutexTache.get());
        _aFaire.push_back(tache);
    }

}
bool PersoManager::tryMaj()
{
    {
        if (_mutexTache->try_lock())
        {
            //            boost::mutex::scoped_lock lock(*_mutexTache.get());
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
void PersoManager::NSTdeletePerso(int id)
{
    //lesAutres[id]->getNode()->removeAll();
    _lesAutres[id]->getNode()->remove();
    _lesAutres[id] = NULL;
    //lesAutres.erase(id);
}
void PersoManager::deletePerso(int id)
{
    TacheDestructionPerso* tache(new TacheDestructionPerso(id));
    addTache(tache);
}
void PersoManager::setAnim(int id, Perso::typeAnim typeAnim)
{
    TacheSetAnime* tache(new TacheSetAnime(id, typeAnim, false));
    addTache(tache);
}
std::vector<int>& PersoManager::quiEstEnFace(Perso* perso)
{
    enFace.clear();
    irr::core::vector3df positionReference = perso->getNode()->getPosition();
    map<int, PointeurIntelligent<PersoJoueur> >::iterator it;
    for (it = _lesAutres.begin(); it != _lesAutres.end(); ++it)
    {
        if (it->second.get() != NULL)
        {
            if (isEnFace(_joueur->getNode(), it->second->getNode()->getPosition()))
            {
                if (it->second->getNode()->getPosition().getDistanceFrom(positionReference) < 2)
                {
                    enFace.push_back(it->first);
                }
            }
        }
    }
    return enFace;//NULL;//_lesAutres; // les autres, c'est NULL

}
bool PersoManager::isEnFace(irr::scene::ISceneNode* node, irr::core::vector3df position)
{

    float a = position.X - node->getPosition().X;
    float b = position.Z - node->getPosition().Z;

    //a = abs(a);
    // b = abs(b);

    float beta = atan(b / a) * 180 / M_PI;
    std::cout << beta << std::endl;

    //  beta = abs(beta);

    float rot = node->getRotation().Y;
    float alpha = 90 - rot - beta;

    // alpha = abs(alpha);


    while (alpha > 220)
    {
        alpha -= 360;
    }
    std::cout << alpha << std::endl;
    if ((alpha > 140 && alpha < 220 && a > 0) || (alpha < 40 && alpha > -240 && a < 0))
    {
        std::cout << "boooooom" << std::endl;
        return true;
    }
    else
    {
        return false;
    }

    // cos 0 sin Xcos+Zsin-X
    // 0   1 0   0
    //-sin 0 cos -Xsin+Zcos-Z
    // 0   0  0   1
    //

    //X, Y, Z
    /*
     float x = position.X;
     float y = position.Y;
     float z = position.Z;

     float rx = node->getPosition().X;
     float ry = node->getPosition().Y;
     float rz = node->getPosition().Z;
     float theta = - node->getRotation().Y*M_PI/180;
     irr::core::vector3df newPos = irr::core::vector3df(x* cos(theta) - z* sin(theta), y, x * (rx*cos(theta)+rz*sin(theta)-rx) + z * (-rx * sin(theta) + rz * cos(theta) - rz));
     std::cout << newPos.Z  << " - " << newPos.X << std::endl;

     if (newPos.Z > newPos.X*2)
     {
     std::cout << "ok" << std::endl;
     }
     core::line3d<f32> rayReference;
     rayReference.start = node->getPosition();
     //    rayReference.end = node->getPosition() + irr::core::vector3df(1, 0, 0);
     rayReference.end.X = sin((node->getRotation().Y) * M_PI / 180);
     rayReference.end.Z = cos((node->getRotation().Y) * M_PI / 180);
     rayReference.end.X /= rayReference.getLength();
     rayReference.end.Z /= rayReference.getLength();
     rayReference.end.Y = position.Y;
     rayReference.start.Y = position.Y;
     rayReference.end.X *= 6;
     rayReference.end.Z *= 6;
     f64 dist;
     if (rayReference.getIntersectionWithSphere(position, 0.5, dist))
     {
     return true;
     }
     else
     {
     return false;
     }
     */
    return true; // ouais je suis pas sur que cette methode sois fonctionelle à 100%
}
void PersoManager::setMainPerso(MainPerso* perso)
{
    _joueur = perso; // le mieux ça serais de le creer ici .... enfin moi je dit ça, je dit rien
}
MainPerso* PersoManager::getMainPerso()
{
    return _joueur;
}

void PersoManager::majAttaqueAllPerso()
{
    map<int, PointeurIntelligent<PersoJoueur> >::iterator it;
    for (it = _lesAutres.begin(); it != _lesAutres.end(); ++it)
    {
        if (it->second.get() != NULL)
        {
            it->second->effectuerAtk(_joueur->getDevice()->getTimer()->getTime() / 1000);
        }
    }
    _joueur->effectuerAtk(_joueur->getDevice()->getTimer()->getTime() / 1000);
    if (!_joueur->estVivant())
    {
        _joueur->setDead();
    }

}

void PersoManager::setDevice(irr::IrrlichtDevice* device)
{
    _isDeviceDefine = true;
    _device = device;
}

void PersoManager::connexionTexture(int id, std::vector<std::string>* l_texture)
{
    addTache(new TacheModifTexture(id, l_texture));
}
