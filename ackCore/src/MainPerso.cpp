/*
 * MainPerso.cpp
 *
 *  Created on: 30 juil. 2010
 *      Author: romain
 */

#include "../include/MainPerso.h"
#include "../include/PersoManager.h"
#include <irrlicht.h>
#include "../../ackAudio/include/Son.h"
#include "../../ackAudio/include/AudioManager.h"
#include "../../ackAudio/include/Buffer.h"
#include "boost/lexical_cast.hpp"
#include "../include/MessageVie.h"
#include "../../ackTache/include/TacheSetAttaque.h"

using irr::scene::ISceneNodeAnimator;

MainPerso::MainPerso(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* camera, Interface & interface, int init) :
    PersoJoueur(device, init), _camera(camera), _interface(interface)
{
    _interface.setExperienceMax(xpprochainlvl());
}

MainPerso::MainPerso(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* camera, Interface & interface, std::string pseudo, EventInfoPerso* eip, int init) :
    PersoJoueur(device, pseudo, init), _camera(camera), _interface(interface), _eip(eip)
{
    _interface.setExperienceMax(xpprochainlvl() - xplvlCourent());
}
MainPerso::~MainPerso()
{
}
void MainPerso::afficher(int x, int y, int z)
{
    _interface.setVieMax(getVieMax());
    _interface.setVie(getVie());
    _interface.setPouvoirMax(getRadiationMax());
    _interface.setPouvoir(getRadiation());
    _interface.setPseudo(getNom());
    _interface.setNiveau(getNiveau());

    Perso::afficher(x, y, z);
    scene::IAnimatedMeshSceneNode* node;
    node = getNode();
    node->addChild(_camera);
}
void MainPerso::majCam()
{
    _camera->setTarget(getNode()->getPosition());
    //    _interface.setVieMax(getVieMax());
    //    _interface.setVie(getVie());
    //    _interface.setRadMax(getRadiationMax());
    //    _interface.setRad(getRadiation());
    //    _interface.setPseudo(getNom());
    //    _interface.setNiveau(getNiveau());
}
void MainPerso::attaque(Perso::typeAttaque type)
{
    switch (type)
    {
    case MAINNUE:
        Perso::setAnim(Perso::FRAPERA2M);
        _tempsAvantFinAnim = 39.0f / 50.0f;
        break;
    case ARME2M:
        Perso::setAnim(Perso::FRAPERA2M);
        _tempsAvantFinAnim = 39.0f / 50.0f;
        break;
    case MAGIE:
        Perso::setAnim(Perso::INCANT);
        _tempsAvantFinAnim = 39.0f / 50.0f;
        break;
    default:
        break;
    }
    //    Son* son = new Son(getNode()->getTransformedBoundingBox().getCenter(), Buffer::EAU, false, NULL);
    //    AudioManager::get()->addSound(son);
    //    son->play();
}
void MainPerso::appliqueVitesse(float delta)
{
    {
        core::line3d<f32> ray;
        ray.start = getNode()->getPosition() + core::vector3df(0, -0.7, 0);
        ray.end = getNode()->getPosition() + core::vector3df(0, -1.75, 0);
        // Tracks the current intersection point with the level or a mesh
        core::vector3df intersection;
        // Used to show with triangle has been hit
        core::triangle3df hitTriangle;
        scene::ISceneCollisionManager* collMan = getDevice()->getSceneManager()->getSceneCollisionManager(); //jean-jacque collMan
        scene::ISceneNode* selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, // This will be the triangle hit in the collision
                0, // This ensures that only nodes that we have
                // set up to be pickable are considered
                0); // Check the entire scene (this is actually the implicit default)


        if (selectedSceneNode != NULL) // on touche le sol
        {
            //            selectedSceneNode->setRotation(selectedSceneNode->getRotation() + irr::core::vector3df(0,0,0.1));
            if (vpy < 0)
            {
                float degat = abs(vpy + vpx + vpz);
                degat -= 170;
                degat *= 0.5;
                if (degat < 0)
                {
                    degat = 0;
                }
                if (degat != 0)
                {
                    PersoManager::get()->addTache(new TacheSetAttaque(0, "<#nom=\"Degat de chute\"#degat="+boost::lexical_cast<std::string> (degat)+">"));
                }
                //TODO: mettre les déats de chutes
                //                _interface.setVie(_interface.getVie() - degat);
                //vpy = -(intersection.getDistanceFrom(getNode()->getAbsolutePosition())-1.7)*100;
                vpy = 0;
                vpx = 0;
                vpz = 0;
                getNode()->setPosition(irr::core::vector3df(getNode()->getPosition().X, intersection.Y + 1.7, getNode()->getPosition().Z));
                if (getAnim() == Perso::JUMP)
                {
                    unLockAnim();
                }
                //                irr::core::vector3df position = getNode()->getPosition();
                //                getNode()->setParent(selectedSceneNode);
                //                selectedSceneNode->addChild(getNode());
                //                getNode()->setPosition(position - selectedSceneNode->getAbsolutePosition());
            }

        }
        else // on est en l'air
        {
            core::line3d<f32> rayTombe;
            rayTombe.start = getNode()->getPosition() + core::vector3df(0, -0.7, 0);
            rayTombe.end = getNode()->getPosition() + core::vector3df(0, -2.5, 0);
            // Tracks the current intersection point with the level or a mesh
            scene::ISceneNode* selectedSceneNodeTombe = collMan->getSceneNodeAndCollisionPointFromRay(rayTombe, intersection, hitTriangle, // This will be the triangle hit in the collision
                    0, // This ensures that only nodes that we have
                    // set up to be pickable are considered
                    0); // Check the entire scene (this is actually the implicit default)

            if (selectedSceneNodeTombe == NULL)
            {
                setAnimHolded(Perso::JUMP);
            }
        }
    }
    {

        core::line3d<f32> ray;
        ray.start = getNode()->getPosition();
        ray.end = getNode()->getPosition() + core::vector3df(0, +0.85, 0);
        // Tracks the current intersection point with the level or a mesh
        core::vector3df intersection;
        // Used to show with triangle has been hit
        core::triangle3df hitTriangle;
        scene::ISceneCollisionManager* collMan = getDevice()->getSceneManager()->getSceneCollisionManager(); //jean-jacque collMan
        scene::ISceneNode* selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, // This will be the triangle hit in the collision
                0, // This ensures that only nodes that we have
                // set up to be pickable are considered
                0); // Check the entire scene (this is actually the implicit default)


        if (selectedSceneNode != NULL)//on touche le plafond
        {
            if (vpy > 0)
            {
                float degat = abs(vpy);
                degat -= 120;
                degat *= 2;
                if (degat < 0)
                {
                    degat = 0;
                }
                //                _interface.setVie(_interface.getVie() - degat);
                vpy = -vpy;
            }
            // std::cout << "ça touche !" << std::endl;
        }

    }

    getNode()->setPosition(irr::core::vector3df(getNode()->getPosition().X + delta * vpx, getNode()->getPosition().Y + delta * vpy, getNode()->getPosition().Z + delta * vpz));
    vpy -= 5000 * delta;

}

void MainPerso::setVitesseY(float vit)
{
    core::line3d<f32> ray;
    ray.start = getNode()->getPosition() + core::vector3df(0, -0.7, 0);
    ray.end = getNode()->getPosition() + core::vector3df(0, -1.8, 0);
    // Tracks the current intersection point with the level or a mesh
    core::vector3df intersection;
    // Used to show with triangle has been hit
    core::triangle3df hitTriangle;
    scene::ISceneCollisionManager* collMan = getDevice()->getSceneManager()->getSceneCollisionManager(); //jean-jacque collMan
    scene::ISceneNode* selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, // This will be the triangle hit in the collision
            0, // This ensures that only nodes that we have
            // set up to be pickable are considered
            0); // Check the entire scene (this is actually the implicit default)


    if (selectedSceneNode != NULL)
    {
        vpy = vit;
    }
}

void MainPerso::saute()
{
    if (estVivant())
    {
        setVitesseY(120);
    }
}

std::vector<int>& MainPerso::alloYAQuelquUn()
{
    return PersoManager::get()->quiEstEnFace(this);
}
void MainPerso::setNodeRez(irr::scene::ISceneNode* nodeRez)
{
    _nodeRez = nodeRez;
}
void MainPerso::tpRez()
{
    irr::core::vector3df pos = _nodeRez->getTransformedBoundingBox().getCenter();
    getNode()->removeAnimators();
    teleport(pos.X, pos.Y, pos.Z);
    scene::ISceneNodeAnimator* anim = getDevice()->getSceneManager()->createCollisionResponseAnimator(_metaSelector, getNode(), core::vector3df(0.20, 0.60, 0.30), core::vector3df(0, -0, 0),
            core::vector3df(0, +0.50, 0));
    getNode()->addAnimator(anim);
    anim->drop(); // And likewise, drop the animator when we're done referring to it.

}

void MainPerso::setMetaSelector(scene::IMetaTriangleSelector * metaSelector)
{
    _metaSelector = metaSelector;
}

bool MainPerso::gainxp(float xp)
{
    new MessageVie(getNode()->getPosition(), getDevice(), xp, MessageVie::GAINXP);
    bool lvlup = PersoJoueur::gainxp(xp);
    _eip->majXp(getXp() - xplvlCourent(), xpprochainlvl() - xplvlCourent());
    return (lvlup);
}

void MainPerso::setVie(float vie)
{
    if (vie < getVie())
    {
        new MessageVie(getNode()->getPosition(), getDevice(), getVie() - vie, MessageVie::PERTEVIE);
    }
    else if (vie > getVie())
    {
        new MessageVie(getNode()->getPosition(), getDevice(), vie - getVie(), MessageVie::GAINVIE);
    }
    _eip->majVie(vie);
    AbstractPerso::setVie(vie);
}

void MainPerso::addNiveau()
{
    new MessageVie(getNode()->getPosition(), getDevice(), "LVL UP !", irr::video::SColor(0, 216, 198, 21));
    AbstractPerso::addNiveau();
    _eip->majNiveau(getNiveau(), xpprochainlvl() - xplvlCourent());
    _interface.gagnerNiveau(10);
}

void MainPerso::setRadiation(float rad)
{
    _eip->majRadiation(rad);
    AbstractPerso::setRadiation(rad);
}

void MainPerso::setRadiationMax(float radm)
{
    _eip->majRadiationMax(radm);
    AbstractPerso::setRadiationMax(radm);
}

void MainPerso::setVieMax(float viem)
{
    _eip->majVieMax(viem);
    AbstractPerso::setVieMax(viem);
}

scene::ICameraSceneNode* MainPerso::getCamera()
{
    return _camera;
}
Interface& MainPerso::getInterface()
{
    return _interface;
}
IrrlichtDevice* MainPerso::getDevice()
{
    return Perso::getDevice();
}
const bool MainPerso::isReady()
{
    return (PersoJoueur::getInit() != 0);
}
