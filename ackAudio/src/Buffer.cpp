/*
 * Buffer.cpp
 *
 *  Created on: 29 sept. 2010
 *      Author: genesis
 */

#include "Buffer.h"
#include "Contexte.h"
#include "hasard.h"
#include "SequenceAleatoire.h"
#include <sndfile.h>
#include "Source.h"

// Méthodes publiques

///////////////////////////////////////////////////////////////////
//////////////////// Constructeurs/Destructeur ////////////////////
///////////////////////////////////////////////////////////////////

Buffer::Buffer()
{
	std::cerr << "Création d'un objet BUFFER avec le constructeur de base" << std::endl;
	this->_sources.clear();
	this->_buffers.clear();
	this->_fichiers.clear();
}

Buffer::Buffer(Buffer::typeSon son)
{
	std::cerr << "Création d'un objet BUFFER avec le constructeur typeSon" << std::endl;
	this->setTypeSon(son);
	this->_sources.clear();
	this->_buffers = this->creerBuffer(son);
	this->_fichiers.clear();
}

Buffer::Buffer(Buffer::typeSon son, Source* source)
{
	std::cerr << "Création d'un objet BUFFER avec le constructeur typeSon + source" << std::endl;
	this->setTypeSon(son);
	this->_sources.clear();
	this->_buffers = this->creerBuffer(son, source);
	this->_fichiers.clear();
}

Buffer::Buffer(Buffer::typeSon son, Source* source, float x, float y, float z)
{
	std::cerr << "Création d'un objet BUFFER avec le constructeur typeSon + source + coordonneesSource" << std::endl;
	this->setTypeSon(son);
	this->_sources.clear();
	this->_buffers = this->creerBuffer(son, source, x, y, z);
	this->_fichiers.clear();
}

Buffer::Buffer(Buffer::typeSon son, Source* source, irr::core::vector3df coordonnees)
{
	std::cerr << "Création d'un objet BUFFER avec le constructeur typeSon + source + coordonneesSource Irrlicht" << std::endl;
	this->setTypeSon(son);
	this->_sources.clear();
	this->_buffers = this->creerBuffer(son, source, coordonnees.X, coordonnees.Y, coordonnees.Z);
	this->_fichiers.clear();}

Buffer::~Buffer()
{
	std::cerr << "Destruction d'un objet BUFFER" << std::endl;

	for (std::size_t i=0; i < this->_buffers.size(); i++)
	{
		alGetError();
		alDeleteBuffers(1, &this->_buffers[i]);

		ALenum error = alGetError();

		if (error == AL_NO_ERROR)
		{
			std::cerr << "BUFFERS SUPPRIMES..." << std::endl;
		} else if (error == AL_INVALID_OPERATION) {
			std::cerr << "AL_INVALID_OPERATION : Un des buffers est toujours en cours d'utilisation." << std::endl;
		} else if (error == AL_INVALID_NAME) {
			std::cerr << "AL_INVALID_NAME : Un nom de buffer n'est pas valide." << std::endl;
		} else if (error == AL_INVALID_VALUE) {
			std::cerr << "AL_INVALID_VALUE : Tous les buffers de l'objet n'ont pas pu etre supprimes." << std::endl;
		}
	}

	this->_sources.clear();
	this->_buffers.clear();
	this->_fichiers.clear();

	std::cerr << "Objet BUFFER detruit !" << std::endl;
}

/////////////////////////////////////////////////////////////
//////////////////// Création de buffers ////////////////////
/////////////////////////////////////////////////////////////

ALuint Buffer::creerBufferFromFile(const std::string Filename, Source* source)
{
	SF_INFO FileInfos;
	SNDFILE* File;

	// Ouverture du fichier audio avec libsndfile
	File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);

	if (!File)
	{
		std::cerr << "Impossible d'ouvrir le fichier audio : " << Filename << std::endl;
		return 0;
	}

	// Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
	ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
	ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

	// Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
	std::vector<ALshort> Samples(NbSamples);

	if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
	{
		std::cerr << "Impossible de lire les echantillons stockes dans le fichier audio : " << Filename << std::endl;
		return 0;
	}

	// Fermeture du fichier
	int close = sf_close(File);

	if (close != 0)
	{
		std::cerr << "Impossible de fermer le fichier audio : " << Filename << std::endl;
		return 0;
	}

	// Détermination du format en fonction du nombre de canaux
	ALenum Format;

	switch (FileInfos.channels)
	{
		case 1 : Format = AL_FORMAT_MONO16; break;
		case 2 : Format = AL_FORMAT_STEREO16; break;
		default :
			std::cerr << "Format audio non supporte (plus de 2 canaux)" << std::endl;
			return 0;
	}

	ALuint Buffer;

	alGetError();

	// Création du tampon OpenAL
	alGenBuffers(1, &Buffer);

	alCheckError();

	// Remplissage avec les échantillons lus
	alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

	// Vérification des erreurs
	if (alGetError() != AL_NO_ERROR)
	{
		std::cerr << "Impossible de remplir le tampon OpenAL avec les echantillons du fichier audio : " << Filename << std::endl;
		return 0;
	}

	this->attachBufferToSource(Buffer, source);
	return Buffer;
}

std::vector<ALuint> Buffer::creerBuffer(Buffer::typeSon son)
{
	this->_fichiers.clear();
	this->setTypeSon(son);
	PointeurIntelligent<SequenceAleatoire> seq;

	switch (son)
	{
		case ARBRE:
			this->addFichier("./data/sound/arbre.wav");
			break;
		case CASCADE:
			this->addFichier("./data/sound/cascade.wav");
			break;
		case CHUTE:
			this->addFichier("./data/sound/chute.wav");
			break;
		case DIALOGUE:
			this->addFichier("./data/sound/dialogue.wav");
			break;
		case EAU:
			this->addFichier("./data/sound/brook.wav");
			break;
		case EPEE:
			seq = new SequenceAleatoire(2);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/epee1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/epee2.wav");
						break;
				}
			}

			break;
		case HACHE:
			seq = new SequenceAleatoire(2);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/hache1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/hache2.wav");
						break;
				}
			}

			break;
		case MARTEAU:
			seq = new SequenceAleatoire(2);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/marteau1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/marteau2.wav");
						break;
				}
			}

			break;
		case MUSIQUE_COMBAT:
			seq = new SequenceAleatoire(3);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/musique_combat1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/musique_combat2.wav");
						break;
					case 3:
						this->addFichier("./data/sound/musique_combat3.wav");
						break;
				}
			}

			break;
		case MUSIQUE_EXPLORATION:
			seq = new SequenceAleatoire(3);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/musique_exploration1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/musique_exploration2.wav");
						break;
					case 3:
						this->addFichier("./data/sound/musique_exploration3.wav");
						break;
				}
			}

			break;
		case NAGE:
			seq = new SequenceAleatoire(4);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/nage1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/nage2.wav");
						break;
					case 3:
						this->addFichier("./data/sound/nage3.wav");
						break;
					case 4:
						this->addFichier("./data/sound/nage4.wav");
						break;
				}
			}

			break;
		case OISEAU:
			seq = new SequenceAleatoire(2);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/oiseau1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/oiseau2.wav");
						break;
				}
			}

			break;
		case PAS:
			seq = new SequenceAleatoire(4);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/pas1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/pas2.wav");
						break;
					case 3:
						this->addFichier("./data/sound/pas3.wav");
						break;
					case 4:
						this->addFichier("./data/sound/pas4.wav");
						break;
				}
			}

			break;
		case PORTE:
			this->addFichier("./data/sound/porte.wav");
			break;
		case SAUT:
			seq = new SequenceAleatoire(2);

			for (unsigned int i=0; i < seq->size(); ++i)
			{
				switch(seq->get(i))
				{
					case 1:
						this->addFichier("./data/sound/saut1.wav");
						break;
					case 2:
						this->addFichier("./data/sound/saut2.wav");
						break;
				}
			}

			break;
		case TA_GUEULE:
			this->addFichier("./data/sound/ta_gueule.wav");
			break;
		case TONNERRE:
			this->addFichier("./data/sound/tonnerre.wav");
			break;
		case VENT:
			this->addFichier("./data/sound/vent.wav");
			break;
		default :
			std::cerr << "Ce type de son n'existe pas : " << this->convertTypeSonToString(son) << std::endl;
			this->_buffers.clear();
			return this->_buffers;
	}

	delete seq;

	SF_INFO FileInfos;
	SNDFILE* File;
	ALuint Buffer;

	for (std::size_t i=0; i < this->_fichiers.size(); i++)
	{

		// Ouverture du fichier audio avec libsndfile
		File = sf_open(this->getFichiers()[i].c_str(), SFM_READ, &FileInfos);

		if (!File)
		{
			std::cerr << "Impossible d'ouvrir le fichier audio : " << getFichiers()[i] << std::endl;
			// this->_buffers.clear();
			return this->_buffers;
		}

		// Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
		ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
		ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

		// Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
		std::vector<ALshort> Samples(NbSamples);

		if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
		{
			std::cerr << "Impossible de lire les echantillons stockes dans le fichier audio : " << getFichiers()[i] << std::endl;
			// this->_buffers.clear();
			return this->_buffers;
		}

		// Fermeture du fichier
		int close = sf_close(File);

		if (close != 0)
		{
			std::cerr << "Impossible de fermer le fichier audio : " << getFichiers()[i] << std::endl;
			// this->_buffers.clear();
			return this->_buffers;
		}

		// Détermination du format en fonction du nombre de canaux
		ALenum Format;
		// bool IsMultiChannelSupported = alIsExtensionPresent("AL_EXT_MCFORMATS");

		switch (FileInfos.channels)
		{
			case 1 : Format = AL_FORMAT_MONO16; break;
			case 2 : Format = AL_FORMAT_STEREO16; break;
		/*
			if (IsMultiChannelSupported == true)
			{
				case 4 : Format = alGetEnumValue("AL_FORMAT_QUAD16");  break;
				case 6 : Format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
				case 7 : Format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
				case 8 : Format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
			}
		*/
			default :
				std::cerr << "Format audio non supporte (plus de 2 canaux)" << std::endl;
				// this->_buffers.clear();
				return this->_buffers;
		}

		alGetError();

		// Création du tampon OpenAL
		alGenBuffers(1, &Buffer);

		// Vérification des erreurs
		if (alGetError() != AL_NO_ERROR)
		{
			std::cerr << "Impossible de creer le tampon OpenAL n°" << i+1 << std::endl;
			this->_buffers.clear();
			return this->_buffers;
		}

		alGetError();

		// Remplissage avec les échantillons lus
		alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

		// Vérification des erreurs
		if (alGetError() != AL_NO_ERROR)
		{
			std::cerr << "Impossible de remplir le tampon OpenAL n°" << i+1 << " avec les echantillons du fichier audio : " << getFichiers()[i] << std::endl;
			this->_buffers.clear();
			return this->_buffers;
		}

		this->_buffers.push_back(Buffer);

	}

	return this->_buffers;
}

std::vector<ALuint> Buffer::creerBuffer(Buffer::typeSon son, Source* source)
{
	this->_buffers = this->creerBuffer(son);

	if (! this->getBuffers().empty())
	{
		this->attachBuffersToSource(source);
	} else {
		std::cerr << "Le vecteur de buffers est vide !" << std::endl;
	}

	return this->_buffers;
}

std::vector<ALuint> Buffer::creerBuffer(Buffer::typeSon son, Source* source, float x, float y, float z)
{
	this->_buffers = creerBuffer(son, source);
	source->setCoordonnees(x, y, z);
	return this->_buffers;
}

//////////////////////////////////////////////////////////////////////
//////////////////// Ajout/suppression de buffers ////////////////////
//////////////////////////////////////////////////////////////////////

void Buffer::attachBufferToSource(ALuint buffer, Source* source)
{
	alGetError();
	alSourceQueueBuffers(source->getSource(), 1, &buffer);

	if (alGetError() == AL_NO_ERROR)
	{
		this->_sources.push_back(source);
	} else {
		std::cerr << "Erreur lors de l'attachement du buffer à la source" << std::endl;
	}
}

void Buffer::attachBuffersToSource(Source* source)
{
	alGetError();
	alSourceQueueBuffers(source->getSource(), this->_buffers.size(), this->_buffers.data());

	if (alGetError() == AL_NO_ERROR)
	{
		this->_sources.push_back(source);
	} else {
		std::cerr << "Erreur lors de l'attachement des buffers à la source" << std::endl;
	}
}

void Buffer::detachBufferFromSource(ALuint buffer, Source* source)
{
	alGetError();
	alSourceUnqueueBuffers(source->getSource(), 1, &buffer);
	alCheckError();
}

void Buffer::detachBuffersFromSource(Source* source)
{
	alGetError();
	alSourceUnqueueBuffers(source->getSource(), this->_buffers.size(), this->_buffers.data());

	if (alGetError() == AL_NO_ERROR)
	{
		this->_sources.clear();
	} else {
		std::cerr << "Erreur lors du detachement des buffers de la source" << std::endl;
	}
}

void Buffer::detachBuffersFromAllSources()
{
	for (std::size_t i=0; i < this->getSourcesSize(); i++)
	{
		this->detachBuffersFromSource(getSources()[i]);
	}
}

////////////////////////////////////////////////////////////////
//////////////////// Méthodes de conversion ////////////////////
////////////////////////////////////////////////////////////////

std::string Buffer::convertTypeSonToString(Buffer::typeSon typeSon)
{
	std::string typeSonString;

	if (typeSon == Buffer::ARBRE)
	{
		typeSonString = "ARBRE";
	} else if (typeSon == Buffer::CASCADE) {
		typeSonString = "CASCADE";
	} else if (typeSon == Buffer::CHUTE) {
		typeSonString = "CHUTE";
	} else if (typeSon == Buffer::DIALOGUE) {
		typeSonString = "DIALOGUE";
	} else if (typeSon == Buffer::EAU) {
		typeSonString = "EAU";
	} else if (typeSon == Buffer::EPEE) {
		typeSonString = "EPEE";
	} else if (typeSon == Buffer::HACHE) {
		typeSonString = "HACHE";
	} else if (typeSon == Buffer::MARTEAU) {
		typeSonString = "MARTEAU";
	} else if (typeSon == Buffer::MUSIQUE_COMBAT) {
		typeSonString = "MUSIQUE_COMBAT";
	} else if (typeSon == Buffer::MUSIQUE_EXPLORATION) {
		typeSonString = "MUSIQUE_EXPLORATION";
	} else if (typeSon == Buffer::NAGE) {
		typeSonString = "NAGE";
	} else if (typeSon == Buffer::OISEAU) {
		typeSonString = "OISEAU";
	} else if (typeSon == Buffer::PAS) {
		typeSonString = "PAS";
	} else if (typeSon == Buffer::PORTE) {
		typeSonString = "PORTE";
	} else if (typeSon == Buffer::SAUT) {
		typeSonString = "SAUT";
	} else if (typeSon == Buffer::TA_GUEULE) {
		typeSonString = "TA_GUEULE";
	} else if (typeSon == Buffer::TONNERRE) {
		typeSonString = "TONNERRE";
	} else if (typeSon == Buffer::VENT) {
		typeSonString = "VENT";
	} else {
		std::cerr << "Ce type de son n'existe pas : " << typeSon << std::endl;
		exit(0);
	}

	return typeSonString;
}

Buffer::typeSon Buffer::convertStringToTypeSon(std::string typeSonString)
{
	Buffer::typeSon typeSon;


	if (typeSonString == "ARBRE" || typeSonString == "arbre")
	{
		typeSon = Buffer::ARBRE;
	} else if (typeSonString == "CASCADE" || typeSonString == "cascade") {
		typeSon = Buffer::CASCADE;
	} else if (typeSonString == "CHUTE" || typeSonString == "chute") {
		typeSon = Buffer::CHUTE;
	} else if (typeSonString == "DIALOGUE" || typeSonString == "dialogue") {
		typeSon = Buffer::DIALOGUE;
	} else if (typeSonString == "EAU" || typeSonString == "eau") {
		typeSon = Buffer::EAU;
	} else if (typeSonString == "EPEE" || typeSonString == "epee") {
		typeSon = Buffer::EPEE;
	} else if (typeSonString == "HACHE" || typeSonString == "hache") {
		typeSon = Buffer::HACHE;
	} else if (typeSonString == "MARTEAU" || typeSonString == "marteau") {
		typeSon = Buffer::MARTEAU;
	} else if (typeSonString == "MUSIQUE_COMBAT" || typeSonString == "musique_combat") {
		typeSon = Buffer::MUSIQUE_COMBAT;
	} else if (typeSonString == "MUSIQUE_EXPLORATION" || typeSonString == "musique_exploration") {
		typeSon = Buffer::MUSIQUE_EXPLORATION;
	} else if (typeSonString == "NAGE" || typeSonString == "nage") {
		typeSon = Buffer::NAGE;
	} else if (typeSonString == "OISEAU" || typeSonString == "oiseau") {
		typeSon = Buffer::OISEAU;
	} else if (typeSonString == "PAS" || typeSonString == "pas") {
		typeSon = Buffer::PAS;
	} else if (typeSonString == "PORTE" || typeSonString == "porte") {
		typeSon = Buffer::PORTE;
	} else if (typeSonString == "SAUT" || typeSonString == "saut") {
		typeSon = Buffer::SAUT;
	} else if (typeSonString == "TA_GUEULE" || typeSonString == "ta_gueule") {
		typeSon = Buffer::TA_GUEULE;
	} else if (typeSonString == "TONNERRE" || typeSonString == "tonnerre") {
		typeSon = Buffer::TONNERRE;
	} else if (typeSonString == "VENT" || typeSonString == "vent") {
		typeSon = Buffer::VENT;
	} else {
		std::cerr << "Ce type de son n'existe pas : " << typeSonString << std::endl;
		exit(0);
	}

	return typeSon;
}

//////////////////////////////////////////////////
//////////////////// Getteurs ////////////////////
//////////////////////////////////////////////////

Buffer::typeSon Buffer::getTypeSon()
{
	return this->_typeSon;
}

std::vector< PointeurIntelligent<Source> > Buffer::getSources()
{
	return this->_sources;
}

size_t Buffer::getSourcesSize()
{
	return this->_sources.size();
}

std::vector<ALuint> Buffer::getBuffers()
{
	return this->_buffers;
}

ALuint* Buffer::getBuffersPointer()
{
	return (ALuint*)(this->_buffers.data());
}

size_t Buffer::getBuffersSize()
{
	return this->_buffers.size();
}

std::vector<std::string> Buffer::getFichiers()
{
	return this->_fichiers;
}


// Méthodes privées

//////////////////////////////////////////////////
//////////////////// Setteurs ////////////////////
//////////////////////////////////////////////////

void Buffer::setTypeSon(Buffer::typeSon son)
{
	this->_typeSon = son;
}

////////////////////////////////////////////////////////////////////////////
//////////////////// Méthodes d'ajout dans les vecteurs ////////////////////
////////////////////////////////////////////////////////////////////////////

void Buffer::addSource(Source* source)
{
	this->_sources.push_back(source);
}

void Buffer::addBuffer(ALuint buffer)
{
	this->_buffers.push_back(buffer);
}

void Buffer::addFichier(std::string Filename)
{
	this->_fichiers.push_back(Filename);
}
