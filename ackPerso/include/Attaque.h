/*
 * Attaque.h
 *
 *  Created on: 17 mars 2010
 *      Author: cephise
 */

#ifndef ATTAQUE_H_
#define ATTAQUE_H_

#include <iostream>
#include <vector>
#include "SousAttaque.h"

using namespace std;

class Attaque: public SousAttaque
{

public:
	Attaque();
	Attaque(std::string nom, float dgt = 0, float tps = 0, int type = 0, float ct = 0, std::string affect = "vie", std::string affectct = "radiation", int pas = 1, float calld = 0);
	Attaque(t_attribut attr);
	void ajouterEffet(SousAttaque& effet);
	void afficheInfos();

	//getter
	std::vector<SousAttaque>* getEffet();

	//setter
	void addTps(float ctime);

private:
	std::vector<SousAttaque> l_sousEffet;

};

#endif /* ATTAQUE_H_ */
