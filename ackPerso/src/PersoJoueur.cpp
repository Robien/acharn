/*
 * PersoJoueur.cpp
 *
 *  Created on:
 *      Author: cephise
 */

#include "PersoJoueur.h"
#include <string>
#include "../include/PersoJoueur.h"

using namespace std;

PersoJoueur::PersoJoueur(IrrlichtDevice* device, int init) :
    AbstractPerso(device, init)
{
    m_pointexp = 0;
}

PersoJoueur::PersoJoueur(IrrlichtDevice* device, string pseudo, int init) :
    AbstractPerso(device, pseudo, init)
{
    m_pointexp = 0;
}

PersoJoueur::PersoJoueur(string infojoueur, IrrlichtDevice* device, int init) :
    AbstractPerso(recupxp(infojoueur), device, init)
{
}

PersoJoueur::~PersoJoueur()
{
}

string PersoJoueur::recupxp(string info)//methode spécial constructeur
{
    string xp = "";
    unsigned int i = 0;
    while (i < info.size() && info[i] != ',')
    {
        xp += info[i];
        i++;
    }
    info.erase(0, i + 1);
    m_pointexp = converfl(xp);
    return info;
}

///retourne le nombre xp pour le prochain niveau
float PersoJoueur::xpprochainlvl()
{
    int lvl = getNiveau();
    float nbxp = (40.0 * (float) (lvl * lvl) + 360.0 * (float) lvl) / 100.0;
    nbxp *= 100.0;//réglage pour pas que céphise passe pour un con, mais bon vu la gueule du calcul, c'est trop tard
    return nbxp;
}
///retourne le nombre xp pour le prochain niveau
float PersoJoueur::xplvlCourent()
{
    int lvl = getNiveau() - 1;
    float nbxp = (40.0 * (float) (lvl) + 360.0) / 100.0;
    nbxp *= (float) lvl;
    nbxp *= 100.0;//réglage pour pas que céphise passe pour un con, mais bon vu la gueule du calcul, c'est trop tard
    return nbxp;
}

float PersoJoueur::getXp()
{
    return m_pointexp;
}

//ajoute les xp gagné (paramètre) a ceux du perso, retourne true si lvl up
bool PersoJoueur::gainxp(float xp)
{
    bool lvlup = false;
    m_pointexp += xp;
    while (xpprochainlvl() <= m_pointexp)
    {
        addNiveau();
        lvlup = true;
    }
    return lvlup;
}

string PersoJoueur::saveCara()
{
    string retour = converstr(m_pointexp) + ","+ AbstractPerso::saveCara();
    return retour;
}

void PersoJoueur::setInfo(string infojoueur, int init)
{
    AbstractPerso::setInfo(recupxp(infojoueur), init);
}

void PersoJoueur::mortALInstant()
{
    std::cout << "PERSOJOUEUR" << std::endl;
    PersoJoueur* tueur;
    if ((tueur = getLastAttaquant()) != NULL)
    {
        getLastAttaquant()->gainxp(donnexp(*this));
    }
}
