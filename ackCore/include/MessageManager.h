/*
 * MessageManager.h
 *
 *  Created on: 9 nov. 2010
 *      Author: romain
 */

#ifndef MESSAGEMANAGER_H_
#define MESSAGEMANAGER_H_

#include "Singleton.h"
#include <irrlicht.h>
#include "../include/MessageVie.h"
#include <vector>
#include "../../ackUtils/include/PointeurIntelligent.h"

class MessageManager : public Singleton<MessageManager>
{
public:
    MessageManager();
    virtual ~MessageManager();

public:
   void addMessage(MessageVie* message);

public:
    void majAll(float delta);

private:
    std::vector<PointeurIntelligent<MessageVie> >* _messages;
};

#endif /* MESSAGEMANAGER_H_ */
