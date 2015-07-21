/*
 * MessageVie.h
 *
 *  Created on: 9 nov. 2010
 *      Author: romain
 */

#ifndef MESSAGEVIE_H_
#define MESSAGEVIE_H_

#include "Referenced.h"
#include <irrlicht.h>
#include <iostream>

class MessageVie: public Referenced
{

public:
    typedef enum
      {
          GAINVIE, PERTEVIE, GAINXP
      } typeMessage;

public:
    MessageVie(irr::core::vector3df position, irr::IrrlichtDevice* device, float quantite, MessageVie::typeMessage type);
    MessageVie(irr::core::vector3df position, irr::IrrlichtDevice* device, std::string message, irr::video::SColor couleur); //autre messages
    virtual ~MessageVie();

public:
    bool maj(float delta);

private:
    float _tempsRestantAVivre;
    irr::scene::IBillboardTextSceneNode* _bill;
};

#endif /* MESSAGEVIE_H_ */
