/*
 * AbstractQuete.h
 *
 *  Created on: 31 oct. 2010
 *      Author: cephise
 */

#ifndef ABSTRACTQUETE_H_
#define ABSTRACTQUETE_H_

#include "string"

using namespace std;

class AbstractQuete
{

public:

	AbstractQuete(string n, string t, string r);
	virtual ~AbstractQuete();
	void newEvenement(string eve);

private:

	string m_nom;
	string m_texte;
	string m_requete;

};

#endif /* ABSTRACTQUETE_H_ */
