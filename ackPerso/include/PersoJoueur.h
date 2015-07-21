/*
 * PersoJoueur.h
 *
 *  Created on:
 *      Author: cephise
 */

#ifndef PERSOJOUEUR_H_INCLUDED
#define PERSOJOUEUR_H_INCLUDED

#include <cassert>
#include <iostream>
#include "AbstractPerso.h"

class PersoJoueur: public AbstractPerso
{
public:
	PersoJoueur(IrrlichtDevice* device, int init = 0);
	PersoJoueur(IrrlichtDevice* device, string pseudo, int init = 0);
	PersoJoueur(string infojoueur, IrrlichtDevice* device, int init = 0);
	string saveCara();
	void setInfo(string infojoueur, int init);
	virtual ~PersoJoueur();
	float getXp();
	float xpprochainlvl();
	float xplvlCourent();
	virtual bool gainxp(float xp);

    void mortALInstant();

private:

	string recupxp(string info);

private:

	float m_pointexp; //point d'experience du personnage
	// int m_dexterite; //capacité aux travaux manuel
	//int m_statcomm; //stat communautaire: nombre de point de societe et aide communautaire
	//cree class AbstractStock, Recompense et SacADos
	// std::string m_sacdos; //objet stocké par le personnage


};

#endif // PERSOJOUEUR_H_INCLUDED
