/*
 * Animation.h
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "Referenced.h"
namespace ackCore
{

class Animation: public Referenced
{
public:
    Animation(int debut, int fin, float fps = 50.0);
    virtual ~Animation();

public:
    int getDebut();
    int getFin();
    float getFps();

private:
    int _debut;
    int _fin;
    float _fps;
};

} // namespace ackCore
#endif /* ANIMATION_H_ */
