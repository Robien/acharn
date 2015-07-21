/*
 * Son.h
 *
 *  Created on: 6 oct. 2010
 *      Author: genesis
 */

#ifndef SON_H_
#define SON_H_

#include <AL/al.h>
#include <AL/alc.h>
#include "Buffer.h"
#include <irrlicht.h>
#include "PointeurIntelligent.h"
#include "Source.h"

class Son : public Referenced
{
public:

	////////// Constructeurs/Destructeur //////////

	Son();
	Son(Buffer::typeSon typeSon, std::string nomSon, float x, float y, float z, bool loop = false, const char* DeviceName = NULL);
	Son(Buffer::typeSon typeSon, std::string nomSon, irr::core::vector3df coordonneesSource, bool loop = false, const char* DeviceName = NULL);
    Son(std::string typeSon, std::string nomSon, float x, float y, float z, bool loop = false, const char* DeviceName = NULL);
    Son(std::string typeSon, std::string nomSon, irr::core::vector3df coordonneesSource, bool loop = false, const char* DeviceName = NULL);

    virtual ~Son();

    void play();
    void pause();
	void stop();
	void rewind();

	////////// Setteurs //////////

	// modifie le volume de la source (range : 10 - 400)
	void setVolumeSource (unsigned int volume);

	// modifie les coordonnées de la source
    void setCoordonneesSource(float x, float y, float z);

	// modifie les coordonnées IrrLicht de la source
    inline void setCoordonneesSource(irr::core::vector3df coordonneesSource)
    {
    	this->setCoordonneesSource(coordonneesSource.X, coordonneesSource.Y, coordonneesSource.Z);
    }

	// modifie le mode de lecture de la source
    void setLoopSource(bool loop);

	////////// Getteurs //////////

    // retourne la source
    Source* getSource();
	// retourne le volume de la source
	unsigned int getVolumeSource();
	// retourne les coordonnées IrrLicht de la source
	irr::core::vector3df getCoordonneesSource();

private:
	PointeurIntelligent<Source> _source;
};

#endif /* SON_H_ */
