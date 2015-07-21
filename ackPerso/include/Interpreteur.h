/*
 * Interpreteur.h
 *
 *  Created on: 12 juin 2010
 *      Author: cephise
 */

#ifndef INTERPRETEUR_H_
#define INTERPRETEUR_H_

#include "SousAttaque.h"
#include "Symbole.h"
#include "LecteurSymbole.h"
#include <iostream>
#include <string>
#include <map>
#include "Caracteristique.h"
#include "PointeurIntelligent.h"

using namespace std;

class Interpreteur: public Referenced
{

public:

    Interpreteur(Caracteristique* src, Random* randsrc, Caracteristique* cib, const string atq, bool sousatt = false);
    Interpreteur(Caracteristique* src, Random* randsrc, const string atq, bool sousatt = false);
    SousAttaque* analyse();
    bool analyseIncantation(float &incantation, int &type, float &portee);

    void setCible(Caracteristique* cib);
    SousAttaque* getAttaque();
    std::string getAttaqueString();
    bool getVerification();
    SousAttaque* getReverse();
    bool isReverse();

protected:

    float expression();
    float terme();
    std::string getChaine();
    bool testerSymCour(string ch); // si symbole courant != ch
    bool sauterSymCour(string ch); // si symbole courant == ch
    void reinitialiser();

private:

    LecteurSymbole ls; // le lecteur de symboles utilisé pour analyser le fichier
    string saveAttaque;
    std::string sAttaque;
    SousAttaque* attaque;
    //PointeurIntelligent<SousAttaque> attaque;
    Caracteristique* source;
    //	PointeurIntelligent<Caracteristique> source;
    Caracteristique* cible;
    //PointeurIntelligent<Caracteristique> cible;
    //Random* randomSource;
    PointeurIntelligent<Random> randomSource;
    bool justIncant;
    bool SsAtt;
    bool m_verification;
    bool reversible;
    bool critique;
    t_attribut attri;
};

#endif /* INTERPRETEUR_H_ */
