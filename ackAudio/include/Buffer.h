/*
 * Buffer.h
 *
 *  Created on: 29 sept. 2010
 *      Author: genesis
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <irrlicht.h>
#include "PointeurIntelligent.h"
#include "Referenced.h"
#include <vector>

class Source;

class Buffer : public Referenced
{
public:

	// type énuméré avec tous les différents types de son utilisables
	typedef enum {
		ARBRE,
		CASCADE,
		CHUTE,
		DIALOGUE,
		EAU,
		EPEE,
		HACHE,
		MARTEAU,
		MUSIQUE_COMBAT,
		MUSIQUE_EXPLORATION,
		NAGE,
		OISEAU,
		PAS,
		PORTE,
		SAUT,
		TA_GUEULE,
		TONNERRE,
		VENT
	} typeSon;

	////////// Constructeurs/Destructeur //////////

	// constructeur de base, qui crée un objet Buffer vide
	Buffer();

	// constructeur simple, qui crée un objet Buffer avec les
	// buffers correspondant au type de son passé en paramètre
	Buffer(Buffer::typeSon son);

	// constructeur avancé, qui crée un objet Buffer avec les
	// buffers correspondant au type de son passé en paramètre
	// et les attache à l'objet Source passé en paramètre
	Buffer(Buffer::typeSon son, Source* source);

	// constructeur complexe, qui crée un objet Buffer avec les
	// buffers correspondant au type de son passé en paramètre,
	// les attache à l'objet Source passé en paramètre, et
	// définit les coordonnées de la source
	Buffer(Buffer::typeSon son, Source* source, float x, float y, float z);

	// constructeur complexe, qui crée un objet Buffer avec les
	// buffers correspondant au type de son passé en paramètre,
	// les attache à l'objet Source passé en paramètre, et
	// définit les coordonnées Irrlicht de la source
	Buffer(Buffer::typeSon son, Source* source, irr::core::vector3df coordonnees);

	// destructeur, détache tous les buffers des sources
	// auxquels ils sont attachés, puis les détruit
	virtual ~Buffer();

	////////// Création des buffers //////////

	// crée un buffer à partir du fichier passé en paramètre,
	// au cas où l'on voudrait jouer d'autres sons que ceux
	// de base, et attache ce buffer à l'objet Source passé
	// en paramètre
	// retourne l'identifiant du buffer créé, ou 0 en cas
	// d'erreur
	ALuint creerBufferFromFile(const std::string Filename, Source* source);

	// crée un ou plusieurs buffers prêts à l'emploi, selon
	// le type de son passé en paramètre
	// retourne un vecteur contenant les buffers créés
	std::vector<ALuint> creerBuffer(Buffer::typeSon son);

	// crée un ou plusieurs buffers prêts à l'emploi, selon
	// le type de son passé en paramètre et les attache à
	// l'objet Source passé en paramètre
	// retourne un vecteur contenant les buffers créés
	std::vector<ALuint> creerBuffer(Buffer::typeSon son, Source* source);

	// crée un ou plusieurs buffers prêts à l'emploi, selon
	// le type de son passé en paramètre, les attache à
	// l'objet Source passé en paramètre et définit les
	// coordonnées de la source aux coordonnées passées
	// en paramètre
	// retourne un vecteur contenant les buffers créés
	std::vector<ALuint> creerBuffer(Buffer::typeSon son, Source* source, float x, float y, float z);

	// crée un ou plusieurs buffers prêts à l'emploi, selon
	// le type de son passé en paramètre, les attache à
	// l'objet Source passé en paramètre et définit les
	// coordonnées Irrlicht de la source aux coordonnées
	// Irrlicht passées en paramètre
	// retourne un vecteur contenant les buffers créés
	inline std::vector<ALuint> creerBuffer(Buffer::typeSon son, Source* source, irr::core::vector3df coordonnees)
	{
		return this->creerBuffer(son, source, coordonnees.X, coordonnees.Y, coordonnees.Z);
	}

	////////// Ajout/suppression de buffers //////////

	// ajoute le buffer passé en paramètre à l'objet Source
	// passé en paramètre
	void attachBufferToSource(ALuint buffer, Source* source);

	// ajoute les buffers de l'objet Buffer à l'objet Source
	// passé en paramètre
	void attachBuffersToSource(Source* source);

	// détache un buffer de l'objet Source passé en paramètre
	void detachBufferFromSource(ALuint buffer, Source* source);

	// détache les buffers de l'objet Buffer de l'objet Source
	// passé en paramètre
	void detachBuffersFromSource(Source* source);

	// détache les buffers de l'objet Buffer de tous les objets
	// Source auxquels ils sont attachés
	void detachBuffersFromAllSources();

	////////// Méthodes de conversion //////////

	// convertit le type de son passé en paramètre en une chaîne
	static std::string convertTypeSonToString(Buffer::typeSon typeSon);

	// convertit la chaîne passée en paramètre en un type de son
	static Buffer::typeSon convertStringToTypeSon(std::string typeSon);

	////////// Getteurs //////////

	// retourne le type de son des buffers de l'objet Buffer
	Buffer::typeSon getTypeSon();

	// retourne le vecteur des objets Source auxquels sont
	// attachés les buffers de l'objet Buffer
	std::vector< PointeurIntelligent<Source> > getSources();

	// retourne la taille du vecteur des objets Source auxquels
	// sont attachés les buffers de l'objet Buffer
	size_t getSourcesSize();

	// utilisé lors de la création des buffers pour les mettre
	// dans le vecteur de buffers
	// ALuint getBuffer();

	// retourne le vecteur des buffers de l'objet Buffer
	std::vector<ALuint> getBuffers();

	// retourne un pointeur sur le vecteur de buffers
	ALuint* getBuffersPointer();

	// retourne la taille du vecteur de buffers
	size_t getBuffersSize();

    // utilisé lors de la création des buffers pour savoir à
	// partir de quels fichiers on doit créer des buffers
	std::vector<std::string> getFichiers();

private:

	// le type de son
	Buffer::typeSon _typeSon;

    // vecteur contenant tous les objets Source auxquels les
	// buffers créés sont attachés
	std::vector< PointeurIntelligent<Source> > _sources;

	// vecteur contenant tous les buffers créés
	std::vector<ALuint> _buffers;

	// vecteur contenant les fichiers à partir desquels on doit
	// créer des buffers
	std::vector<std::string> _fichiers;

	//////////////////////////////////////////////////
	//////////////////// Setteurs ////////////////////
	//////////////////////////////////////////////////

	// modifie le type de son
	void setTypeSon(Buffer::typeSon son);

	////////////////////////////////////////////////////////////////////////////
	//////////////////// Méthodes d'ajout dans les vecteurs ////////////////////
	////////////////////////////////////////////////////////////////////////////

    // ajoute un buffer dans le vecteur de buffers
	void addBuffer(ALuint buffer);

    // ajoute une source dans le vecteur de sources
	void addSource(Source* source);

    // ajoute un fichier dans le vecteur de fichiers
	void addFichier(std::string Filename);
};

#endif /* BUFFER_H_ */
