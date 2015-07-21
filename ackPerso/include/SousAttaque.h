/*
 * Attaque.h
 *
 *  Created on: 17 mars 2010
 *      Author: Cephise
 */

#ifndef SOUSATTAQUE_H_
#define SOUSATTAQUE_H_

#include <iostream>
#include <list>
#include "../include/Referenced.h"
#include "string"
#include "../../ackUtils/include/PointeurIntelligent.h"

class PersoJoueur;

using namespace std;

struct t_attribut
{
    t_attribut()
    {
        nom = "";
        affect = "";
        affectcout = "";
    }
    ~t_attribut()
    {

    }
	std::string nom;
	std::string affect;
	float degat;
	float tps;
	int type;
	int pas;
	float parcoup;
	float cout;
	float cooldown;
	float reverse;
	float incantation;
	float portee;
	float crit;
	std::string affectcout;
};

class SousAttaque
{

public:
	SousAttaque();
	SousAttaque(std::string nom, float dgt = 0, float tps = 0, int type = 0, float ct = 0, std::string affect = "vie", std::string affectct = "radiation", int pas = 1, float calld = 0);
	SousAttaque(t_attribut attr);
	void afficheInfos();

	//getter
	std::string getNom();
	std::string getAffect();
	std::string getAffectCout();
	float getDegat();
	float getDegatBrut();
	float getTps();
	int getType();
	float getParCoup();
	int getPas();
	float getCout();
	float getCoolDown();
	float getReverse();
	float getIncantation();
	float getPortee();
	PersoJoueur* getAttaquant();
	t_attribut getAttribut();

	//setter
	void setAttribut(t_attribut attr);
	void addTps(float ctime);
	void setPas(int p);
	void supPas();
	void setAttaquant(PersoJoueur* noma);

private:

	t_attribut attribut;
	PersoJoueur* attaquant;

};

#endif /* SOUSATTAQUE_H_ */
