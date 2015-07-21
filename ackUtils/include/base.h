#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED
//regroupe les fonctions du programme principal
#include <iostream>
#include <list>
#include "AbstractPerso.h"
#include "PersoJoueur.h"
#include "PersoNonJoueur.h"
#include "const.h"

//-----fonction perso----//
bool vivant(std::list<AbstractPerso*>::iterator i, std::list<AbstractPerso*>::iterator iend);
void vainqueur(PersoJoueur &pj, PersoNonJoueur &pnj);
void vainqueur(PersoJoueur &pj1, PersoJoueur &pj2);
void vainqueur(PersoNonJoueur &pnj1, PersoNonJoueur &pnj2);
//float converfl(std::string txt); //converti un string en float ou int
//int converint(std::string txt);
//std::string converstr(int nb);
//std::string converstr(float nb);
#endif // BASE_H_INCLUDED
