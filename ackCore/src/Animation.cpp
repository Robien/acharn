/*
 * Animation.cpp
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#include "../include/Animation.h"

ackCore::Animation::Animation(int debut, int fin, float fps) :
    _debut(debut), _fin(fin), _fps(fps)
{
}

ackCore::Animation::~Animation()
{
}

int ackCore::Animation::getDebut()
{
    return _debut;
}

int ackCore::Animation::getFin()
{
    return _fin;
}

float ackCore::Animation::getFps()
{
    return _fps;
}
