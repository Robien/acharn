/*
 * CallbackIncantation.h
 *
 * Callback signalant le debut d'une incantation
 * A la fin de celle ci il faut appeler endOfIncantation
 * de AbstractPerso pour affecter réelement l'attaque aux cibles
 *
 *  Created on: 6 oct. 2010
 *      Author: céphise
 */

#ifndef CALLBACKINCANTATION_H_
#define CALLBACKINCANTATION_H_

#include "../include/Referenced.h"

using namespace std;

class CallbackIncantation: public Referenced
{

public:

	CallbackIncantation(){}
	virtual void incantation(float temps, int type, float portee){}
	virtual ~CallbackIncantation(){}

};

#endif /* CALLBACKINCANTATION_H_ */
