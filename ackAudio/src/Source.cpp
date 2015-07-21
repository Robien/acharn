/*
 * Source.cpp
 *
 *  Created on: 1 oct. 2010
 *      Author: genesis
 */

#include "Contexte.h"
#include "Source.h"

// Méthodes publiques

///////////////////////////////////////////////////////////////////
//////////////////// Constructeurs/Destructeur ////////////////////
///////////////////////////////////////////////////////////////////

Source::Source()
{
	std::cerr << "Création d'un objet SOURCE avec le constructeur de base" << std::endl;
	this->_buffers.clear();
	this->creerSource();
}

Source::Source(Buffer::typeSon son)
{
	std::cerr << "Création d'un objet SOURCE avec le constructeur typeSon" << std::endl;
	this->_buffers.clear();
	this->creerSource();
	Buffer* buffer = new Buffer(son);
	this->attachBuffersToSource(buffer);
}

Source::Source(Buffer::typeSon son, float x, float y, float z, bool loop)
{
	std::cerr << "Création d'un objet SOURCE avec le constructeur typeSon + coordonnees float + loop" << std::endl;
	this->_buffers.clear();
	this->creerSource(x, y, z, loop);
	Buffer* buffer = new Buffer(son);
	this->attachBuffersToSource(buffer);
}

Source::Source(Buffer::typeSon son, irr::core::vector3df coordonnees, bool loop)
{
	std::cerr << "Création d'un objet SOURCE avec le constructeur typeSon + coordonnees Irrlicht + loop" << std::endl;
	this->_buffers.clear();
	this->creerSource(coordonnees, loop);
	Buffer* buffer = new Buffer(son);
	this->attachBuffersToSource(buffer);
}

Source::~Source()
{
	std::cerr << "Destruction d'un objet SOURCE" << std::endl;
	this->deleteSource();
	std::cerr << "Objet SOURCE detruit !" << std::endl;
}

/////////////////////////////////////////////////////////////
//////////////////// Création de sources ////////////////////
/////////////////////////////////////////////////////////////

void Source::creerSource()
{
	alGetError();

	// Création d'une source
	alGenSources(1, &this->_source);

	if (alCheckError("alGenSources", false) != AL_NO_ERROR)
	{
		std::cerr << "SOURCE : impossible de creer la source" << std::endl;
		alDeleteSources(1, &this->_source);
		alCheckError("alDeleteSources");
		this->_source = 0;
	}
}

void Source::creerSource(float x, float y, float z, bool loop)
{
	this->creerSource();

	if (this->_source != 0)
	{
		alGetError();

		// Définition des coordonnées de la source
		alSource3f(this->_source, AL_POSITION, x, y, z);
		alCheckError("alSource3f");

		alGetError();

		// Définition du mode de lecture de la source
		alSourcei(this->_source, AL_LOOPING, loop);
		alCheckError("alSourcei");
	}
}

//////////////////////////////////////////////////////////////////////
//////////////////// Ajout/suppression de sources ////////////////////
//////////////////////////////////////////////////////////////////////

void Source::attachBufferToSource(ALuint buffer)
{
	alGetError();

	alSourceQueueBuffers(this->_source, 1, &buffer);
	// alSourcei(this->_source, AL_BUFFER, buffer);

	alCheckError("alSourceQueueBuffers");
}

void Source::attachBuffersToSource(Buffer* buffer)
{

	for (std::size_t i=0; i < buffer->getBuffersSize(); i++)
	{
		alGetError();
		alSourceQueueBuffers(this->_source, 1, &buffer->getBuffers()[i]);
		// alSourcei(this->_source, AL_BUFFER, buffer->getBuffersPointer());

		ALenum error = alCheckError("alSourceQueueBuffers");

		if (error == AL_NO_ERROR)
		{
			std::cerr << "SOURCE : buffer attaché à la source !" << std::endl;
			this->addBuffer(buffer);
		}
	}
}

/*
void Source::detachBufferFromSource(ALuint buffer)
{
	alGetError();
	alSourceUnqueueBuffers(this->_source, 1, &buffer);

	if (alGetError() == AL_INVALID_VALUE)
	{
		std::cerr << "At least one buffer can not be unqueued because it has not been processed yet." << std::endl;
	} else if (alGetError() == AL_INVALID_NAME) {
		std::cerr << "The specified source name is not valid." << std::endl;
	} else if (alGetError() == AL_INVALID_OPERATION) {
		std::cerr << "There is no current context." << std::endl;
	}
}

void Source::detachBuffersFromSource(Buffer* buffer)
{

	alGetError();

	alSourceUnqueueBuffers(this->_source, buffer->getBuffersSize(), buffer->getBuffersPointer());

	if (alGetError() == AL_INVALID_VALUE)
	{
		std::cerr << "At least one buffer can not be unqueued because it has not been processed yet." << std::endl;
	} else if (alGetError() == AL_INVALID_NAME) {
		std::cerr << "The specified source name is not valid." << std::endl;
	} else if (alGetError() == AL_INVALID_OPERATION) {
		std::cerr << "There is no current context." << std::endl;
	}
}

void Source::detachAllBuffersFromSource()
{
	if (this->_buffers.size() > 0)
	{
		for (std::size_t i=0; i < this->_buffers.size(); i++)
		{
			this->detachBuffersFromSource(this->_buffers[i]);
		}
	}
}
*/

void Source::deleteSource()
{
	ALint NbQueued;
	ALuint Buffer;

	alGetError();
	alGetSourcei(this->_source, AL_BUFFERS_QUEUED, &NbQueued);

	for (ALint i=0; i < NbQueued; ++i)
	{
		alGetError();
	    alSourceUnqueueBuffers(this->_source, 1, &Buffer);
	    alCheckError("alSourceUnqueueBuffers");

		alGetError();
		alDeleteBuffers(1, &this->getBuffers()[0]->getBuffers()[i]);
	}

	alGetError();
	alSourcei(this->_source, AL_BUFFER, 0);

	ALenum error = alCheckError("alSourcei", false);

	if (error != AL_NO_ERROR)
	{
		std::cerr << "erreur lors du detachement des buffers" << std::endl;
	}

/*
	// this->detachAllBuffersFromSource();
	alGetError();

	// Destruction de la source
	alSourcei(this->_source, AL_BUFFER, 0);

	if (alGetError() != AL_NO_ERROR)
	{
		std::cerr << "erreur lors du detachement des buffers" << std::endl;
	}
*/
	alGetError();

	alDeleteSources(1, &_source);

	if (alGetError() == AL_INVALID_NAME)
	{
		std::cerr << "At least one specified source is not valid, or an attempt is being made to delete more sources than exist." << std::endl;
	} else if (alGetError() == AL_INVALID_OPERATION) {
		std::cerr << "There is no current context." << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////
//////////////////// Manipulations sur les sources ////////////////////
///////////////////////////////////////////////////////////////////////

void Source::enableLoop()
{
	alGetError();
	alSourcei(this->_source, AL_LOOPING, AL_TRUE);
	alCheckError("alSourcei");
}

void Source::disableLoop()
{
	alGetError();
	alSourcei(this->_source, AL_LOOPING, AL_FALSE);
	alCheckError("alSourcei");
}

void Source::play()
{
	// if (! this->isPlaying() && ! this->isStopped())
	// {
		alGetError();
		alSourcePlay(this->_source);
		alCheckError("alSourcePlay");
	// }
}

void Source::pause()
{
	// if (this->isPlaying())
	// {
		alGetError();
		alSourcePause(this->_source);
		alCheckError("alSourcePause");
	// }
}

void Source::stop()
{
	// if (this->isPlaying() || this->isPaused())
	// {
		alGetError();
		alSourceStop(this->_source);
		alCheckError("alSourceStop");
	// }
}

void Source::rewind()
{
	/* if (this->isPlaying())
	{
		this->stop();
	} */

	alGetError();
	alSourceRewind(this->_source);
	alCheckError("alSourceRewind");
}

//////////////////////////////////////////////////
//////////////////// Setteurs ////////////////////
//////////////////////////////////////////////////

void Source::setVitesseLecture(float vitesse)
{
	alGetError();

	if (vitesse <= 0.5)
	{
		alSourcef(_source, AL_PITCH, 0.5);
	} else if (vitesse >= 2.0) {
		alSourcef(this->_source, AL_PITCH, 2.0);
	} else {
		alSourcef(this->_source, AL_PITCH, vitesse);
	}
}

void Source::setVolume(unsigned int volume)
{
/*
	if (volume <= 0)
	{
		alSourcei(this->_source, AL_GAIN, 0);
	} else if (volume >= 400) {
		alSourcei(this->_source, AL_GAIN, 400);
	} else {
		alSourcei(this->_source, AL_GAIN, volume);
	}
*/

	alSourcei(this->_source, AL_GAIN, volume);
}

void Source::setCoordonnees(float x, float y, float z)
{
	alSource3f(this->_source, AL_POSITION, x, y, z);
}

void Source::setLoop (bool loop)
{
	if (loop == true)
	{
		this->enableLoop();
	} else {
		this->disableLoop();
	}
}

//////////////////////////////////////////////////
//////////////////// Getteurs ////////////////////
//////////////////////////////////////////////////

ALuint Source::getSource()
{
	return this->_source;
}

std::vector< PointeurIntelligent<Buffer> > Source::getBuffers()
{
	return this->_buffers;
}

size_t Source::getBuffersSize()
{
	return this->_buffers.size();
}

float Source::getVitesseLecture()
{
	float VitesseLecture;
	alGetSourcef(this->_source, AL_PITCH, &VitesseLecture);
	return VitesseLecture;
}

unsigned int Source::getVolume()
{
	int Volume;
	alGetSourcei(this->_source, AL_GAIN, &Volume);
	return Volume;
}

irr::core::vector3df Source::getCoordonnees()
{
	irr::core::vector3df Coordonnees;
	alGetSource3f(this->_source, AL_POSITION, &Coordonnees.X, &Coordonnees.Y, &Coordonnees.Z);
	return Coordonnees;
}

ALfloat Source::getTemps()
{
	ALfloat Seconds = 0.f;
	alGetSourcef(this->_source, AL_SEC_OFFSET, &Seconds);
	return Seconds;
}

ALint Source::getStatus()
{
	ALint Status;
	alGetSourcei(this->_source, AL_SOURCE_STATE, &Status);
	return Status;
}

//////////////////////////////////////////////////////////
//////////////////// Méthodes de test ////////////////////
//////////////////////////////////////////////////////////

bool Source::isLooping()
{
	ALint etat;
	alGetSourcei(this->_source, AL_LOOPING, &etat);

	if (etat == 1)
	{
		return true;
	} else {
		return false;
	}
}

bool Source::isInitialized()
{
	ALint etat;
	alGetSourcei(this->_source, AL_SOURCE_STATE, &etat);

	if (etat == AL_INITIAL)
	{
		return true;
	} else {
		return false;
	}
}

bool Source::isPlaying()
{
	ALint etat;
	alGetSourcei(this->_source, AL_SOURCE_STATE, &etat);

	if (etat == AL_PLAYING)
	{
		return true;
	} else {
		return false;
	}
}

bool Source::isPaused()
{
	ALint etat;
	alGetSourcei(this->_source, AL_SOURCE_STATE, &etat);

	if (etat == AL_PAUSED)
	{
		return true;
	} else {
		return false;
	}
}

bool Source::isStopped()
{
	ALint etat;
	alGetSourcei(this->_source, AL_SOURCE_STATE, &etat);

	if (etat == AL_STOPPED)
	{
		return true;
	} else {
		return false;
	}
}


// Méthodes privées

////////////////////////////////////////////////////////////////////////////
//////////////////// Méthodes d'ajout dans les vecteurs ////////////////////
////////////////////////////////////////////////////////////////////////////

void Source::addBuffer(Buffer* buffer)
{
	this->_buffers.push_back(buffer);
}
