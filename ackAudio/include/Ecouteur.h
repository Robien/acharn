/*
 * Ecouteur.h
 *
 *  Created on: 5 oct. 2010
 *      Author: genesis
 */

#ifndef ECOUTEUR_H_
#define ECOUTEUR_H_

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <irrlicht.h>
#include "Referenced.h"
#include <vector>

class Ecouteur : public Referenced
{
public:

	////////// Constructeurs/Destructeur //////////

	// constructeurs
	Ecouteur();
	Ecouteur(float x = 0.0, float y = 0.0, float z = 0.0, unsigned int volume = 100);
	Ecouteur(irr::core::vector3df coordonnees = irr::core::vector3df(0.0,0.0,0.0), unsigned int volume = 100);

	// destructeur
	virtual ~Ecouteur();

	////////// Setteurs //////////

	// modifie le volume de l'écouteur (range : 10 - 400)
	void setVolume (unsigned int volume);

	// met à jour le vecteur de vitesse du joueur
	void setVitesse(float x, float y, float z);

	// met à jour le vecteur de vitesse du joueur
	inline void setVitesse(irr::core::vector3df vitesse)
	{
		this->setVitesse(vitesse.X, vitesse.Y, vitesse.Z);
	}

	// met à jour les coordonnées sonores du joueur
	void setCoordonnees(float x, float y, float z);

	// met à jour les coordonnées sonores IrrLicht du joueur
	inline void setCoordonnees(irr::core::vector3df coordonnees)
	{
		this->setCoordonnees(coordonnees.X, coordonnees.Y, coordonnees.Z);
	}

	////////// Getteurs //////////

	// retourne le volume de l'écouteur
	unsigned int getVolume();
	// retourne le vecteur de vitesse du joueur
	irr::core::vector3df getVitesse();
	// retourne les coordonnées sonores IrrLicht du joueur
	irr::core::vector3df getCoordonnees();

private:
/*
	// les coordonnées sonores IrrLicht du joueur
	irr::core::vector3df _coordonnees;
	// le vecteur de vitesse du joueur
	irr::core::vector3df _vitesse;
	// le volume de l'écouteur
	unsigned int _volume;
*/
};

#endif /* ECOUTEUR_H_ */
