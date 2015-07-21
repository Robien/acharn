/*
 * ObjetPorte.h
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#ifndef OBJETPORTE_H_
#define OBJETPORTE_H_
#include <iostream>
#include <irrlicht.h>
#include "../include/ObjetPhysiqueAnimed.h"

namespace ackCore
{

class ObjetPorte: public ackCore::ObjetPhysiqueAnimed
{
public:
    ObjetPorte(std::string path, std::string diffuse, std::string normale, bool joueurCollision = true, bool cameraCollision = true); // ne peut pas être false, true
    virtual ~ObjetPorte();

    irr::scene::ITriangleSelector* getSelector();

private:


};

} // namespace ackCore

#endif /* OBJETPORTE_H_ */
