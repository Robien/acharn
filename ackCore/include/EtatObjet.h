/*
 * EtatObjet.h
 *
 *  Created on: 8 nov. 2010
 *      Author: romain
 */

#ifndef ETATOBJET_H_
#define ETATOBJET_H_

#include "Referenced.h"
#include "../include/Animation.h"

using ackCore::Animation;

class EtatObjet: public Referenced
{
public:
    EtatObjet(int frame);
    virtual ~EtatObjet();

    static ackCore::Animation* factory(EtatObjet* etat1, EtatObjet* etat2);

    int getFrame();

private:
    int frameFixe;
};

#endif /* ETATOBJET_H_ */
