/*
 * =====================================================================================
 *
 *       Filename:  EventReceiver.cpp
 *
 *    Description:  Traite les évenement
 *
 *        Version:  1.0
 *        Created:  14/05/2010 22:00:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Buffer.h"
#include "AudioManager.h"
#include "EventReceiver.h"
#include <math.h>
#include "boost/lexical_cast.hpp"
#include <irrlicht.h>
#include "../include/DeclencheursManager.h"
#define ANGLE_MAX_CAMERA 155
#define ANGLE_MIN_CAMERA 2
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace irr;
using namespace std;
using namespace gui;

EventReceiver::EventReceiver(MainPerso & joueur_n, ackCore::Appli& app, Protocole* protocole) :
    _joueur(joueur_n), _app(app), _protocole(protocole)
{
    _mWheel = true;
    _mIsPressed = false;
    _mIsPressedR = false;
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        _KeyIsDown[i] = false;
    _poscam.X = 0;
    _poscam.Y = 20;
    _poscam.Z = 0;
    _rho = 20;
    _maxRho = 20;
    _phi = 0;
    _theta = 0;
    _isOnGui = false;
    _isGuiFocus = false;
    _lock = false;

    _isCurseurVisible = true;
    _curseur = NULL;

    _images = _joueur.getDevice()->getVideoDriver()->getTexture("data/mesh/curseur/test_curseur.png");
    _joueur.getDevice()->getVideoDriver()->makeColorKeyTexture(_images, core::position2d<s32>(0, 0));

}

bool EventReceiver::OnEvent(const SEvent& event)
{
    if (event.EventType == EET_GUI_EVENT)
    {
        if (event.GUIEvent.EventType == EGET_ELEMENT_HOVERED && event.GUIEvent.Caller->getID() != 9999)
        {
            _isOnGui = true;
        }
        else if (event.GUIEvent.EventType == EGET_ELEMENT_LEFT)
        {
            _isOnGui = false;
        }
        else if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUSED && event.GUIEvent.Caller->getID() == 707)
        {
            _isGuiFocus = true;
        }
        else if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
        {
            _isGuiFocus = false;
        }
        else if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
        {
            s32 id = event.GUIEvent.Caller->getID();
            std::string msg;
            switch (id)
            {
            case 1:
                //_joueur.teleport_rel(0, 2, 0);
                _joueur.saute();
                break;
            case 2:
                _joueur.setAnim(Perso::NAGE);
                break;
            case 3:
                _joueur.avancer(130);
                break;
            case 4:
                _joueur.avancer(130, false);
                break;
            case 9905:
                _joueur.getInterface().switchLogVisible(true);
                break;
            case 9906:
                _joueur.getInterface().switchMenuJeuVisible(true);
                break;
            case 1337:

                msg = _joueur.getInterface().envoyerMessageChat();
                if (msg != "")
                {
                    if (msg[0] == '/')
                    {
                        if (msg == "/rand")
                        {
                            _app.envoyerMessage(msg, _protocole, _joueur.getRandom()->getNumero() + 1);
                            _joueur.getInterface().recevoirMessageChat("vous faites un " + boost::lexical_cast<std::string>(_joueur.getRandom()->genererParJoueur(0, 100)));
                        }
                        else if (msg == "/demo")
                        {
                            _joueur.setAnim(Perso::DEMO);
                        }
                        else
                        {
                            vector<string> info = split(msg.c_str(), ' ');
                            if (info[0] == "/tshirt" || info[0] == "/t")
                            {
                                if ((info[1].size() == 1 && isdigit(info[1][0])))
                                {
                                    string texte;
                                    texte += info[1][0];

                                    int valtshirt = converint(texte);
                                    if (valtshirt <= 34 && valtshirt > 0)
                                    {
                                        _joueur.setTexture();
                                        _joueur.setTexture("data/mesh/texture_chaussure.png");
                                        _joueur.setTexture("data/mesh/texture_pantalon.png");
                                        _joueur.setTexture("data/mesh/texture_tshirt" + texte + ".png");
                                        _joueur.changeTexture();
                                        _protocole->setTexture(_joueur.saveTexture());
                                    }
                                    else
                                    {
                                        string texte = "tshirt inexistant ! \n commande: /t nb (de 1à34)";
                                        _joueur.getInterface().recevoirMessageChat(texte);
                                    }
                                }
                                else if (info[1].size() == 2 && isdigit(info[1][0]) && isdigit(info[1][1]))
                                {
                                    string texte;
                                    texte += info[1][0];
                                    texte += info[1][1];
                                    int valtshirt = converint(texte);
                                    if (valtshirt <= 34 && valtshirt > 0)
                                    {
                                        _joueur.setTexture();
                                        // _joueur.setTexture("data/mesh/texture_chaussure.png");
                                        //  _joueur.setTexture("data/mesh/texture_pantalon.png");
                                        //  _joueur.setTexture("data/mesh/texture_tshirt" + texte + ".png");
                                        _joueur.changeTexture();
                                        _protocole->setTexture(_joueur.saveTexture());
                                    }
                                    else
                                    {
                                        string texte = "tshirt inexistant ! \n commande: /t nb (de 1à34)";
                                        _joueur.getInterface().recevoirMessageChat(texte);
                                    }
                                }
                                else
                                {
                                    string texte = "tshirt inexistant ! \n commande: /t nb (de 1à34)";
                                    _joueur.getInterface().recevoirMessageChat(texte);
                                }

                            }
                            else if (info[0] == "/attaque")
                            {//attaque

                                if ((info[1][0] != '\0' && isdigit(info[1][0])) || (info[1][1] != '\0' && isdigit(info[1][1])))
                                {
                                    string texte;
                                    texte += info[1][0];
                                    texte += info[1][1];
                                    _joueur.getInterface().recevoirMessageChat(" demande d'attaque: " + texte);
                                }
                                else
                                {
                                    string texte = _joueur.afficherCompetences();
                                    _joueur.getInterface().recevoirMessageChat(texte);
                                }
                            }
                        }
                    }
                    else
                    {
                        _app.envoyerMessage(msg, _protocole);
                        _joueur.getInterface().recevoirMessageChat("<" + _joueur.getNom() + "> dit : " + msg);
                    }
                }

                break;
            case 7:
            {
                _joueur.attaque(Perso::MAGIE);
                _joueur.setVie(_joueur.getVie() + _joueur.getVieMax() / 10);

            }
                break;
            case 8:
            {
                _joueur.setVie(_joueur.getVie() - _joueur.getVieMax() / 10);
            }
                break;

            case 9:
            {
                _joueur.attaque(Perso::MAGIE);
                _joueur.setRadiation(_joueur.getRadiation() + _joueur.getRadiationMax() / 10);

            }
                break;

            case 10:
            {
                _joueur.setRadiation(_joueur.getRadiation() - _joueur.getRadiationMax() / 10);
            }
                break;
            case 11:
            {
                if (_joueur.haveArme())
                {
                    _joueur.attaque(Perso::ARME2M);
                }
                else
                {
                    _joueur.attaque(Perso::MAINNUE);
                }
                std::vector<int>& enFace = _joueur.alloYAQuelquUn();
                std::vector<AbstractPerso*> perso;
                if (true)
                {
                	irr::core::vector3df position = _joueur.getNode()->getPosition();
                	AudioManager::get()->play(Buffer::EPEE, "epee", position,false,NULL);
                	AudioManager::get()->getSon("epee")->setVolumeSource(400);
                	AudioManager::get()->setCoordonneesSon("epee", position);
                }
                for (unsigned int i = 0; i < enFace.size(); ++i)
                {
                    perso.push_back(PersoManager::get()->getPersoById(enFace[i]));
                    _app.attaque(enFace[i], _protocole);
                    _app.attaqueFinale(enFace[i], _protocole);
                }
            }
                break;
            case 12:
                if (_joueur.getAnim() == Perso::DEAD)
                {
                    _joueur.setAlive();
                    _joueur.regeneration();
                    _joueur.tpRez();
                }
                break;
            case 13:
                _joueur.setVie(0);
                break;
            case 14:
            {
                _joueur.gainxp(23);
            }
                break;
            case 7301:
            {
                Caracteristique* cara = new Caracteristique();
                cara->opeCaracteristique((*_joueur.getInterface().appliquerNiveau()), true);
                cara->opeCaracteristique((*_joueur.getCaracteristique()), false);
                _joueur.addCaracteristique(cara);
            }
                break;
            case 7302:
            {
                _joueur.getInterface().afficherCara(false);
            }
                break;
            case 9901:
            {
                _joueur.getInterface().majCara(_joueur.getCaracteristique());
                _joueur.getInterface().afficherCara(true);
            }
                break;
            default:
                if (id >= 7200 && id <= 7220)
                {
                    _joueur.getInterface().cliquePoint(id);
                }
                break;
            }
            std::cout << id << std::endl;

        }
    }
    else if (!_isOnGui || event.EventType != EET_MOUSE_INPUT_EVENT)
    {
        if (event.EventType == EET_MOUSE_INPUT_EVENT)
        {
            if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
            {
                _positionSouris = (_joueur.getDevice())->getCursorControl()->getRelativePosition();
                _mIsPressed = true;
                _isCurseurVisible = false;

            }
            else if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
            {
                _mIsPressed = false;
                if (_mIsPressedR == false)
                {
                    _isCurseurVisible = true;
                }
            }
            else if (event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
            {

                _positionSouris = (_joueur.getDevice())->getCursorControl()->getRelativePosition();
                _mIsPressedR = true;
                _isCurseurVisible = false;

            }
            else if (event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP)
            {
                _mIsPressedR = false;
                if (_mIsPressed == false)
                {
                    _isCurseurVisible = true;
                }
            }
        }
        if (event.MouseInput.Event == irr::EMIE_MOUSE_WHEEL)
        {
            _mWheel = true;
            if (event.MouseInput.Wheel > 0)
            {
                _maxRho -= 1;
            }
            else
            {
                _maxRho += 1;
            }
            if (_maxRho < 1)
            {
                _maxRho = 1;
            }

        }

        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
            if (event.KeyInput.Key == KEY_SPACE && _KeyIsDown[KEY_SPACE] == false)
            {
                if (!_isOnGui)
                {
                    _joueur.saute();
                }
            }
            if (event.KeyInput.Key == KEY_RETURN && _KeyIsDown[KEY_RETURN] == false)
            {
                string msg;
                msg = _joueur.getInterface().envoyerMessageChat();
                if (msg != "")
                {
                    if (msg[0] == '/')
                    {
                        if (msg == "/rand")
                        {
                            _app.envoyerMessage(msg, _protocole, _joueur.getRandom()->getNumero() + 1);
                            _joueur.getInterface().recevoirMessageChat("vous faites un " + boost::lexical_cast<std::string>(_joueur.getRandom()->genererParJoueur(0, 100)));
                        }
                        else if (msg == "/demo")
                        {
                            _joueur.setAnim(Perso::DEMO);
                        }
                        else
                        {
                            vector<string> info = split(msg.c_str(), ' ');
                            if (info[0] == "/tshirt" || info[0] == "/t")
                            {
                                if ((info[1].size() == 1 && isdigit(info[1][0])))
                                {
                                    string texte;
                                    texte += info[1][0];

                                    int valtshirt = converint(texte);
                                    if (valtshirt <= 34 && valtshirt > 0)
                                    {
                                        _joueur.setTexture();
                                        _joueur.setTexture("data/mesh/texture_chaussure.png");
                                        _joueur.setTexture("data/mesh/texture_pantalon.png");
                                        _joueur.setTexture("data/mesh/texture_tshirt" + texte + ".png");
                                        _joueur.changeTexture();
                                        _protocole->setTexture(_joueur.saveTexture());
                                    }
                                    else
                                    {
                                        string texte = "tshirt inexistant ! \n commande: /t nb (de 1à34)";
                                        _joueur.getInterface().recevoirMessageChat(texte);
                                    }
                                }
                                else if (info[1].size() == 2 && isdigit(info[1][0]) && isdigit(info[1][1]))
                                {
                                    string texte;
                                    texte += info[1][0];
                                    texte += info[1][1];
                                    int valtshirt = converint(texte);
                                    if (valtshirt <= 34 && valtshirt > 0)
                                    {
                                        _joueur.setTexture();
                                        _joueur.setTexture("data/mesh/texture_tshirt" + texte + ".png");
                                        _joueur.changeTexture();
                                        _protocole->setTexture(_joueur.saveTexture());
                                    }
                                    else
                                    {
                                        string texte = "tshirt inexistant ! \n commande: /t nb (de 1à34)";
                                        _joueur.getInterface().recevoirMessageChat(texte);
                                    }
                                }
                                else
                                {
                                    string texte = "tshirt inexistant ! \n commande: /t nb (de 1à34)";
                                    _joueur.getInterface().recevoirMessageChat(texte);
                                }

                            }
                            else if (info[0] == "/attaque")
                            {//attaque

                                if ((info[1][0] != '\0' && isdigit(info[1][0])) || (info[1][1] != '\0' && isdigit(info[1][1])))
                                {
                                    string texte;
                                    texte += info[1][0];
                                    texte += info[1][1];
                                    _joueur.getInterface().recevoirMessageChat(" demande d'attaque: " + texte);
                                }
                                else
                                {
                                    string texte = "  /attaque numeroAttaque \n" + _joueur.afficherCompetences();
                                    _joueur.getInterface().recevoirMessageChat(texte);
                                }
                            }
                        }
                    }
                    else
                    {
                        _app.envoyerMessage(msg, _protocole);
                        _joueur.getInterface().recevoirMessageChat("<" + _joueur.getNom() + "> dit : " + msg);
                    }
                }
            }
            _KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        }
    }
    if (event.EventType == EET_KEY_INPUT_EVENT)
    {
        if (_KeyIsDown[KEY_KEY_F])
        {
            DeclencheursManager::get()->setBoutonActionOn();
        }
        else
        {
            DeclencheursManager::get()->setBoutonActionOff();
        }
    }

    return false;

}

void EventReceiver::majPerso(float delta)
{
    _joueur.appliqueVitesse(delta / 10);
}

void EventReceiver::majCam(float delta)
{
    _joueur.majCam();
    bool avance = _mIsPressed && _mIsPressedR;
    if (avance)
    {
        _mIsPressed = false;
    }
    if (_mIsPressed || _mWheel || _mIsPressedR)
    {

        if (!_mWheel)
        {
            _phi -= ((_joueur.getDevice())->getCursorControl()->getRelativePosition().Y - _positionSouris.Y) * 360;
            if (_phi > ANGLE_MAX_CAMERA)
            {
                _phi = ANGLE_MAX_CAMERA;
            }
            if (_phi < ANGLE_MIN_CAMERA)
            {
                _phi = ANGLE_MIN_CAMERA;
            }

            _theta -= ((_joueur.getDevice())->getCursorControl()->getRelativePosition().X - _positionSouris.X) * 360;
            if (_mIsPressedR)
            {
                _joueur.tourner_rel(0, -_theta + 90, 0);
                _theta = 90;
            }
        }

        _poscam.X = _rho * sin(_phi * M_PI / 180) * cos(_theta * M_PI / 180);
        _poscam.Z = _rho * sin(_phi * M_PI / 180) * sin(_theta * M_PI / 180);
        _poscam.Y = _rho * cos(_phi * M_PI / 180);

        (_joueur.getCamera())->setPosition(_poscam);
        if (!_mWheel)
        {
            (_joueur.getDevice())->getCursorControl()->setPosition(_positionSouris);
            _positionSouris = _joueur.getDevice()->getCursorControl()->getRelativePosition();
        }
        _mWheel = false;
    }
    gestionCollisionCamera(delta);
    _exPosPerso = _joueur.getNode()->getPosition();
    _exRotPerso = _joueur.getNode()->getRotation();
    _exPoscam = _joueur.getCamera()->getPosition();

    majCurseur();

    if (avance)
    {
        _mIsPressed = true;
    }

}

bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return _KeyIsDown[keyCode];
}

void EventReceiver::gestionCollisionCamera(float deltaTime)
{
    if (!(isEqual(_exPosPerso, _joueur.getNode()->getPosition()) && isEqual(_exPoscam, _joueur.getCamera()->getPosition()) && isEqual(_exRotPerso, _joueur.getNode()->getRotation())))
    {
        _lock = false;
    }
    scene::ISceneCollisionManager* collMan = _joueur.getDevice()->getSceneManager()->getSceneCollisionManager(); //jean-jacque collMan


    // All intersections in this example are done with a ray cast out from the camera to
    // a distance of 1000.  You can easily modify this to check (e.g.) a bullet
    // trajectory or a sword's position, or create a ray from a mouse click position using
    // ISceneCollisionManager::getRayFromScreenCoordinates()
    core::line3d<f32> ray;
    ray.end = _joueur.getCamera()->getAbsolutePosition();
    ray.start = _joueur.getNode()->getAbsolutePosition();
    ray.end = ray.end + (ray.end - ray.start).normalize() * -0.3f;
    //ray.end = ray.start + (ray.end - ray.start).normalize() * 1000.0f;
    //std::cout << ray.start.X << " - " << ray.end.X << std::endl;


    // Tracks the current intersection point with the level or a mesh
    core::vector3df intersection;
    // Used to show with triangle has been hit
    core::triangle3df hitTriangle;

    // This call is all you need to perform ray/triangle collision on every scene node
    // that has a triangle selector, including the Quake level mesh.  It finds the nearest
    // collision point/triangle, and returns the scene node containing that point.
    // Irrlicht provides other types of selection, including ray/triangle selector,
    // ray/box and ellipse/triangle selector, plus associated helpers.
    // See the methods of ISceneCollisionManager
    //	scene::ISceneNode * selectedSceneNode = collMan->getSceneNodeFromCameraBB(_joueur.getCamera().get(), IDFlag_IsPickable);

    scene::ISceneNode * selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, // This will be the triangle hit in the collision
            0, // This ensures that only nodes that we have
            // set up to be pickable are considered
            0); // Check the entire scene (this is actually the implicit default)


    if (selectedSceneNode == NULL)
    {
        core::line3d<f32> ray;
        ray.end = _joueur.getCamera()->getAbsolutePosition();
        ray.end.X += 1;
        ray.start = _joueur.getNode()->getAbsolutePosition();
        ray.end = ray.end + (ray.end - ray.start).normalize() * -0.3f;

        selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, 0, 0);
    }
    if (selectedSceneNode == NULL)
    {
        core::line3d<f32> ray;
        ray.end = _joueur.getCamera()->getAbsolutePosition();
        ray.end.X -= 1;
        ray.start = _joueur.getNode()->getAbsolutePosition();
        ray.end = ray.end + (ray.end - ray.start).normalize() * -0.3f;

        selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, 0, 0);
    }
    if (selectedSceneNode == NULL)
    {
        core::line3d<f32> ray;
        ray.end = _joueur.getCamera()->getAbsolutePosition();
        ray.end.Y += 1;
        ray.start = _joueur.getNode()->getAbsolutePosition();
        ray.end = ray.end + (ray.end - ray.start).normalize() * -0.3f;

        selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, 0, 0);
    }
    if (selectedSceneNode == NULL)
    {
        core::line3d<f32> ray;
        ray.end = _joueur.getCamera()->getAbsolutePosition();
        ray.end.Y -= 1;
        ray.start = _joueur.getNode()->getAbsolutePosition();
        ray.end = ray.end + (ray.end - ray.start).normalize() * -0.3f;

        selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, 0, 0);
    }
    float exRho = _rho;
    if (selectedSceneNode)
    {
        _lock = true;
        _rho -= 0.2 * deltaTime * 100;

    }
    else if (_rho < _maxRho)
    {
        if (!_lock)
        {
            _rho += 0.1 * deltaTime * 100;
        }

    }
    else if (_rho > _maxRho)
    {
        _rho = _maxRho;
    }
    if (_rho < 1)
    {
        _rho = 1;
    }
    if (exRho != _rho)
    {
        _poscam.X = _rho * sin(_phi * M_PI / 180) * cos(_theta * M_PI / 180);
        _poscam.Z = _rho * sin(_phi * M_PI / 180) * sin(_theta * M_PI / 180);
        _poscam.Y = _rho * cos(_phi * M_PI / 180);
        _joueur.getCamera()->setPosition(_poscam);
    }

}

bool EventReceiver::isEqual(irr::core::vector3df vec1, irr::core::vector3df vec2)
{
    return (abs(vec1.X - vec2.X) < 0.1 && abs(vec1.Y - vec2.Y) < 0.1 && abs(vec1.Z - vec2.Z) < 0.1);
}

void EventReceiver::majCurseur()
{
    if (_curseur != NULL)
    {
        _curseur->remove();
    }
    _curseur = NULL;
    if (_isCurseurVisible)
    {
        core::position2d<s32> m = _joueur.getDevice()->getCursorControl()->getPosition();
        if (m != _exPositionSouris)
        {
            m += core::position2d<s32>(-12, 3);
            _curseur = _joueur.getDevice()->getGUIEnvironment()->addImage(_images, m, true, 0, 9999);
            _exPositionSouris = m;
        }
    }
}

bool EventReceiver::avance()
{
    return _mIsPressed && _mIsPressedR;
}
