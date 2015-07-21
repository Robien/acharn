//============================================================================
// Name        : SousAttaque.cpp
// Author      : céphise
// Version     :
// Copyright   : Your copyright notice
// Description : Sous Attaque
//============================================================================

#include <iostream>
#include "SousAttaque.h"
#include "PersoJoueur.h"

using namespace std;

SousAttaque::SousAttaque()
{
    attaquant = NULL;
    attribut.nom = "attaque basique";
    attribut.degat = 0;
    attribut.tps = 0;
    attribut.type = 0;
    attribut.pas = 1;
    attribut.affect = "vie";
    attribut.cout = 0;
    attribut.affectcout = "radiation";
    attribut.cooldown = 0;
    attribut.reverse = 0;
    attribut.incantation = 0;
    attribut.portee = 1;
    attribut.crit = 0;
    if (attribut.pas > 1)
    {
        attribut.parcoup = (attribut.tps / (attribut.pas - 1));
    }
    else
    {
        attribut.parcoup = 0;
    }
}

SousAttaque::SousAttaque(std::string nom, float dgt, float tps, int type, float ct, std::string affect, std::string affectct, int pas, float calld)
{
    attaquant = NULL;
    attribut.degat = dgt;
    attribut.tps = tps;
    attribut.type = type;
    attribut.pas = pas;
    attribut.nom = nom;
    attribut.affect = affect;
    attribut.cooldown = calld;
    attribut.cout = 0;
    attribut.affectcout = "radiation";
    attribut.reverse = 0;
    attribut.incantation = 0;
    attribut.crit = 0;
    if (attribut.type >= 10)
    {
        attribut.portee = 10;
    }
    else
    {
        attribut.portee = 1;
    }
    if (attribut.pas > 1)
    {
        attribut.parcoup = (attribut.tps / (attribut.pas - 1));
    }
    else
    {
        attribut.parcoup = 0;
    }
}

SousAttaque::SousAttaque(t_attribut attr)
{
    attaquant = NULL;
    attribut.degat = attr.degat;
    attribut.tps = attr.tps;
    attribut.type = attr.type;
    attribut.pas = attr.pas;
    attribut.nom = attr.nom;
    attribut.affect = attr.affect;
    attribut.cout = attr.cout;
    attribut.affectcout = attr.affectcout;
    attribut.cooldown = attr.cooldown;
    attribut.reverse = attr.reverse;
    attribut.incantation = attr.incantation;
    attribut.portee = attr.portee;
    attribut.crit = attr.crit;
    if (attribut.pas > 1)
    {
        attribut.parcoup = (attribut.tps / (attribut.pas - 1));
    }
    else
    {
        attribut.parcoup = 0;
    }
}

//-----
void SousAttaque::afficheInfos()
{
    cout << getNom() << " : degats(" << getDegat() << "*" << getPas() << "), duree du sorts(" << getTps() << "), type(" << getType() << ") cout(" << getCout() << getAffectCout() << ")" << endl;

}

/// ----getter-----  ///	
std::string SousAttaque::getNom()
{
    return attribut.nom;
}

std::string SousAttaque::getAffect()
{
    return attribut.affect;
}

std::string SousAttaque::getAffectCout()
{
    return attribut.affectcout;
}

float SousAttaque::getDegat()
{
    return attribut.degat * attribut.crit;
}

float SousAttaque::getDegatBrut()
{
    return attribut.degat;
}

float SousAttaque::getTps()
{
    return attribut.tps;
}

int SousAttaque::getType()
{
    return attribut.type;
}

int SousAttaque::getPas()
{
    return attribut.pas;
}

float SousAttaque::getParCoup()
{
    return attribut.parcoup;
}

float SousAttaque::getCout()
{
    return attribut.cout;
}

float SousAttaque::getCoolDown()
{
    return attribut.cooldown;
}

float SousAttaque::getReverse()
{
    return attribut.reverse;
}

t_attribut SousAttaque::getAttribut()
{
    return attribut;
}

float SousAttaque::getIncantation()
{
    return attribut.incantation;
}

float SousAttaque::getPortee()
{
    return attribut.portee;
}

/// ----setter-----  ///	
void SousAttaque::addTps(float ctime)
{
    attribut.tps += ctime;
}

void SousAttaque::setPas(int p)
{
    attribut.pas = p;
}

void SousAttaque::supPas()
{
    attribut.pas--;
}

PersoJoueur* SousAttaque::getAttaquant()
{
    return attaquant;
}

void SousAttaque::setAttaquant(PersoJoueur* noma)
{
    attaquant = noma;
}

void SousAttaque::setAttribut(t_attribut attr)
{
    attribut.degat = attr.degat;
    attribut.tps = attr.tps;
    attribut.type = attr.type;
    attribut.pas = attr.pas;
    attribut.nom = attr.nom;
    attribut.affect = attr.affect;
    attribut.cout = attr.cout;
    attribut.affectcout = attr.affectcout;
    attribut.cooldown = attr.cooldown;
    attribut.reverse = attr.reverse;
    attribut.portee = attr.portee;
    attribut.crit = attr.crit;
    if (attribut.pas > 1)
    {
        attribut.parcoup = (float) (attribut.tps / (float) (attribut.pas - 1));
    }
    else
    {
        attribut.parcoup = 0;
    }
}
