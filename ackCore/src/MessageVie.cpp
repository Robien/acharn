/*
 * MessageVie.cpp
 *
 *  Created on: 9 nov. 2010
 *      Author: romain
 */

#include "../include/MessageVie.h"
#include "boost/lexical_cast.hpp"
#include "../include/MessageManager.h"

MessageVie::MessageVie(irr::core::vector3df position, irr::IrrlichtDevice* device, float quantite, MessageVie::typeMessage type)
{
    _tempsRestantAVivre = 2;
    if (type == MessageVie::PERTEVIE)
    {
        std::string degat;
        degat = boost::lexical_cast<std::string>(floor(quantite));
        degat = "-" + degat;
        wchar_t message[100];
        mbstowcs(message, degat.c_str(), strlen(degat.c_str()) + 1);
        _bill = device->getSceneManager()->addBillboardTextSceneNode(0, message, 0, irr::core::dimension2d<float>(1, 0.6), position, 0, irr::video::SColor(0, 255, 2, 2));

    }
    else if (type == MessageVie::GAINVIE)
    {
        std::string degat;
        degat = boost::lexical_cast<std::string>(floor(quantite));
        degat = "+" + degat;
        wchar_t message[100];
        mbstowcs(message, degat.c_str(), strlen(degat.c_str()) + 1);
        _bill = device->getSceneManager()->addBillboardTextSceneNode(0, message, 0, irr::core::dimension2d<float>(1, 0.6), position, 0, irr::video::SColor(0, 2, 255, 2));

    }
    else if (type == MessageVie::GAINXP)
    {
        std::string degat;
        degat = boost::lexical_cast<std::string>(floor(quantite));
        degat = "+" + degat;
        wchar_t message[100];
        mbstowcs(message, degat.c_str(), strlen(degat.c_str()) + 1);
        _bill = device->getSceneManager()->addBillboardTextSceneNode(0, message, 0, irr::core::dimension2d<float>(1, 0.6), position, 0, irr::video::SColor(0, 151, 40, 183));

    }

    MessageManager::get()->addMessage(this);

}

MessageVie::MessageVie(irr::core::vector3df position, irr::IrrlichtDevice* device, std::string message, irr::video::SColor couleur) //autre messages
{
    _tempsRestantAVivre = 2;

    wchar_t messagewc[100];
    mbstowcs(messagewc, message.c_str(), strlen(message.c_str()) + 1);
    _bill = device->getSceneManager()->addBillboardTextSceneNode(0, messagewc, 0, irr::core::dimension2d<float>(1 + strlen(message.c_str()) / 10, 0.6), position, 0, couleur);

    MessageManager::get()->addMessage(this);

}

MessageVie::~MessageVie()
{
}

bool MessageVie::maj(float delta)
{
    _tempsRestantAVivre -= delta;

    if (_tempsRestantAVivre <= 0)
    {
        _bill->remove();
        return false;
    }
    _bill->setPosition(_bill->getPosition() + irr::core::vector3df(0, 0.6 * delta, 0));

    return true;
}
