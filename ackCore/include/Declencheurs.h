/*
 * Declancheurs.h
 *
 *  Created on: 7 sept. 2010
 *      Author: romain & céphise
 */

#ifndef DECLANCHEURS_H_
#define DECLANCHEURS_H_

#include "Referenced.h"
#include <irrlicht.h>
#include "../include/PointeurIntelligent.h"
#include "Tache.h"
#include "Perso.h"
#include "../include/TacheSetAnime.h"
#include "../include/TacheSetAttaque.h"
#include "../include/TacheTalkPnj.h"

class Declencheurs: public Referenced
{

public:

	typedef enum
	{
		LIQUIDE, ACTIONNEUR, SURFACE_MOLLE, SURFACE_GLISSANTE, SURFACE_COLLANTE, SURFACE_FLUIDE, ZONE, PIEGE, PNJ_QUETE, PNJ_VENDEUR, INCONNU
	} typeDeclancheur;

public:

	Declencheurs(irr::scene::ISceneNode* nodeDeclancheur, typeDeclancheur type);
	Declencheurs(irr::scene::ISceneNode* nodeDeclancheur,std::string typeDeclenche);
	Declencheurs(irr::scene::ISceneNode* nodeDeclancheur, std::string name, int etat);
	virtual ~Declencheurs();
	void setJoueur(Perso* joueur);
	bool test(bool& nothing);
	void execute();
	bool isFace();
	bool isCenter();
	bool isIn();
	bool isUpon();
	void stop();
	Tache* getTache();
	Tache* getTacheEtat();
	bool isActionneurEtat();


private:

	irr::scene::ISceneNode* _nodeDeclancheur;
	typeDeclancheur _type;
	PointeurIntelligent<Perso> _joueur;
	PointeurIntelligent<Tache> _aFaire;
    PointeurIntelligent<Tache> _aFaireEtat;
	bool lastState;
	bool _isActionneurEtat;
	std::string name;
	int etat;

};

#endif /* DECLANCHEURS_H_ */
