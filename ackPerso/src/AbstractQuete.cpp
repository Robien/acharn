/*
 * AbstractQuete.cpp
 *
 *  Created on: 31 oct. 2010
 *      Author: cephise
 */

#include "AbstractQuete.h"

AbstractQuete::AbstractQuete(string n, string t, string r):
m_nom(n), m_texte(t), m_requete(r)
{
}

AbstractQuete::~AbstractQuete()
{
}

void AbstractQuete::newEvenement(string eve)
{

}
