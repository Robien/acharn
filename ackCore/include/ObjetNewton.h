/*
 * ObjetNewton.h
 *
 *  Created on: 2 nov. 2010
 *      Author: romain
 */

#ifndef OBJETNEWTON_H_
#define OBJETNEWTON_H_

#include "../include/ObjetPersoPhysique.h"
#include <irrlicht.h>

namespace ackCore
{

class ObjetNewton : public ObjetPersoPhysique
{
public:
    ObjetNewton(irr::IrrlichtDevice* device);
    virtual ~ObjetNewton();

public:
    void maj(float delta);

private:
    irr::core::vector3df _vitesse;

private:
    bool toucheQuelquechose(irr::core::vector3df vec);
};

}

#endif /* OBJETNEWTON_H_ */
