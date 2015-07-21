/*
 * Contexte.cpp
 *
 *  Created on: 9 oct. 2010
 *      Author: genesis
 */

#include "Contexte.h"

//////////////////////////////////////////////////////////
//////////////////// Méthodes de test ////////////////////
//////////////////////////////////////////////////////////

ALenum alCheckError(std::string nomFonction, bool affichageErreur)
{
	ALenum error = alGetError();

	alGetError();

	if (affichageErreur == true)
	{
		if (nomFonction == "générique")
		{

			if (error == AL_INVALID_NAME)
			{
				std::cerr << "AL_INVALID_NAME : a bad name (ID) was passed to an OpenAL function." << std::endl;
			} else if (error == AL_INVALID_ENUM) {
				std::cerr << "AL_INVALID_ENUM : an invalid enum value was passed to an OpenAL function." << std::endl;
			} else if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : an invalid value was passed to an OpenAL function." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : the requested operation is not valid." << std::endl;
			} else if (error == AL_OUT_OF_MEMORY) {
				std::cerr << "AL_OUT_OF_MEMORY : the requested operation resulted in OpenAL running out of memory." << std::endl;
			}

		} else if (nomFonction == "contexte") {

			if (error == ALC_INVALID_DEVICE)
			{
				std::cerr << "ALC_INVALID_DEVICE : a bad device was passed to an OpenAL function." << std::endl;
			} else if (error == ALC_INVALID_CONTEXT) {
				std::cerr << "ALC_INVALID_CONTEXT : a bad context was passed to an OpenAL function." << std::endl;
			} else if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : an invalid value was passed to an OpenAL function." << std::endl;
			} else if (error == ALC_INVALID_ENUM) {
				std::cerr << "ALC_INVALID_ENUM : an unknown enum value was passed to an OpenAL function." << std::endl;
			} else if (error == ALC_OUT_OF_MEMORY) {
				std::cerr << "ALC_OUT_OF_MEMORY : the requested operation resulted in OpenAL running out of memory." << std::endl;
			}

		} else if (nomFonction == "écouteur (set)") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value given is not valid." << std::endl;
			} else if (error == ALC_INVALID_ENUM) {
				std::cerr << "ALC_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "écouteur (get)") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value pointer given is not valid." << std::endl;
			} else if (error == ALC_INVALID_ENUM) {
				std::cerr << "ALC_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alGenBuffers") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The buffer array isn't large enough to hold the number of buffers requested." << std::endl;
			} else if (error == AL_OUT_OF_MEMORY) {
				std::cerr << "AL_OUT_OF_MEMORY : There is not enough memory available to generate all the buffers requested." << std::endl;
			}

		} else if (nomFonction == "alDeleteBuffers") {

			if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : The buffer is still in use and can not be deleted." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : A buffer name is invalid." << std::endl;
			} else if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The requested number of buffers can not be deleted." << std::endl;
			}

		} else if (nomFonction == "alGenSources") {

			if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_OUT_OF_MEMORY : There is not enough memory to generate all the requested sources." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_VALUE : There are not enough non-memory resources to create all the requested sources, or the array pointer is not valid." << std::endl;
			} else if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_OPERATION : There is no context to create sources in." << std::endl;
			}

		} else if (nomFonction == "alDeleteSources") {

			if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : At least one specified source is not valid, or an attempt is being made to delete more sources than exist." << std::endl;
			} else if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alSourcef") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value given is out of range." << std::endl;
			} else if (error == AL_INVALID_ENUM) {
				std::cerr << "AL_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alSource3f") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value pointer given is not valid." << std::endl;
			} else if (error == AL_INVALID_ENUM) {
				std::cerr << "AL_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alSourcei") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value pointer given is not valid." << std::endl;
			} else if (error == AL_INVALID_ENUM) {
				std::cerr << "AL_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alGetSourcef") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value pointer given is not valid." << std::endl;
			} else if (error == AL_INVALID_ENUM) {
				std::cerr << "AL_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alGetSource3f") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value pointer given is not valid." << std::endl;
			} else if (error == AL_INVALID_ENUM) {
				std::cerr << "AL_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alGetSourcei") {

			if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : The value pointer given is not valid." << std::endl;
			} else if (error == AL_INVALID_ENUM) {
				std::cerr << "AL_INVALID_ENUM : The specified parameter is not valid." << std::endl;
			} else if (error == AL_INVALID_NAME) {
				std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
			} else if (error == AL_INVALID_OPERATION) {
				std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
			}

		} else if (nomFonction == "alSourcePlay") {

				if (error == AL_INVALID_NAME) {
					std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
				} else if (error == AL_INVALID_OPERATION) {
					std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
				}

		} else if (nomFonction == "alSourcePause") {

				if (error == AL_INVALID_NAME) {
					std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
				} else if (error == AL_INVALID_OPERATION) {
					std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
				}

		} else if (nomFonction == "alSourceStop") {

				if (error == AL_INVALID_NAME) {
					std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
				} else if (error == AL_INVALID_OPERATION) {
					std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
				}

		} else if (nomFonction == "alSourceRewind") {

				if (error == AL_INVALID_NAME) {
					std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
				} else if (error == AL_INVALID_OPERATION) {
					std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
				}

		} else if (nomFonction == "alSourceQueueBuffers") {

				if (error == AL_INVALID_NAME) {
					std::cerr << "AL_INVALID_NAME : At least one specified buffer name is not valid, or the specified source name is not valid." << std::endl;
				} else if (error == AL_INVALID_OPERATION) {
					std::cerr << "AL_INVALID_OPERATION : There is no current context, an attempt was made to add a new buffer which is not the same format as the buffers already in the queue, or the source already has a static buffer attached." << std::endl;
				}

		} else if (nomFonction == "alSourceUnqueueBuffers") {

				if (error == AL_INVALID_VALUE) {
					std::cerr << "AL_INVALID_VALUE : At least one buffer can not be unqueued because it has not been processed yet." << std::endl;
				} else if (error == AL_INVALID_NAME) {
					std::cerr << "AL_INVALID_NAME : The specified source name is not valid." << std::endl;
				} else if (error == AL_INVALID_OPERATION) {
					std::cerr << "AL_INVALID_OPERATION : There is no current context." << std::endl;
				}

		}
	}

	return error;
}

ALCenum alCheckContextError(bool affichageErreur)
{
	ALCenum error = alGetError();

	alGetError();

	if (affichageErreur == true)
	{

			if (error == ALC_INVALID_DEVICE)
			{
				std::cerr << "ALC_INVALID_DEVICE : a bad device was passed to an OpenAL function." << std::endl;
			} else if (error == ALC_INVALID_CONTEXT) {
				std::cerr << "ALC_INVALID_CONTEXT : a bad context was passed to an OpenAL function." << std::endl;
			} else if (error == AL_INVALID_VALUE) {
				std::cerr << "AL_INVALID_VALUE : an invalid value was passed to an OpenAL function." << std::endl;
			} else if (error == ALC_INVALID_ENUM) {
				std::cerr << "ALC_INVALID_ENUM : an unknown enum value was passed to an OpenAL function." << std::endl;
			} else if (error == ALC_OUT_OF_MEMORY) {
				std::cerr << "ALC_OUT_OF_MEMORY : the requested operation resulted in OpenAL running out of memory." << std::endl;
			}

	}

	return error;
}

Contexte::Contexte(const char* DeviceName, ALCint* attributs, ALenum modele)
{
	std::cerr << "Création d'un objet CONTEXTE" << std::endl;
	this->creerContexte(DeviceName, attributs, modele);
	this->_ecouteur = new Ecouteur(0.0, 0.0, 0.0);
}

Contexte::~Contexte()
{
	std::cerr << "Destruction d'un objet CONTEXTE" << std::endl;
	this->detruireContexte();
	std::cerr << "Objet CONTEXTE détruit !" << std::endl;
}

void Contexte::pauseContexte()
{
	alcSuspendContext(alcGetCurrentContext());
}

void Contexte::resumeContexte()
{
	alcProcessContext(alcGetCurrentContext());
}

void Contexte::setDevice(const std::string DeviceName, ALCint* attributs, ALenum modele)
{
	this->detruireContexte();
	this->creerContexte(DeviceName.c_str(), attributs);
}

void Contexte::setDistanceModel(ALenum modele)
{
	alGetError();

	alDistanceModel(modele);

	ALenum error = alCheckError();

	if (error == AL_INVALID_VALUE)
	{
		std::cerr << "The specified distance model is not valid." << std::endl;
	} else if (error == AL_INVALID_OPERATION) {
		std::cerr << "There is no current context." << std::endl;
	}
}

ALCdevice* Contexte::getDevice()
{
	return alcGetContextsDevice(alcGetCurrentContext());
}

ALenum Contexte::getDistanceModel()
{
	return this->_distanceModel;
}

Ecouteur* Contexte::getEcouteur()
{
	return this->_ecouteur;
}


// Méthodes privées

void Contexte::creerContexte(const char* DeviceName, ALCint* attributs, ALenum modele)
{
	// Ouverture du device
	ALCdevice* Device = alcOpenDevice(DeviceName);

	if (! Device)
	{
		std::cerr << "CONTEXTE : impossible d'ouvrir le device : " << DeviceName << std::endl;
	}

	// Création du contexte
	ALCcontext* Context = alcCreateContext(Device, attributs);

	if (! Context)
	{
		std::cerr << "CONTEXTE : impossible de créer un environnement audio" << std::endl;
	}

	// Activation du contexte
	if (! alcMakeContextCurrent(Context))
	{
		std::cerr << "CONTEXTE : impossible d'activer l'environnement audio" << std::endl;
	}

	this->setDistanceModel(modele);
}

void Contexte::detruireContexte()
{
    // Récupération du contexte et du device
    ALCcontext* Context = alcGetCurrentContext();
    ALCdevice* Device = alcGetContextsDevice(Context);

	// Désactivation du contexte
	alGetError();

	if (alcMakeContextCurrent(NULL))
	{
		std::cerr << "CONTEXTE : contexte désactivé" << std::endl;
	} else {
		std::cerr << "CONTEXTE : erreur lors de la désactivation" << std::endl;
	}

	// Destruction du contexte
	alGetError();
	alcDestroyContext(Context);

	ALCenum error = alCheckContextError(true);

	if (error != ALC_INVALID_CONTEXT)
	{
		std::cerr << "CONTEXTE : contexte détruit" << std::endl;
	} else {
		std::cerr << "CONTEXTE : erreur lors de la destruction" << std::endl;
	}

	// Fermeture du device
	alGetError();

	if (alcCloseDevice(Device))
	{
		std::cerr << "CONTEXTE : périphérique audio fermé" << std::endl;
	}  else {
		std::cerr << "CONTEXTE : erreur lors de la fermeture du périphérique audio" << std::endl;
	}
}
