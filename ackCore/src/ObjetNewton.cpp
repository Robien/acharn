/*
 * ObjetNewton.cpp
 *
 *  Created on: 2 nov. 2010
 *      Author: romain
 */

#include "../include/ObjetNewton.h"

namespace ackCore
{

ObjetNewton::ObjetNewton(irr::IrrlichtDevice* device) :
    ObjetPersoPhysique(device)
{
}

ObjetNewton::~ObjetNewton()
{
}

void ObjetNewton::maj(float delta)
{

}

bool ObjetNewton::toucheQuelquechose(irr::core::vector3df vec)
{
    irr::core::line3d<irr::f32> ray;
    ray.start = getPosition();
    ray.end = getPosition() + vec;
    // Tracks the current intersection point with the level or a mesh
    irr::core::vector3df intersection;
    // Used to show with triangle has been hit
    irr::core::triangle3df hitTriangle;
    irr::scene::ISceneCollisionManager* collMan = _device->getSceneManager()->getSceneCollisionManager(); //jean-jacque collMan
    irr::scene::ISceneNode* selectedSceneNode = collMan->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle, // This will be the triangle hit in the collision
            0, // This ensures that only nodes that we have
            // set up to be pickable are considered
            0); // Check the entire scene (this is actually the implicit default)


    return (selectedSceneNode != NULL);

}
}
