/*
 * Login.cpp
 *
 *  Created on: 6 sept. 2010
 *      Author: romain
 */
#define FENEL 800
#define FENEH 600
#define FULL_SCREEN false

#include <thread>
#include "../include/Login.h"
#include <memory>
#include <iostream>

ackCore::Login::Login(irr::IrrlichtDevice* device) :
    _device(device)
{


}

ackCore::Login::~Login()
{
}

void ackCore::Login::chargement()
{
    _threadChargement = new std::thread(&ackCore::Login::goTread, this);

}

void ackCore::Login::stopChargement()
{
    _bill->remove();
    _threadChargement->join();
    delete _threadChargement;
}

void* ackCore::Login::goTread(ackCore::Login* login)
{
    irr::video::E_DRIVER_TYPE driverType;

    int type = 3; // opengl

    switch (type)
    {
    case 1:
        driverType = irr::video::EDT_DIRECT3D9;
        break;
    case 2:
        driverType = irr::video::EDT_DIRECT3D8;
        break;
    case 3:
        driverType = irr::video::EDT_OPENGL;
        break;
    case 4:
        driverType = irr::video::EDT_SOFTWARE;
        break;
    case 5:
        driverType = irr::video::EDT_BURNINGSVIDEO;
        break;
    case 6:
        driverType = irr::video::EDT_NULL;
        break;
    default:
        exit(0);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////
    ////// étape 1 : création du device :

    //login->_device = irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(FENEL, FENEH), 16, FULL_SCREEN, true, true);

    irr::scene::ISceneManager* sm = login->_device->getSceneManager();
    login->_device->getSceneManager()->createNewSceneManager();



    // irr::scene::IMeshSceneNode* arbre = sm->addMeshSceneNode(sm->getMesh("mesh/tree.b3d"));
    //  arbre->setPosition(irr::core::vector3df(20,20,20));
    sm->setAmbientLight(irr::video::SColorf(1.0f, 1.0f, 1.0f));
    // sm->addLightSceneNode(0,arbre->getAbsolutePosition()+irr::core::vector3df(10,0,0), irr::video::SColorf(1.0f,1.0f,1.0f));
    login->_camera = sm->addCameraSceneNode();
    //  camera->setTarget(arbre->getAbsolutePosition());
    //0,irr::core::vector3df(0,0,0), arbre->getAbsolutePosition(),0, true);
    irr::core::array<irr::video::ITexture*>* array = new irr::core::array<irr::video::ITexture*>();
    irr::video::ITexture* tex;
    std::cout << login->_device->getVideoDriver() << std::endl;
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0001.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0002.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0003.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0004.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0005.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0006.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0007.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0008.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0009.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0010.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0011.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0012.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0013.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0014.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0015.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0016.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0017.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0018.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0019.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0020.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0021.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0022.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0023.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0024.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0025.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0026.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0027.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0028.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0029.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0030.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0031.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0032.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0033.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0034.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0035.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0036.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0037.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0038.png");
    array->push_back(tex);
    tex = login->_device->getVideoDriver()->getTexture("data/mesh/ecran_chargement/images_chargement/0039.png");
    array->push_back(tex);
    irr::scene::ISceneNodeAnimator* paulo = sm->createTextureAnimator(*array, 40, true);
    login->_bill = sm->addBillboardSceneNode();
    login->_bill->addAnimator(paulo);
    login->_bill->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    login->_camera->setTarget(login->_bill->getAbsolutePosition());
    login->_camera->setPosition(irr::core::vector3df(5, 0, 0));

    while (login->_device->run())
    {
        if (login->_device->isWindowActive()) //la boucle "infini"
        {
            login->_device->getVideoDriver()->beginScene(true, true, 0);
            sm->drawAll();
            login->_device->getVideoDriver()->endScene();
        }
    }
    sm->drop();
    return NULL;
}
