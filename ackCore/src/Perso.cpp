/*
 * =====================================================================================
 *
 *       Filename:  Perso.cpp
 *
 *    Description:  implementation de Perso -> objet gérant l'affichage des personnages
 *
 *        Version:  1.0
 *        Created:  05/04/2010 18:33:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "Perso.h"
#include <irrlicht.h>
#include <math.h>
#include "../include/EventReceiver.h"
#include "../../ackUtils/include/TextureMaker.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//deplacement du personage principal
#define VITESSE_DEPLACEMENT 200
#define VITESSE_SANS_GLISSEMENT 150 //vitesse du mesh pour laquelle l'anim de déplacement colle bien
using namespace irr;
using namespace std;

void Perso::teleport_rel(float x, float y, float z)
{
    if (_node)
    {
        irr::core::vector3df pos = _node->getPosition();

        px = pos.X + x;
        py = pos.Y + y;
        pz = pos.Z + z;

        _node->setPosition(core::vector3df(px, py, pz));

    }
    else
    {

        afficher(x, y, z);

    }
}
void Perso::teleport(float x, float y, float z)
{
    if (_node)
    {

        _node->setPosition(core::vector3df(x, y, z));
        px = x;
        py = y;
        pz = z;
    }
    else
    {
        std::cout << "Si cette ligne s'affiche, faut prévenir Romain !" << std::endl; // hé ouais !
        afficher(x, y, z);
    }
}
void Perso::tourner(float x, float y, float z)
{

    _node->setRotation(core::vector3df(x, y, z));

    rotx = x;
    roty = y;
    rotz = z;
}
void Perso::tourner_rel(float x, float y, float z)
{
    irr::core::vector3df pos = _node->getRotation();
    rotx = pos.X + x;
    roty = pos.Y + y;
    rotz = pos.Z + z;

    _node->setRotation(core::vector3df(rotx, roty, rotz));

}

void Perso::calcul_position(float delta)
{
    float a = 0;
    float b = 0;
    float c = 0;
    float ra = 0;
    float rb = 0;
    float rc = 0;
    //on est arrivé ?
    //rotation
    if (rotx != frotx)
    {
        ra = delta * vrotx * (frotx - rotx) / (fabs(frotx - rotx));
    }
    if (roty != froty)
    {
        rb = delta * vroty * (froty - roty) / (fabs(froty - roty));
    }
    if (rotz != frotz)
    {
        rc = delta * vrotz * (frotz - rotz) / (fabs(frotz - rotz));
    }
    //translation
    if (px != fpx)
    {
        a = delta * vpx * (fpx - px) / (fabs(fpx - px));
    }
    if (py != fpy)
    {
        b = delta * vpy * (fpy - py) / (fabs(fpy - py));
    }
    if (pz != fpz)
    {
        c = delta * vpz * (fpz - pz) / (fabs(fpz - pz));
    }

    //on est proche de la destination ?
    //rotation
    if ((frotx - rotx) > delta * vrotx)
    {
        rotx += ra;
    }
    else
    {
        rotx = frotx;
    }
    if ((froty - roty) > delta * vroty)
    {
        roty += rb;
    }
    else
    {
        roty = froty;
    }
    if ((frotz - rotz) > delta * vrotz)
    {
        rotz += rc;
    }
    else
    {
        rotz = frotz;
    }
    //translation
    if ((fpx - px) > delta * vpx)
    {
        px += a;
    }
    else
    {
        px = px;
    }
    if ((fpy - py) > delta * vpy)
    {
        py += b;
    }
    else
    {
        py = py;
    }
    if ((fpz - pz) > delta * vpz)
    {
        pz += c;
    }
    else
    {
        pz = pz;
    }

    //		std::cout << a << " - " << delta << " - " << rotx<< std::endl;

    _node->setRotation(core::vector3df(rotx, roty, rotz));
    _node->setPosition(core::vector3df(px, py, pz));

    //std::cout<<a<<std::endl;
}
void Perso::tourner_vers(float x, float y, float z)
{
    frotx = x;
    froty = y;
    frotz = z;
}
void Perso::aller_vers(float x, float y, float z)
{
    fpx = x;
    fpy = y;
    fpz = z;
}
scene::IAnimatedMeshSceneNode* Perso::getNode()
{
    return _node;
}

void Perso::setScale(float x, float y, float z)
{

    _node->setScale(core::vector3df(x, y, z));

}

void Perso::afficher(float x, float y, float z, std::string pseudo, std::string mesh, std::string normal, string texture)
{
    texturecorp = texture;
    //      video::IVideoDriver* driver = _device->getVideoDriver();
    px = x;
    py = y;
    pz = z;

    // And this B3D file uses skinned skeletal animation.
    _node = _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh(mesh.c_str()), 0, ID_IsNotPickable);
    _node->setPosition(core::vector3df(x, y, z));

    //_node->getMaterial(0).NormalizeNormals = true;
    //      boost::shared_ptr<scene::ITriangleSelector> selector(smgr->createTriangleSelector(node.get()));

    _node->setID(IDFlag_IsPickable);

    video::ITexture* persoNormalMap = _device->getVideoDriver()->getTexture(normal.c_str());
    _node->setMaterialFlag(video::EMF_GOURAUD_SHADING, true);

    if (persoNormalMap)
    {

        _device->getVideoDriver()->makeNormalMapTexture(persoNormalMap, 2.5f);
        _node->setMaterialTexture(1, persoNormalMap);

        _node->setMaterialType(video::EMT_NORMAL_MAP_SOLID);

    }
cout << " --------------------------------------------------------------------------------------------" << endl;

    if (!textureperso->empty()) //ajoute des tshirt qu'il a sauvegardé
    {
        changeTexture();
        cout << " ------------------------------------------1-------------------------------------------" << endl;
    }
    else if (mesh == "data/mesh/character.b3d") //ajoute du premier tshirt
    {
        cout << " ------------------------------------------2-------------------------------------------------" << endl;
        vector<string>* v_texture = new vector<string>();
        vector<string>* v_masque = new vector<string>();
        v_texture->push_back(texture);
        v_texture->push_back("data/mesh/texture_chaussure.png");
        v_masque->push_back("data/mesh/texture_chaussure.png");
        v_texture->push_back("data/mesh/texture_pantalon.png");
        v_masque->push_back("data/mesh/texture_pantalon.png");
        v_texture->push_back("data/mesh/texture_tshirt1.png");
        v_masque->push_back("data/mesh/texture_tshirt1.png");
        video::ITexture* persoT = TextureMaker::get()->createTextureByCopy(v_texture, v_masque, _device);
        if (persoT)
        {
            _node->setMaterialTexture(0, persoT);
        }
    }
    else //non humanoide texture de base
    {
        video::ITexture* persoT = _device->getVideoDriver()->getTexture(texture.c_str());
        if (persoT)
        {
            _node->setMaterialTexture(0, persoT);
        }
    }

    // add shadow
    //      _node->addShadowVolumeSceneNode(_node->getMesh(), 0, true, 1);
    //      getDevice()->getSceneManager()->setShadowColor(video::SColor(150,0,0,0));
    if (mesh == "data/mesh/character.b3d")
    {
        _node->setScale(core::vector3df(0.45, 0.45, 0.45));
    }
    else
    {
        _node->setScale(core::vector3df(0.15, 0.15, 0.15));
    }
    _node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
    //    _node->setMaterialFlag(video::EMF_ANISOTROPIC_FILTER, true);
    setAnim(Perso::STAND);
    //scene::ISceneNode bone = node->getBoneSceneNode("hand.L");
    wchar_t message[100];
    mbstowcs(message, pseudo.c_str(), strlen(pseudo.c_str()) + 1);
    _device->getSceneManager()->addBillboardTextSceneNode(0, message, _node, irr::core::dimension2d<float>(1, 1), irr::core::vector3df(0, 1.5, 0));
    if (mesh == "data/mesh/character.b3d")
    {
        addEpee();
        _nodeEpee->setScale(irr::core::vector3df(9, 9, 9));
        _nodeEpee->setRotation(irr::core::vector3df(90, 0, 0));
        _nodeEpee->setPosition(core::vector3df(0, 1, 0));
        _enMain = false;
        irr::scene::ISceneNode* hand = _node->getJointNode("weapon_shoulder.L");
        hand->addChild(_nodeEpee);
        //    irr::scene::IAnimatedMeshSceneNode bone = _node->getJointNode("weapon_shoulder.L");
        //scene::ISceneNode bone = _node->getBoneSceneNode();
    }
}

void Perso::changeTexture()
{
    if (textureperso->size() != 0 && !texturecorp.empty())
    {
        if (textureperso->size() == 1)
        {
            cout << "texture: " << (*textureperso)[0] << endl;
            video::ITexture* persoT = TextureMaker::get()->createTextureByCopy(texturecorp, (*textureperso)[0], (*textureperso)[0], _device);
            if (persoT)
            {
                _node->setMaterialTexture(0, persoT);
                std::cout << "Perso::changeTexture::setTexture 1 " << std::endl;
            }
        }
        else
        {
            vector<string> tex = (*textureperso);
            tex.insert(tex.begin(), texturecorp);

            video::ITexture* persoT = TextureMaker::get()->createTextureByCopy(&tex, textureperso, _device);
            if (persoT)
            {
                std::cout << "Perso::changeTexture::setTexture 2 " << std::endl;
                _node->setMaterialTexture(0, persoT);
            }
        }
    }

}

Perso::Perso(IrrlichtDevice* device)
{
    _tempsAvantFinMort = 1000.0;
    _enMain = false;
    _animLocked = false;
    //vitesse de base
    vpx = vpy = vpz = 0;
    vrotx = vroty = vrotz = -100;
    //rotation de base
    rotx = roty = rotz = 0;
    px = py = pz = 0;
    _device = device;
    _ancienAnim = Perso::MARCHER;
    _etat = Perso::DEPLACEMENT;

    deplace = false;
    sensAvant = true;
    tourne = false;
    _isAnimChanged = true;
    _tempsAvantFinAnim = -1;
    textureperso = new vector<string> ;
}

Perso::~Perso()
{
}

void Perso::setFrameAnim(int deb, int fin)
{
    _node->setFrameLoop(deb, fin);
}

void Perso::setFramePerSecond(float vitesse)
{
    _node->setAnimationSpeed(vitesse);
}

const irr::core::vector2di Perso::getRangeAnimByType(Perso::typeAnim type)
{
    switch (type)
    {
    case Perso::MARCHER:
        return irr::core::vector2di(10, 49);
    case Perso::COURRIR:
        return irr::core::vector2di(340, 398);
    case Perso::STAND:
        return irr::core::vector2di(1, 1);
    case Perso::TOURNE:
        return irr::core::vector2di(60, 75);
    case Perso::POSEROBERT:
        return irr::core::vector2di(100, 100);
    case Perso::POSECOMBATA2M:
        return irr::core::vector2di(120, 159);
    case Perso::FRAPERA2M:
        return irr::core::vector2di(160, 198);
    case Perso::POSECOMBATMN:
        return irr::core::vector2di(200, 238);
    case Perso::INCANT:
        return irr::core::vector2di(240, 278);
    case Perso::INCANT2STAND:
        return irr::core::vector2di(280, 310);
    case Perso::JUMP:
        return irr::core::vector2di(430, 481);
    case Perso::NAGE:
        return irr::core::vector2di(490, 558);
    case Perso::COUPDEPOING:
        return irr::core::vector2di(570, 638);
    case Perso::DYING:
        return irr::core::vector2di(689, 715);
    case Perso::DEAD:
        return irr::core::vector2di(710, 710);
    case Perso::DEMO:
        return irr::core::vector2di(0, 1000);
    default:
        return irr::core::vector2di(1, 1);

    }
}

const Perso::typeEtat Perso::getEtatByAnim(Perso::typeAnim type)
{
    switch (type)
    {
    case Perso::MARCHER:
        return Perso::DEPLACEMENT;
    case Perso::COURRIR:
        return Perso::DEPLACEMENT;
    case Perso::STAND:
        return Perso::IMMOBILE;
    case Perso::TOURNE:
        return Perso::DEPLACEMENT;
    case Perso::POSEROBERT:
        return Perso::IMMOBILE;
    case Perso::POSECOMBATA2M:
        return Perso::POSECOMBAT;
    case Perso::FRAPERA2M:
        return Perso::COMBAT;
    case Perso::POSECOMBATMN:
        return Perso::POSECOMBAT;
    case Perso::INCANT:
        return Perso::COMBAT;
    case Perso::INCANT2STAND:
        return Perso::POSECOMBAT;
    default:
        return Perso::IMMOBILE;

    }
}

void Perso::unLockAnim()
{
    _animLocked = false;
}

void Perso::setAnimHolded(Perso::typeAnim type, bool EnAvant)
{
    setAnim(type, EnAvant);
    _animLocked = true;
}

void Perso::setAnim(Perso::typeAnim type, bool EnAvant)
{
    if (type == Perso::DEAD)
    {
        mortALInstant();
    }
    if (!_animLocked)
    {
        if (_ancienAnim != type)
        {
            _isAnimChanged = true;
            setFrameAnim(getRangeAnimByType(type));
            if (EnAvant)
            {
                setFramePerSecond(getFPS(type));
            }
            else
            {
                setFramePerSecond(-getFPS(type));
            }
            if (type == Perso::FRAPERA2M && _enMain == false)
            {
                irr::scene::ISceneNode* hand = _node->getJointNode("weapon_hand.R");
                _nodeEpee->setParent(hand);
                _nodeEpee->setPosition(irr::core::vector3df(0, -1.7, 0));
                _nodeEpee->setRotation(irr::core::vector3df(-90, 0, 0));
                _enMain = true;
            }
            else if (type != Perso::FRAPERA2M && _enMain == true)
            {
                irr::scene::ISceneNode* hand = _node->getJointNode("weapon_shoulder.L");
                _nodeEpee->setParent(hand);
                _nodeEpee->setPosition(irr::core::vector3df(0, 1, 0));
                _nodeEpee->setRotation(irr::core::vector3df(90, 0, 0));
                _enMain = false;
            }
            _etat = getEtatByAnim(type);
            _ancienAnim = type;
        }
    }
}

bool Perso::checkIfActionPossible(Perso::typeAnim type) //casseeee
{
    Perso::typeEtat typeEtat = getEtatByAnim(type);
    return ((typeEtat == Perso::IMMOBILE && _etat == Perso::DEPLACEMENT) || (typeEtat == Perso::DEPLACEMENT && _etat == Perso::IMMOBILE) || (typeEtat == Perso::DEPLACEMENT && _etat == Perso::COMBAT)
            || (typeEtat == Perso::DEPLACEMENT && _etat == Perso::POSECOMBAT) || (typeEtat == Perso::COMBAT && _etat == Perso::POSECOMBAT) || (typeEtat == _etat) || (typeEtat == Perso::POSECOMBAT
            && _etat == Perso::COMBAT));
    /*
     stand > marcher
     marcher > combat
     marcher > posecombat
     combat = posecombat
     return true;
     */
}

void Perso::maj(float delta)
{
    //calcul_position(delta);
    if (_tempsAvantFinAnim > -1)
    {
        _tempsAvantFinAnim -= delta;

        if (_tempsAvantFinAnim <= 0)
        {
            _tempsAvantFinAnim = -1;
            if (_etat == Perso::COMBAT)
            {
                setAnim(Perso::STAND);
            }
        }
    }
    //    std::cout << _tempsAvantFinMort << std::endl;
    if (_tempsAvantFinMort != 1000.0)
    {
        _tempsAvantFinMort -= delta;
    }
    if (_tempsAvantFinMort <= 0)
    {
        _tempsAvantFinMort = 0;
        unLockAnim();
        setAnimHolded(Perso::DEAD);
    }
}

void Perso::pousse(irr::core::line3df direction)
{
    irr::core::vector3df vecteurVitesse(direction.end.X - direction.start.X, direction.end.Y - direction.start.Y, direction.end.Z - direction.start.Z);

    vecteurVitesse = vecteurVitesse.normalize();
    vecteurVitesse *= 30;
    vecteurVitesse.Y += 30;
    vpx = vecteurVitesse.X;
    vpy = vecteurVitesse.Y;
    vpz = vecteurVitesse.Z;

    std::cout << "poof : " << vpx << " - " << vpy << " - " << vpz << std::endl;
}

void Perso::avancer(float dist, bool enAvant)
{
    if (getAnim() == Perso::DEAD)
    {
        return;
    }
    irr::core::vector3df pos = _node->getPosition();

    if (enAvant)
    {
        pos.Z -= (dist) * cos(_node->getRotation().Y * M_PI / 180) / 40;
        pos.X -= (dist) * sin(_node->getRotation().Y * M_PI / 180) / 40;
    }
    else
    {
        pos.Z += (dist) * cos(_node->getRotation().Y * M_PI / 180) / 40;
        pos.X += (dist) * sin(_node->getRotation().Y * M_PI / 180) / 40;

    }
    _node->setPosition(pos);
}
void Perso::avancerCote(float dist, bool droit)
{
    if (getAnim() == Perso::DEAD)
    {
        return;
    }
    irr::core::vector3df pos = _node->getPosition();

    if (droit)
    {
        pos.X += (dist) * cos(-_node->getRotation().Y * M_PI / 180) / 40;
        pos.Z += (dist) * sin(-_node->getRotation().Y * M_PI / 180) / 40;
    }
    else
    {
        pos.X -= (dist) * cos(-_node->getRotation().Y * M_PI / 180) / 40;
        pos.Z -= (dist) * sin(-_node->getRotation().Y * M_PI / 180) / 40;

    }
    _node->setPosition(pos);

}

void Perso::deplacement(EventReceiver & receiver, float frameDeltaTime)
{
    if (getAnim() == Perso::DEAD)
    {
        return;
    }
    if (!receiver.isGuiFocus())
    {
        deplace = false;
        tourne = false;
        if (receiver.avance())
        {
            avancer(VITESSE_DEPLACEMENT * frameDeltaTime, true);
            sensAvant = false;
            deplace = true;
            tourne = false;
        }
        else
        {
            if (receiver.IsKeyDown(irr::KEY_KEY_D))
            {
                tourner_rel(0, 200 * frameDeltaTime, 0);
                tourne = true;
            }
            if (receiver.IsKeyDown(irr::KEY_KEY_Q))
            {
                tourner_rel(0, -200 * frameDeltaTime, 0);
                tourne = true;
            }
            if (receiver.IsKeyDown(irr::KEY_KEY_Z))
            {
                sensAvant = false;
                deplace = true;
                tourne = false;
                avancer(VITESSE_DEPLACEMENT * frameDeltaTime, true);
            }
            if (receiver.IsKeyDown(irr::KEY_KEY_A))
            {
                sensAvant = true;
                deplace = true;
                tourne = false;
                avancerCote(VITESSE_DEPLACEMENT * frameDeltaTime);
            }
            if (receiver.IsKeyDown(irr::KEY_KEY_E))
            {
                sensAvant = true;
                deplace = true;
                tourne = false;
                avancerCote(VITESSE_DEPLACEMENT * frameDeltaTime, false);
            }
            if (receiver.IsKeyDown(irr::KEY_KEY_S))
            {
                sensAvant = true;
                deplace = true;
                tourne = false;
                avancer(VITESSE_DEPLACEMENT * frameDeltaTime, false);
            }
        }
    }
    else
    {
        deplace = false;
        tourne = false;
    }
    if (deplace)
    {
        setAnim(Perso::COURRIR, !sensAvant);// le mesh est a l'envers :-(
    }
    else if (!deplace && !tourne && (_ancienAnim != Perso::POSEROBERT && _ancienAnim != Perso::NAGE) && _etat != COMBAT && _etat != POSECOMBAT && (_ancienAnim != Perso::DEMO))
    {
        setAnim(Perso::STAND);

    }
    else if (tourne)
    {
        setAnim(Perso::TOURNE, !sensAvant);
    }
    maj(frameDeltaTime);
}

int Perso::getFPS(Perso::typeAnim type)
{
    switch (type)
    {
    case Perso::MARCHER:
        return 50;
    case Perso::COURRIR:
        return 90;
    case Perso::STAND:
        return 1;
    case Perso::TOURNE:
        return 25;
    case Perso::POSEROBERT:
        return 1;
    case Perso::POSECOMBATA2M:
        return 50;
    case Perso::FRAPERA2M:
        return 50;
    case Perso::POSECOMBATMN:
        return 50;
    case Perso::INCANT:
        return 50;
    case Perso::INCANT2STAND:
        return 50;
    case Perso::JUMP:
        return 50;
    case Perso::NAGE:
        return 50;
    case Perso::COUPDEPOING:
        return 50;
    case Perso::DYING:
        return 50;
    case Perso::DEAD:
        return 1;
    case Perso::DEMO:
        return 50;
    default:
        return 50;

    }
}

void Perso::addEpee()
{

    _nodeEpee = _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh("data/mesh/epee.b3d"), 0, ID_IsNotPickable);
    //_nodeEpee = _device->getSceneManager()->addAnimatedMeshSceneNode(_device->getSceneManager()->getMesh("data/mesh/batte.b3d"), 0, ID_IsNotPickable);
    //_node->getMaterial(0).NormalizeNormals = true;
    //  boost::shared_ptr<scene::ITriangleSelector> selector(smgr->createTriangleSelector(node.get()));

    _nodeEpee->setID(IDFlag_IsPickable);

    video::ITexture* armeT = _device->getVideoDriver()->getTexture("data/mesh/texture_epee.png");
    //video::ITexture* armeT = _device->getVideoDriver()->getTexture("data/mesh/texture_batte.jpg");
    video::ITexture* armeNormalMap = _device->getVideoDriver()->getTexture("data/mesh/normal_epee.jpg");

    if (armeNormalMap)
    {

        _device->getVideoDriver()->makeNormalMapTexture(armeNormalMap, 10.0f);

        _nodeEpee->setMaterialTexture(1, armeNormalMap);
        _nodeEpee->setMaterialType(video::EMT_NORMAL_MAP_SOLID);

    }
    if (armeT)
    {
        _nodeEpee->setMaterialTexture(0, armeT);
    }
    // add shadow
    //  _node->addShadowVolumeSceneNode();
    //  _smgr->setShadowColor(video::SColor(150,0,0,0));

    _nodeEpee->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
    //scene::ISceneNode bone = node->getBoneSceneNode("hand.L");

}
void Perso::setDead()
{
    if (_tempsAvantFinMort == 1000)
    {
        _tempsAvantFinMort = 16.0 / 50.0;
        setAnimHolded(Perso::DYING);
    }
}
void Perso::setAlive()
{
    _tempsAvantFinMort = 1000.0;
    unLockAnim();
    setAnim(Perso::STAND);
}

bool Perso::isAnimChanged()
{
    bool tmp = _isAnimChanged;
    _isAnimChanged = false;
    return tmp;
}

const Perso::typeAnim Perso::getAnim()
{
    return _ancienAnim;
}

void Perso::setAnimIfIsPossible(Perso::typeAnim type, bool sens)
{
    if (checkIfActionPossible(type))
    {
        setAnim(type, sens);
    }
}

void Perso::setFrameAnim(irr::core::vector2di range)
{
    setFrameAnim(range.X, range.Y);
}

IrrlichtDevice* Perso::getDevice()
{
    return _device;
}

void Perso::mortALInstant()
{
    std::cout << "ICI bientot : rien" << std::endl;
}

void Perso::setTexture(vector<string>* text)
{
    textureperso = text;
}

void Perso::setTexture()
{
    textureperso->clear();
}

void Perso::setTexture(string text)
{
    textureperso->push_back(text);
}

string Perso::saveTexture()
{
    string texture = "";
    std::cout << textureperso->size() << std::endl;
    if (textureperso->size() > 0)
    {
        texture = (*textureperso)[0];
        for (unsigned int i = 1; i < textureperso->size(); i++)
        {
            texture += "!" + (*textureperso)[i];
        }
    }
    return texture;

}
