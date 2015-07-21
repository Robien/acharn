/*
 * Jeu.h
 *
 *  Created on: 19 juil. 2010
 *      Author: romain
 */

#ifndef JEU_H_
#define JEU_H_

#include <irrlicht.h>
#include "Client.h"
#include "Interface.h"
#include "EventReceiver.h"
#include "../include/MainPerso.h"
#include "../include/EventReseau.h"
#include "Protocole.h"
#include "Appli.h"
#include "../include/Referenced.h"
#include "../include/PointeurIntelligent.h"
#include "../include/ShaderCallBack.h"

/**
 * @namespace ackCore
 * @brief ackCore est le namespace contenant la gestion de la 3D et de la gestion des fonctions des autres parties du jeu
 */

namespace ackCore
{

class Jeu: public Referenced
{
public:
    Jeu(Appli & app, Protocole* protocole, bool modeConnecte = true, std::string pseudo = "dadu", std::string mdp = "dadu");
    virtual ~Jeu();
    void run();

public:
    void justOneFrameChargement();

private:

    void makeChargement();
    void finishChargement();

    bool _modeConnecte;

    Appli & _app;
    IrrlichtDevice* _device; //gestion de la mémoire par Irrlicht
    scene::ISceneManager* _smgr;
    scene::IAnimatedMeshSceneNode* node_sauv;
    scene::IAnimatedMeshSceneNode* node_pnj;
    scene::ICameraSceneNode* _camera;
    scene::ICameraSceneNode* _cameraChargement;

    PointeurIntelligent<Interface> _interp;
    PointeurIntelligent<EventReceiver> _receiver;
    PointeurIntelligent<MainPerso> _joueur;

    scene::ITriangleSelector* selector;
    PointeurIntelligent<Protocole> _protocole;

    std::string _pseudo;
    std::string _mdp;

    PointeurIntelligent<ShaderCallBack> _shaderCallBack;

    irr::scene::ISceneNode* _nodeRez;

};
} // namespace ackCore

#endif /* JEU_H_ */
