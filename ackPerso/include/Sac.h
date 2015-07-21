/*
 * Sac.h
 *
 *  Created on: fort longtemps
 *      Author: céphise
 */
#ifndef DEF_SAC
#define DEF_SAC

#include <iostream>
#include "AbstractObjet.h"
#include <vector>
#include "PointeurIntelligent.h"

class Sac
{

public:

	Sac(unsigned taille=20);

	void ajouter(AbstractObjet* equip);
	AbstractObjet* enlever(unsigned int posi);
	inline unsigned int GetTailleMax() {return tailleMax; }
	 unsigned int GetTaille();
	 string enChaine();

private:

	//std::vector<AbstractObjet*> l_Sac;
	std::vector<PointeurIntelligent<AbstractObjet> > l_Sac;
	unsigned int tailleMax;

};

#endif
