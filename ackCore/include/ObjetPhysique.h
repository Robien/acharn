/*
 * Objet.h
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#ifndef OBJET_H_
#define OBJET_H_
#include "../include/Referenced.h"
#include <irrlicht.h>

namespace ackCore
{

class ObjetPhysique: public Referenced
{
public:
    ObjetPhysique(); //doit construire _node
    virtual ~ObjetPhysique();

    irr::scene::ITriangleSelector* getSelector();

    void setIsOnMeta(bool isOnMeta = true);
    bool isOnMeta();

    virtual void maj(float delta)
    {
    }

protected:
    irr::scene::IAnimatedMeshSceneNode* _node;

private:
    bool _isOnMeta;

};

} // namespace ackCore

#endif /* OBJET_H_ */
