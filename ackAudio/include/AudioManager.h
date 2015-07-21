/*
 * AudioManager.h
 *
 *  Created on: 26 sept. 2010
 *      Author: david
 */

#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include "Buffer.h"
#include "Contexte.h"
#include <iostream>
#include <irrlicht.h>
#include <map>
#include "PointeurIntelligent.h"
#include "Singleton.h"
#include "Son.h"

class AudioManager: public Singleton<AudioManager>
{
public:

    AudioManager();
    virtual ~AudioManager();

    Son* getSon (std::string nomSon);

    void setCoordonneesEcouteur(float x, float y, float z);

    inline void setCoordonneesEcouteur(irr::core::vector3df coordonnees)
    {
    	setCoordonneesEcouteur(coordonnees.X, coordonnees.Y, coordonnees.Z);
    }

    void setCoordonneesSon(std::string nomSon, float x, float y, float z);

    inline void setCoordonneesSon(std::string nomSon, irr::core::vector3df coordonnees)
    {
    	setCoordonneesSon(nomSon, coordonnees.X, coordonnees.Y, coordonnees.Z);
    }

    void addSound(std::string nomSon, Son* son);
    void deleteSound(std::string nomSon);

    void play(Buffer::typeSon typeSon, std::string nomSon, float x, float y, float z, bool loop = false, const char* DeviceName = NULL);

    inline void play(Buffer::typeSon typeSon, std::string nomSon, irr::core::vector3df coordonnees, bool loop = false, const char* DeviceName = NULL )
    {
    	this->play(typeSon, nomSon, coordonnees.X, coordonnees.Y, coordonnees.Z, loop, DeviceName);
    }

    void play(std::string typeSon, std::string nomSon, float x, float y, float z, bool loop = false, const char* DeviceName = NULL );

    inline void play(std::string typeSon, std::string nomSon, irr::core::vector3df coordonnees, bool loop = false, const char* DeviceName = NULL )
    {
    	this->play(typeSon, nomSon, coordonnees.X, coordonnees.Y, coordonnees.Z, loop, DeviceName);
    }

    void pause(std::string nomSon);
    void stop(std::string nomSon);
    void rewind(std::string nomSon);

    void drop();

private:

    PointeurIntelligent<Contexte> _contexte;
    std::map< std::string, PointeurIntelligent<Son> > _dicoSons;
};

#endif /* AUDIOMANAGER_H_ */
