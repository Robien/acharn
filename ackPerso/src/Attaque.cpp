//============================================================================
// Name        : Attaque.cpp
// Author      : cephise
// Version     :
// Copyright   : Your copyright notice
// Description : Attaque
//============================================================================

#include <iostream>
#include "Attaque.h"
using namespace std;

Attaque::Attaque() :
	SousAttaque()
{
}

Attaque::Attaque(std::string nom, float dgt, float tps, int type, float ct, std::string affect, std::string affectct, int pas, float calld) :
	SousAttaque(nom, dgt, tps, type, ct, affect, affectct, pas, calld)
{
}

Attaque::Attaque(t_attribut attr) :
	SousAttaque(attr)
{
}

//------
void Attaque::ajouterEffet(SousAttaque& effet)
{
	l_sousEffet.push_back(effet);
}

//-----
void Attaque::afficheInfos()
{
	SousAttaque::afficheInfos();
	if (!l_sousEffet.empty())
	{
		vector<SousAttaque>::iterator it;
		cout << "\tAutre effet(s):" << endl;
		for (it = l_sousEffet.begin(); it != l_sousEffet.end(); it++)
		{
			cout << "\t-";
			it->afficheInfos();
		}
	}

}

/// ----getter-----  ///	
std::vector<SousAttaque>* Attaque::getEffet()
{
	return &l_sousEffet;
}

/// ----setter-----  ///	
void Attaque::addTps(float ctime)
{
	vector<SousAttaque>::iterator it;
	SousAttaque::addTps(ctime);
	for (it = l_sousEffet.begin(); it != l_sousEffet.end(); it++)
	{
		it->addTps(ctime);
	}
}

