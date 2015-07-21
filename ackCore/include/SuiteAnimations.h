/*
 * SuiteAnimations.h
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#ifndef SUITEANIMATIONS_H_
#define SUITEANIMATIONS_H_

#include <vector>
#include "../../ackUtils/include/PointeurIntelligent.h"
#include "../include/Animation.h"
#include "../../ackUtils/include/Referenced.h"

class SuiteAnimations: public std::vector<PointeurIntelligent<ackCore::Animation> >, public Referenced
{
public:
    SuiteAnimations(bool loop = true);
    virtual ~SuiteAnimations();

public:
    void setIsLoopAnimation(bool loop = true);

    bool getLoop();

private:
    bool _loop;
};

#endif /* SUITEANIMATIONS_H_ */
