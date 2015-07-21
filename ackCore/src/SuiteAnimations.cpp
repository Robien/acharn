/*
 * SuiteAnimations.cpp
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#include "../include/SuiteAnimations.h"

SuiteAnimations::SuiteAnimations(bool loop) : _loop(loop)
{
}

SuiteAnimations::~SuiteAnimations()
{
}

void SuiteAnimations::setIsLoopAnimation(bool loop)
{
    _loop = loop;
}
bool SuiteAnimations::getLoop()
{
    return _loop;
}
