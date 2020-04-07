/*
 * Jeu.cpp
 *
 *  Created on: 19 juil. 2010
 *      Author: romain
 */

#include "Jeu.h"
#include "../include/PersoManager.h"
#include "PersoJoueur.h"
#include "../include/Login.h"
#include "../include/PointeurIntelligent.h"
#include "../include/IrrAtributeExtractor.h"
#include "../include/DeclencheursManager.h"
#include "../include/ObjetManager.h"
#include "../include/ObjetPorte.h"
#include "../include/SuiteAnimations.h"
#include "../include/Animation.h"
#include <AL/al.h>
#include "../../ackAudio/include/Audio.h"
#include "../../ackAudio/include/AudioManager.h"
#include "../../ackUtils/include/SequenceAleatoire.h"
#include "../include/EventIncantation.h"
#include "boost/lexical_cast.hpp"
#include "../include/MessageManager.h"

//réseau -> frequence d'envois des coordonnée
#define FREQ_ENVOI 10 		// nombres de frames/deplacement a attendre avant d'envoyer
#define FACTEUR_ENVOI 10 	// ratio d'effet des courbes sur l'envoi
//interface
#define FENEL 800
#define FENEH 600
#define FULL_SCREEN false

using namespace irr;
using namespace std;
using namespace gui;

ackCore::Jeu::Jeu(Appli & app, Protocole* protocole, bool modeConnecte, std::string pseudo, std::string mdp) :
    _modeConnecte(modeConnecte), _app(app), _protocole(protocole), _pseudo(pseudo), _mdp(mdp)
{
    ObjetManager::get()->setProtocol(_protocole);
    selector = 0;
    _nodeRez = NULL;
}

ackCore::Jeu::~Jeu()
{
}

void ackCore::Jeu::run()
{

    video::E_DRIVER_TYPE driverType;

    int i = 3; // opengl

    switch (i)
    {
    case 1:
        driverType = video::EDT_DIRECT3D9;
        break;
    case 2:
        driverType = video::EDT_DIRECT3D8;
        break;
    case 3:
        driverType = video::EDT_OPENGL;
        break;
    case 4:
        driverType = video::EDT_SOFTWARE;
        break;
    case 5:
        driverType = video::EDT_BURNINGSVIDEO;
        break;
    case 6:
        driverType = video::EDT_NULL;
        break;
    default:
        exit(0);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    ////// étape 1 : création du device :

    _device = createDevice(driverType, core::dimension2d<u32>(FENEL, FENEH), 16, FULL_SCREEN, true, true);

    if (_device == 0)
    {
        std::cout << "Problème de type de driver" << std::endl;
        exit(0);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    ////// étape 1.5 gestion du loggin :

    // PointeurIntelligent<Login> log = new Login(_device);
    //log->chargement();

    _smgr = _device->getSceneManager();
    video::IVideoDriver* driver = _device->getVideoDriver();
    PersoManager::get()->setDevice(_device);
    ObjetManager::get()->setDevice(_device);

    //////////////////////////////////////////////////////////////////////////////////////////////
    ////// étape 2 : création de l'interface :

    _interp = new Interface(_smgr, driver, FENEL, FENEH);
    PointeurIntelligent<EventInfoPerso> eip = new EventInfoPerso(_interp);

    //////////////////////////////////////////////////////////////////////////////////////////////
    ////// étape 3 : création de la camera :
    _camera = _smgr->addCameraSceneNode(0, core::vector3df(0, 30, -40), core::vector3df(0, 5, 0));

    //////////////////////////////////////////////////////////////////////////////////////////////
    ////// étape 4 : création du joueur principal :

    _joueur = new MainPerso(_device, _camera, *_interp, _pseudo, eip);
    _joueur->setCallbackIncantation(new EventIncantation(0));
    (dynamic_cast<EventReseau*> (_protocole->getCallback()))->setJoueur(_joueur);
    DeclencheursManager::get()->setJoueur(_joueur);
    PersoManager::get()->setMainPerso(_joueur);

    //////////////////////////////////////////////////////////////////////////////////////////////
    ////// étape 5 : création de l'event Receiver :

    _receiver = new EventReceiver(*_joueur, _app, _protocole);
    _device->setEventReceiver(_receiver);

    ////// Fin des initialisations ///////////////////////////////////////////////////////////////
    makeChargement();
    justOneFrameChargement();
    std::cout << "Si le jeu reste bloqué après cette ligne, c'est qu'il y a un problème de connexion." << std::endl
            << "Il peut s'agir soit d'un pare feu, sois que le serveur est down (regardez si tout est normal à l'adresse http://acharn.no-ip.org)" << std::endl;
    _protocole->connexion(_pseudo, _mdp);
    _protocole->calculReception(0);
    while (!_joueur->isReady() && _modeConnecte)
    {
        justOneFrameChargement();
    }

    //if (not c1->getconnect()) { std::cout << "problème de connexion !" << std::endl; exit(0);}


    _interp->setLogVisible(false);
    _interp->setMenuJeuVisible(false);

    //	device->getFileSystem()->addZipFileArchive("../media/map-20kdm2.pk3");

    //scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("mesh/arene.b3d");
    scene::ISceneNode* q3node = 0;
    //		q3node = smgr->addMeshSceneNode(smgr->getMesh("mesh/arene.b3d"));
    //		0, IDFlag_IsPickable | IDFlag_IsHighlightable);

    // irr::scene::ISceneUserDataSerializer;

    PointeurIntelligent<ackCore::IrrAtributeExtractor> eventIrr = new ackCore::IrrAtributeExtractor(this);
    justOneFrameChargement();
    _smgr->loadScene("data/mesh/arene/Scene.irr", eventIrr);
    justOneFrameChargement();
    scene::IMetaTriangleSelector * meta = _smgr->createMetaTriangleSelector();

    //Romain a dit que la lumiere soit et la lumiere fut
    _device->getSceneManager()->addLightSceneNode();

    core::array<scene::ISceneNode *> nodes;
    _smgr->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes
    scene::ITriangleSelector* selector_sauv = 0;
    std::vector<irr::scene::ISceneNode*> spawnPoint;

    for (u32 i = 0; i < nodes.size(); ++i)
    {
        justOneFrameChargement();
        scene::ISceneNode * node = nodes[i];
        //  node->setID(IDFlag_IsPickable);
        scene::ITriangleSelector * selector = 0;
        q3node = node;
        //q3node->setScale(core::vector3df(1000,1000,1000));
        switch (node->getType())
        {
        case scene::ESNT_CUBE:
            std::cout << "methode 1" << std::endl;
            break;
        case scene::ESNT_ANIMATED_MESH:
            std::cout << "methode 2" << std::endl;
            // Because the selector won't animate with the mesh,
            // and is only being used for camera collision, we'll just use an approximate
            // bounding box instead of ((scene::IAnimatedMeshSceneNode*)node)->getMesh(0)
            selector = _smgr->createTriangleSelectorFromBoundingBox(node);
            break;

        case scene::ESNT_MESH:
            selector = _smgr->createOctreeTriangleSelector(((scene::IMeshSceneNode*) node)->getMesh(), node);
            std::cout << "methode 6" << std::endl;

            //        std::cout << "methode 3" << std::endl;break;
        case scene::ESNT_SPHERE: // Derived from IMeshSceneNode
            //	selector = smgr->createTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);std::cout << "methode 4" << std::endl;
            selector = _smgr->createOctreeTriangleSelector(((scene::IMeshSceneNode*) node)->getMesh(), node);
            std::cout << "methode 6" << std::endl;
            break;

        case scene::ESNT_TERRAIN:
            selector = _smgr->createTerrainTriangleSelector((scene::ITerrainSceneNode*) node);
            std::cout << "methode 5" << std::endl;
            //            ((scene::ITerrainSceneNode*) node)->overrideLODDistance(1000,1000000000);
            break;

        case scene::ESNT_OCTREE:
            selector = _smgr->createOctreeTriangleSelector(((scene::IMeshSceneNode*) node)->getMesh(), node);
            std::cout << "methode 6" << std::endl;
            break;

        default:
            std::cout << "methode 7 - " << (char) node->getType() << std::endl;
            // Don't create a selector for this node type
            break;
        }

        if (selector && node->getID() != 9999 && node->getID() != 9998 && node->getID() != 9997)
        {
            node->setTriangleSelector(selector);
            // Add it to the meta selector, which will take a reference to it
            meta->addTriangleSelector(selector);
            // And drop my reference to it, so that the meta selector owns it.
            selector->drop();
        }
        if (node->getID() == 9998)
        {
            _nodeRez = node;
            _joueur->setNodeRez(_nodeRez);
        }
        if (node->getID() == 9997)
        {
            spawnPoint.push_back(node);
        }
    }
    if (false)
    {
        std::string modele = "ascenseur.b3d";
        std::string texture = "texture_ascenseur.jpg";
        std::string normal = "normal_ascenseur.jpg";
        modele = "data/mesh/" + modele;
        texture = "data/mesh/" + texture;
        normal = "data/mesh/" + normal;
        PointeurIntelligent<ObjetPorte> objet = new ObjetPorte(modele.c_str(), texture.c_str(), normal.c_str());
        PointeurIntelligent<SuiteAnimations> animAscenseur = new SuiteAnimations;
        animAscenseur->push_back(new Animation(1, 1, 50));
        ackCore::ObjetManager::get()->addObjet(objet, "ascenseur");
        objet->setSuiteAnimation(animAscenseur);

        objet->addEtat(0, new EtatObjet(0));
        objet->addEtat(1, new EtatObjet(100));
        ackCore::ObjetManager::get()->setEtat("ascenseur", 0);
    }

#if false
    { // ajout de la porte
        irr::scene::IAnimatedMeshSceneNode* node = _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh("data/mesh/porte.b3d"), 0, ID_IsNotPickable);
        node->setScale(irr::core::vector3df(1, 1, 1));
        selector = _smgr->createTriangleSelector(node);
        node->setTriangleSelector(selector);
        meta->addTriangleSelector(selector);
    }
#else
    {

        //        PointeurIntelligent<ObjetPorte> porte = new ObjetPorte("data/mesh/porte.b3d", "data/mesh/porte.jpg", "");
        //
        //        PointeurIntelligent<SuiteAnimations> animPorte = new SuiteAnimations;
        //        animPorte->push_back(new Animation(75, 75));
        //        //animPorte->push_back(new Animation(6, 74, -50));
        //        porte->setSuiteAnimation(animPorte);

        ObjetManager::get()->addToMeta(meta);
    }
#endif

    justOneFrameChargement();

    selector_sauv = meta;
    _joueur->setMetaSelector(meta);
    irr::core::vector3df posSpawn = spawnPoint[(Random().generer(0, spawnPoint.size() - 1))]->getTransformedBoundingBox().getCenter();
    justOneFrameChargement();
    _joueur->afficher(posSpawn.X, posSpawn.Y, posSpawn.Z);
    justOneFrameChargement();
    node_sauv = _joueur->getNode();
    if (selector_sauv)
    {
        scene::ISceneNodeAnimator* anim = _smgr->createCollisionResponseAnimator(selector_sauv, _joueur->getNode(), core::vector3df(0.20, 0.60, 0.30), core::vector3df(0, -0, 0), core::vector3df(0,
                +0.50, 0));
        _joueur->getNode()->addAnimator(anim);
        anim->drop(); // And likewise, drop the animator when we're done referring to it.
    }
    justOneFrameChargement();

    int lastFPS = -1;
    u32 then = _device->getTimer()->getTime();

    //node_sauv->setJointMode(irr::scene::EJUOR_CONTROL); // To write positions to the mesh on render


    //int z=0;//pas pour le fun
    core::vector3df ancienPos;
    core::vector3df ancienRot;
    ancienPos.X = 0;
    ancienPos.Y = 0;
    ancienPos.Z = 0;
    ancienRot.X = 0;
    ancienRot.Y = 0;
    ancienRot.Z = 0;
    //	bool envoi_mess = false;
    float tempsEcouleSansMajPerso = 1;
    float tempsAvantMajDeclancheur = 0.3;
    _smgr->setActiveCamera(_camera);
    _device->getCursorControl()->setVisible(false);
    DeclencheursManager::get()->startDeclencheurs();
    // bill->getMaterial(0).
    //node_sauv->addChild(bill);
    // log->stopChargement();
    justOneFrameChargement();
    finishChargement();
    _interp->majCara(_joueur->getCaracteristique());

    while (_device->run())

        if (_device->isWindowActive()) //la boucle "infini"
        {
            // Work out a frame delta time.
            const u32 now = _device->getTimer()->getTime();
            f32 frameDeltaTime = (f32) (now - then) / 1000.f; // Time in seconds
            then = now;
            if (frameDeltaTime > 0.1)
            {
                frameDeltaTime = 0.1;
            }
            tempsAvantMajDeclancheur -= frameDeltaTime;
            if ((tempsEcouleSansMajPerso += frameDeltaTime) > 0.02)
            {
                tempsEcouleSansMajPerso -= frameDeltaTime;
                PersoManager::get()->maj();//fait ce que le réseau a demandé.
            }
            else
            {
                if (PersoManager::get()->tryMaj())//fait ce que le réseau a demandé si le réseau n'as pas bloqué la ressource
                {
                    tempsEcouleSansMajPerso -= frameDeltaTime;
                }
            }

            _receiver->majPerso(frameDeltaTime);

            _receiver->majCam(frameDeltaTime); // déplace la camera suivant les évenements reçu entre temps
            driver->beginScene(true, true, 0);

            //node_sauv->animateJoints();

            //scene::ISceneNode* hand=node_sauv->getJointNode("hand.L");
            //                hand->addChild(ninja4.getNode());


            //scene::ISceneNode* mainDuPerso = node_sauv->getJointNode("hand.L");
            //mainDuPerso->setParent(ninja3.getNode());
            //ninja2.teleport(mainDuPerso->getPosition().X,mainDuPerso->getPosition().Y,mainDuPerso->getPosition().Z);
            //std::cout<<mainDuPerso->getPosition().X << std::endl;

            //ninja2.getNode()->getXJointNode("hand.L")->setParent(ninja4.getNode());

            _smgr->drawAll();

            _protocole->calculReception(frameDeltaTime);
            _joueur->deplacement(*_receiver, frameDeltaTime);
            PersoManager::get()->majAttaqueAllPerso();
            ObjetManager::get()->majAll(frameDeltaTime);
            MessageManager::get()->majAll(frameDeltaTime);

            //            std::cout << _joueur->getVie() << std::endl;
            // std::cout << _joueur->alloYAQuelquUn() << std::endl;
            bool animChanged = _joueur->isAnimChanged();
            if (node_sauv->getPosition().X != ancienPos.X || node_sauv->getPosition().Y != ancienPos.Y || node_sauv->getPosition().Z != ancienPos.Z || node_sauv->getRotation().X != ancienRot.X
                    || node_sauv->getRotation().Y != ancienRot.Y || node_sauv->getRotation().Z != ancienRot.Z || animChanged || _receiver->IsKeyDown(KEY_KEY_F))
            {
                AudioManager::get()->setCoordonneesEcouteur(node_sauv->getAbsolutePosition());
                if (tempsAvantMajDeclancheur < 0)
                {
                    DeclencheursManager::get()->majJoueur();
                    tempsAvantMajDeclancheur = 0.01;
                }
                //c1->mouvement(node_sauv->getPosition().X, node_sauv->getPosition().Y, node_sauv->getPosition().Z);

                if (animChanged)
                {
                    _app.envoyerDeplacement(node_sauv->getPosition(), node_sauv->getRotation(), _protocole, _joueur->getAnim());
                }
                else
                {
                    _app.envoyerDeplacement(node_sauv->getPosition(), node_sauv->getRotation(), _protocole);
                }
                ancienPos = node_sauv->getPosition();
                ancienRot = node_sauv->getRotation();
            }
            int fps = driver->getFPS();

            //interface
            _interp->draw();

            if (lastFPS != fps)
            {
                core::stringw str = "Acharn - Version 3D :";
                str += driver->getName();
                str += " - FPS:";
                str += fps;

                _device->setWindowCaption(str.c_str());
                lastFPS = fps;
            }
            driver->endScene();
        }
    DeclencheursManager::get()->stopDeclencheurs();
    AudioManager::get()->drop();
    _protocole->deconnexion(_joueur->saveCara(), _joueur->saveComp(), _joueur->saveSac(), _joueur->saveEquip(), _joueur->saveTexture());
    _device->drop();

}
void ackCore::Jeu::makeChargement()
{
    //    irr::scene::ISceneManager* sm = _device->getSceneManager();
    _device->getSceneManager()->createNewSceneManager();

    // irr::scene::IMeshSceneNode* arbre = _device->getSceneManager()->addMeshSceneNode(_device->getSceneManager()->getMesh("mesh/tree.b3d"));
    //  arbre->setPosition(irr::core::vector3df(20,20,20));
    _device->getSceneManager()->setAmbientLight(irr::video::SColorf(1.0f, 1.0f, 1.0f));
    // _device->getSceneManager()->addLightSceneNode(0,arbre->getAbsolutePosition()+irr::core::vector3df(10,0,0), irr::video::SColorf(1.0f,1.0f,1.0f));
    _cameraChargement = _device->getSceneManager()->addCameraSceneNode();
    //  camera->setTarget(arbre->getAbsolutePosition());
    //0,irr::core::vector3df(0,0,0), arbre->getAbsolutePosition(),0, true);
    irr::core::array<irr::video::ITexture*>* array = new irr::core::array<irr::video::ITexture*>();
    irr::video::ITexture* tex;
    std::cout << _device->getVideoDriver() << std::endl;
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0001.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0002.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0003.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0004.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0005.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0006.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0007.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0008.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0009.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0010.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0011.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0012.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0013.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0014.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0015.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0016.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0017.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0018.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0019.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0020.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0021.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0022.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0023.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0024.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0025.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0026.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0027.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0028.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0029.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0030.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0031.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0032.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0033.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0034.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0035.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0036.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0037.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0038.png");
    array->push_back(tex);
    tex = _device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0039.png");
    array->push_back(tex);
    irr::scene::ISceneNodeAnimator* paulo = _device->getSceneManager()->createTextureAnimator(*array, 40, true);
    irr::scene::IBillboardSceneNode* _bill = _device->getSceneManager()->addBillboardSceneNode();
    _bill->addAnimator(paulo);
    _bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _bill->setPosition(irr::core::vector3df(500, 500, 500));
    _cameraChargement->setPosition(irr::core::vector3df(505, 500, 500));
    _cameraChargement->setTarget(_bill->getPosition());

    _device->getSceneManager()->setActiveCamera(_cameraChargement);

}

void ackCore::Jeu::justOneFrameChargement()
{
    if (_device->run() && _device->isWindowActive()) //la boucle pas du tout "infini" ici
    {
        _device->getVideoDriver()->beginScene(true, true, 0);
        _device->getSceneManager()->drawAll();
        _device->getVideoDriver()->endScene();
    }
}

void ackCore::Jeu::finishChargement()
{
    _device->getSceneManager()->setActiveCamera(_camera);
}
