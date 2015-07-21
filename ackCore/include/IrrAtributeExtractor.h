/*
 * IrrAtributeExtractor.h
 *
 *  Created on: 7 sept. 2010
 *      Author: romain
 */

#ifndef IRRATRIBUTEEXTRACTOR_H_
#define IRRATRIBUTEEXTRACTOR_H_

#include <ISceneUserDataSerializer.h>
#include "../include/Referenced.h"
#include <irrlicht.h>
#include <iostream>
#include "Jeu.h"

namespace ackCore
{

class IrrAtributeExtractor: public irr::scene::ISceneUserDataSerializer, public Referenced
{
public:
    IrrAtributeExtractor(Jeu* jeu);
    virtual ~IrrAtributeExtractor();
    void OnCreateNode(irr::scene::ISceneNode* node);
    void OnReadUserData(irr::scene::ISceneNode* forSceneNode, irr::io::IAttributes* userData);
    irr::io::IAttributes* createUserData(irr::scene::ISceneNode* forSceneNode);

private:
    PointeurIntelligent<Jeu> _jeu;

};

} // namespace ackCore

#endif /* IRRATRIBUTEEXTRACTOR_H_ */
