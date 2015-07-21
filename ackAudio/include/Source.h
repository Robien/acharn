/*
 * Source.h
 *
 *  Created on: 1 oct. 2010
 *      Author: genesis
 */

#ifndef SOURCE_H_
#define SOURCE_H_

#include <AL/al.h>
#include <AL/alc.h>
#include "Buffer.h"
#include <iostream>
#include <irrlicht.h>
#include "PointeurIntelligent.h"
#include "Referenced.h"
#include <vector>

class Source : public Referenced
{
public:

	////////// Constructeurs/Destructeur //////////

	// constructeur de base : crée un objet Source vide
	Source();

	// constructeur simple : crée un objet Source et un objet
	// Buffer correspondant au type de son passé en paramètre,
	// et qui l'attache à la source
	Source(Buffer::typeSon son);

	// constructeur complexe : crée un objet Source et un objet
	// Buffer correspondant au type de son passé en paramètre,
	// attache le buffer à la source, puis la positionne aux
	// coordonnées passées en paramètre et définit son mode
	// de lecture
	Source(Buffer::typeSon son, float x, float y, float z, bool loop = false);

	// constructeur complexe : crée un objet Source et un objet
	// Buffer correspondant au type de son passé en paramètre,
	// attache le buffer à la source, puis la positionne aux
	// coordonnées Irrlicht passées en paramètre et définit
	// son mode de lecture
	Source(Buffer::typeSon son, irr::core::vector3df coordonnees, bool loop = false);

	// destructeur, détache tous les buffers attachés à la source,
	// puis détruit la source
	virtual ~Source();

	////////// Création de sources //////////

	// crée une source
	void creerSource();

	// crée une source de coordonnées x, y, z avec un mode de lecture
	void creerSource(float x, float y, float z, bool loop = false);

	// crée une source de coordonnées IrrLicht x, y, z avec un mode de lecture
	inline void creerSource(irr::core::vector3df coordonnees, bool loop = false)
	{
		this->creerSource(coordonnees.X, coordonnees.Y, coordonnees.Z, loop);
	}

	////////// Ajout/suppression de buffers //////////

	// ajoute le buffer passé en paramètre à la source
	void attachBufferToSource(ALuint buffer);
	// attache les buffers de l'objet Buffer passé en paramètre à la source
	void attachBuffersToSource(Buffer* buffer);
/*
	// détache le buffer passé en paramètre de la source
	void detachBufferFromSource(ALuint buffer);
	// détache les buffers de l'objet Buffer passé en paramètre de la source
	void detachBuffersFromSource(Buffer* buffer);
	// détache TOUS les buffers attachés à la source
	void detachAllBuffersFromSource();
*/
	// supprime la source et TOUS les buffers qui lui sont attachés
	void deleteSource();

	////////// Manipulations sur les sources //////////

	// active la répétition sur la source
	void enableLoop();
	// désactive la répétition sur la source
	void disableLoop();
	// débute la lecture ou reprend la lecture de la source
	// facultatif : rembobine la source et la rejoue si elle était en cours de lecture
	void play();
	// met en pause la lecture de la source
	void pause();
	// termine la lecture de la source
	void stop();
	// termine la lecture de la source et la rembobine
	void rewind();

	////////// Setteurs //////////

	// modifie la vitesse de lecture de la source (range : 50.0 - 200.0)
	void setVitesseLecture (float vitesse);
	// modifie le volume de la source (range : 0 - 400)
	void setVolume (unsigned int volume);
	// modifie les coordonnées de la source
	void setCoordonnees(float x, float y, float z);

	// modifie les coordonnées IrrLicht de la source
	inline void setCoordonnees(irr::core::vector3df coordonnees)
	{
		this->setCoordonnees(coordonnees.X, coordonnees.Y, coordonnees.Z);
	}

	// modifie le mode de répétition de la source
	void setLoop (bool loop);

	////////// Getteurs //////////

	// retourne la source de l'objet
	ALuint getSource();
	// retourne un vecteur contenant les objets Buffer attachés
	// à la source
	std::vector< PointeurIntelligent<Buffer> > getBuffers();
	// retourne la taille du vecteur des objets Buffer qui sont
	// rattachés à la source
	size_t getBuffersSize();
	// retourne la vitesse de lecture de la source
	float getVitesseLecture();
	// retourne le volume de la source
	unsigned int getVolume();
	// retourne les coordonnées IrrLicht de la source
	irr::core::vector3df getCoordonnees();
	// retourne le temps de lecture de la source
	ALfloat getTemps();
	// retourne l'état de la source :
	//
	//		AL_INITIAL : état initial
    //		AL_PLAYING : en cours de lecture
	//		AL_PAUSED : en pause
	//		AL_STOPPED : stoppée
	//
	ALint getStatus();

	////////// Méthodes de test //////////

	// retourne VRAI si la source est jouée en boucle
	bool isLooping();
	// retourne VRAI si la source est positionnée au début
	bool isInitialized();
	// retourne VRAI si la source est en cours de lecture
	bool isPlaying();
	// retourne VRAI si la source a été mise en pause
	bool isPaused();
	// retourne VRAI si la source a été arrêtée
	bool isStopped();

private:
	// la source de l'objet
	ALuint _source;
	// vecteur contenant tous les objets Buffer dont les buffers sont attachés à la source
	std::vector< PointeurIntelligent<Buffer> > _buffers;

	////////// Méthodes d'ajout dans les vecteurs //////////

	// ajoute un buffer dans le vecteur de buffers
	void addBuffer(Buffer* buffer);
};

#endif /* SOURCE_H_ */
