/*
 * ObjetConsommable.h
 *
 *  Created on: 19 sept. 2010
 *      Author: cephise
 */

#ifndef OBJETCONSOMMABLE_H_
#define OBJETCONSOMMABLE_H_

#include "string"
#include "AbstractObjSimple.h"

using namespace std;
class ObjetConsommable: public AbstractObjSimple
{
public:
	ObjetConsommable();
	ObjetConsommable(string infoObjet);
	virtual ~ObjetConsommable();

	std::string toSave();

private:
	string m_effet;
};

#endif /* OBJETCONSOMMABLE_H_ */
