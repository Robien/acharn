/*
 * MessageManager.cpp
 *
 *  Created on: 9 nov. 2010
 *      Author: romain
 */

#include "../include/MessageManager.h"

MessageManager::MessageManager()
{
    _messages = new std::vector<PointeurIntelligent<MessageVie> >;
}

MessageManager::~MessageManager()
{
}

void MessageManager::addMessage(MessageVie* message)
{
    _messages->push_back(message);
}

void MessageManager::majAll(float delta)
{
    if (_messages->size() > 0)
    {
        std::vector<PointeurIntelligent<MessageVie> >* messagesTmp = new std::vector<PointeurIntelligent<MessageVie> >;

        for (unsigned int i = 0; i < _messages->size(); ++i)
        {
            if ((*_messages)[i]->maj(delta))
            {
                messagesTmp->push_back((*_messages)[i]);
            }

        }
        delete _messages;
        _messages = messagesTmp;
    }
}

