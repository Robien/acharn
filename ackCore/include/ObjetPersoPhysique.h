/*
 * ObjetPersoPhysique.h
 *
 *  Created on: 23 sept. 2010
 *      Author: romain
 */

#ifndef OBJETPERSOPHYSIQUE_H_
#define OBJETPERSOPHYSIQUE_H_

#include <ISceneNode.h>
#include <irrlicht.h>

namespace ackCore
{

class ObjetPersoPhysique: public irr::scene::ISceneNode
{
public:
    ObjetPersoPhysique(irr::IrrlichtDevice* device);
    virtual ~ObjetPersoPhysique();
protected:
    irr::IrrlichtDevice* _device;

};

} // namespace ackCore

#endif /* OBJETPERSOPHYSIQUE_H_ */
