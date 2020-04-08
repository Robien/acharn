/*
 * Login.h
 *
 *  Created on: 6 sept. 2010
 *      Author: romain
 */

#ifndef LOGIN_H_
#define LOGIN_H_
#include <irrlicht.h>
#include "../include/Referenced.h"
#include <thread>

namespace ackCore
{

class Login: public Referenced
{
public:
    Login(irr::IrrlichtDevice* device);
    virtual ~Login();
    void chargement();
    void stopChargement();
    irr::IrrlichtDevice* _device;
private:
    static void* goTread(ackCore::Login* login);
    std::thread* _threadChargement;
    irr::scene::IBillboardSceneNode* _bill;
    irr::scene::ICameraSceneNode* _camera;


};

} // namespace ackCore

#endif /* LOGIN_H_ */
