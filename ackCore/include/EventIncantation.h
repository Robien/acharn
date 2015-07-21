/*
 * EventIncantation.h
 *
 * Callback signalant le debut d'une incantation
 * A la fin de celle ci il faut appeler endOfIncantation
 * de AbstractPerso pour affecter réelement l'attaque aux cibles
 *
 *  Created on: 6 oct. 2010
 *      Author: céphise
 */

#ifndef EVENTINCANTATION_H_
#define EVENTINCANTATION_H_

#include "CallbackIncantation.h"
#include "iostream"

class EventIncantation: public CallbackIncantation
{

public:

    EventIncantation(int id);
    virtual ~EventIncantation();
    void incantation(float temps, int type, float portee);

private:
    int _id;
};

#endif /* EVENTINCANTATION_H_ */
