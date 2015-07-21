/*
 * Contexte.h
 *
 *  Created on: 9 oct. 2010
 *      Author: genesis
 */

#ifndef CONTEXTE_H_
#define CONTEXTE_H_

#include <AL/al.h>
#include <AL/alc.h>
#include "Ecouteur.h"
#include <iostream>
#include <irrlicht.h>
#include "PointeurIntelligent.h"
#include "Referenced.h"

////////// Méthodes de test //////////

// vérifie l'état d'erreur actuel d'OpenAL, affiche un
// message d'erreur approprié selon la fonction passée
// en paramètre (si une erreur est détectée), puis
// efface l'état d'erreur
ALenum alCheckError(std::string nomFonction = "générique", bool affichageErreur = true);
ALCenum alCheckContextError(bool affichageErreur = true);

class Contexte : public Referenced
{
public:

	////////// Constructeurs/Destructeur //////////

	Contexte(const char* DeviceName = NULL, ALCint* attributs = NULL, ALenum modele = AL_INVERSE_DISTANCE_CLAMPED);

    virtual ~Contexte();

	////////// Manipulations sur le contexte //////////

    // suspend le contexte (cependant des changements peuvent être
    // effectués sur celui-ci)
    void pauseContexte();
    // réactive le contexte et applique tous les changements
    // effectués sur celui-ci pendant qu'il était en pause
    void resumeContexte();

	////////// Setteurs //////////

    // change le périphérique audio associé au contexte
    // (ATTENTION : détruit le contexte !)
    void setDevice(const std::string DeviceName = NULL, ALCint* attributs = NULL, ALenum modele = AL_INVERSE_DISTANCE_CLAMPED);

    // change le mode d'atténuation du son d'OpenAL (se référer à
    // la documentation pour plus d'explications)
    //
    // valeurs possibles :
    //
    //		- AL_INVERSE_DISTANCE
    //		- AL_INVERSE_DISTANCE_CLAMPED (mode par défaut d'OpenAL)
    //		- AL_LINEAR_DISTANCE
    //		- AL_LINEAR_DISTANCE_CLAMPED
    //		- AL_EXPONENT_DISTANCE
    //		- AL_EXPONENT_DISTANCE_CLAMPED
    //		- AL_NONE
    //
    void setDistanceModel(ALenum modele);

	////////// Getteurs //////////

    // retourne le périphérique audio associé au contexte
    ALCdevice* getDevice();
	// retourne l'écouteur
    Ecouteur* getEcouteur();
	// retourne le modèle actuel d'atténuation du son utilisé
	// par OpenAL
    ALenum getDistanceModel();

private:
	PointeurIntelligent<Ecouteur> _ecouteur;
	ALenum _distanceModel;

	////////// Manipulations sur le contexte //////////

    // crée un contexte
    void creerContexte(const char* DeviceName = NULL, ALCint* attributs = NULL, ALenum modele = AL_INVERSE_DISTANCE_CLAMPED);
    // détruit le contexte
    // ATTENTION : détruit aussi toutes les sources !
    void detruireContexte();
};

#endif /* CONTEXTE_H_ */
