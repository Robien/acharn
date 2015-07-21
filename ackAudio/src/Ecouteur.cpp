/*
 * Ecouteur.cpp
 *
 *  Created on: 5 oct. 2010
 *      Author: genesis
 */

#include "Ecouteur.h"

// Méthodes publiques

///////////////////////////////////////////////////////////////////
//////////////////// Constructeurs/Destructeur ////////////////////
///////////////////////////////////////////////////////////////////

Ecouteur::Ecouteur()
{
	std::cerr << "Création d'un objet ECOUTEUR avec le constructeur de base" << std::endl;
	this->setCoordonnees(0.0, 0.0, 0.0);
	// this->setVitesse(0.0, 0.0, 0.0);
	this->setVolume(100);
}

Ecouteur::Ecouteur(float coordonneesX, float coordonneesY, float coordonneesZ, unsigned int volume)
{
	std::cerr << "Création d'un objet ECOUTEUR avec le constructeur coordonnees float + volume" << std::endl;
	this->setCoordonnees(coordonneesX, coordonneesY, coordonneesZ);
	// this->setVitesse(0.0, 0.0, 0.0);
	this->setVolume(100);
}

Ecouteur::Ecouteur(irr::core::vector3df coordonnees, unsigned int volume)
{
	std::cerr << "Création d'un objet ECOUTEUR avec le constructeur coordonnees Irrlicht + volume" << std::endl;
	this->setCoordonnees(coordonnees.X, coordonnees.Y, coordonnees.Z);
	// this->setVitesse(0.0, 0.0, 0.0);
	this->setVolume(100);
}

Ecouteur::~Ecouteur()
{
	std::cerr << "Destruction d'un objet ECOUTEUR" << std::endl;
}

//////////////////////////////////////////////////
//////////////////// Setteurs ////////////////////
//////////////////////////////////////////////////

void Ecouteur::setVolume (unsigned int volume)
{
/*
	if (volume <= 0)
	{
		alListeneri(AL_GAIN, 0);
	} else if (volume >= 400) {
		alListeneri(AL_GAIN, 400);
	} else {
		alListeneri(AL_GAIN, volume);
	}
*/

	alListeneri(AL_GAIN, volume);
}

void Ecouteur::setVitesse(float x, float y, float z)
{
	alListener3f(AL_VELOCITY, x, y, z);
}

void Ecouteur::setCoordonnees(float x, float y, float z)
{
	alListener3f(AL_POSITION, x, y, z);
}

//////////////////////////////////////////////////
//////////////////// Getteurs ////////////////////
//////////////////////////////////////////////////

unsigned int Ecouteur::getVolume()
{
	ALint Volume;
	alGetListeneri (AL_GAIN, &Volume);
	return Volume;
}

irr::core::vector3df Ecouteur::getVitesse()
{
	irr::core::vector3df Vitesse;
	alGetListener3f(AL_VELOCITY, &Vitesse.X, &Vitesse.Y, &Vitesse.Z);
	return Vitesse;
}

irr::core::vector3df Ecouteur::getCoordonnees()
{
	irr::core::vector3df Coordonnees;
	alGetListener3f(AL_POSITION, &Coordonnees.X, &Coordonnees.Y, &Coordonnees.Z);
	return Coordonnees;
}
