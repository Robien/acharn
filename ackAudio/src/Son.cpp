/*
 * Son.cpp
 *
 *  Created on: 7 oct. 2010
 *      Author: genesis
 */

#include "AudioManager.h"
#include "Son.h"

// Méthodes publiques

///////////////////////////////////////////////////////////////////
//////////////////// Constructeurs/Destructeur ////////////////////
///////////////////////////////////////////////////////////////////

Son::Son()
{
	std::cerr << "Création d'un objet SON avec le constructeur de base" << std::endl;
}

Son::Son(Buffer::typeSon typeSon, std::string nomSon, float x, float y, float z, bool loop, const char* DeviceName)
{
	std::cerr << "Création d'un objet SON avec le constructeur coordonnees float + typeSon + nomSon + loop + device" << std::endl;

	this->_source = new Source(typeSon, x, y, z, loop);
	// PointeurIntelligent<Buffer> buffer = new Buffer(typeSon, this->_source, x, y, z);
}

Son::Son(Buffer::typeSon typeSon, std::string nomSon, irr::core::vector3df coordonneesSource, bool loop, const char* DeviceName)
{
	std::cerr << "Création d'un objet SON avec le constructeur coordonnees Irrlicht + typeSon + nomSon + loop + device" << std::endl;

	this->_source = new Source(typeSon, coordonneesSource, loop);
	// PointeurIntelligent<Buffer> buffer = new Buffer(typeSon, this->_source, coordonneesSource);
}

Son::Son(std::string typeSon, std::string nomSon, float x, float y, float z, bool loop, const char* DeviceName)
{
	std::cerr << "Création d'un objet SON avec le constructeur coordonnees float + typeSonConverti + nomSon + loop + device" << std::endl;

	Buffer::typeSon typeSonConverti = Buffer::convertStringToTypeSon(typeSon);

	this->_source = new Source(typeSonConverti, x, y, z, loop);
	// PointeurIntelligent<Buffer> buffer = new Buffer(typeSon, this->_source, x, y, z);
}

Son::Son(std::string typeSon, std::string nomSon, irr::core::vector3df coordonneesSource, bool loop, const char* DeviceName)
{
	std::cerr << "Création d'un objet SON avec le constructeur coordonnees Irrlicht + typeSonConverti + nomSon + loop + device" << std::endl;

	Buffer::typeSon typeSonConverti = Buffer::convertStringToTypeSon(typeSon);

	this->_source = new Source(typeSonConverti, coordonneesSource, loop);
	// PointeurIntelligent<Buffer> buffer = new Buffer(typeSon, this->_source, coordonneesSource);
}

Son::~Son()
{
	std::cerr << "Destruction d'un objet SON" << std::endl;
}

void Son::play()
{
	this->_source->play();
}
void Son::pause()
{
	this->_source->pause();
}

void Son::stop()
{
	this->_source->stop();
}

void Son::rewind()
{
	this->_source->rewind();
}

//////////////////////////////////////////////////
//////////////////// Setteurs ////////////////////
//////////////////////////////////////////////////

void Son::setVolumeSource (unsigned int volume)
{
	this->_source->setVolume(volume);
}

void Son::setCoordonneesSource(float x, float y, float z)
{
	this->_source->setCoordonnees(x, y, z);
}

void Son::setLoopSource(bool loop)
{
	this->_source->setLoop(loop);
}

//////////////////////////////////////////////////
//////////////////// Getteurs ////////////////////
//////////////////////////////////////////////////

Source* Son::getSource()
{
	return this->_source;
}

unsigned int Son::getVolumeSource()
{
	return this->_source->getVolume();
}

irr::core::vector3df Son::getCoordonneesSource()
{
	return this->_source->getCoordonnees();
}
