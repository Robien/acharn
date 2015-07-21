/*
 * LecteurCaractere.cpp
 *
 *  Created on: 12 juin 2010
 *      Author: C. Louison
 */

/*! \file LecteurCaractere.cc
 \brief L'implementation de la classe LecteurCaractere
 \author C. Louison
 */
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "LecteurCaractere.h"

////////////////////////////////////////////////////////////////////////////////
LecteurCaractere::LecteurCaractere(string at) :
	f(at)
{
	pos = 0;
	carCour = f[pos];
}

////////////////////////////////////////////////////////////////////////////////
void LecteurCaractere::suivant()
{
	if (f[pos] == '\0')
	{
		carCour = '\0';

	}
	else
	{
		pos++;
		carCour = f[pos];
	}
}
