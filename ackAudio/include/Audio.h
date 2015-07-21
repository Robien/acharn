/*
 * Audio.h
 *
 *  Created on: 14 sept. 2010
 *      Author: David
 */

////////////////////////////////////////////////////////////
/// En-têtes
////////////////////////////////////////////////////////////

#ifndef AUDIO_H_
#define AUDIO_H_

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
// #include <iomanip>
#include <iostream>
#include <string.h>
#include <vector>
#include "Referenced.h"

class Audio : public Referenced
{
public:
    Audio();
    virtual ~Audio();
    ALuint creerSource(ALuint Source = NULL, float x=0.0, float y=0.0, float z=0.0, ALboolean loop = AL_FALSE);
    ALuint creerBuffer(const std::string Filename = "");
    ALuint creerBufferArbre();
    ALuint creerBufferCascade();
    ALuint creerBufferChute();
    ALuint creerBufferCri();
    ALuint creerBufferEau();
    ALuint creerBufferEpee();
    ALuint creerBufferMusiqueCombat();
    ALuint creerBufferMusiqueExploration();
    ALuint creerBufferNage();
    ALuint creerBufferOiseau();
    ALuint creerBufferPas();
    ALuint creerBufferPorte();
    ALuint creerBufferSaut();
    ALuint creerBufferTonnerre();
    ALuint creerBufferVent();
    ALboolean addBufferToSource(ALuint Buffer = NULL, ALuint Source = NULL);
    ALboolean deleteBufferFromSource(ALuint Buffer = NULL, ALuint Source = NULL);
    ALuint playFichier(const std::string Filename = "", ALboolean loop = AL_FALSE);
    void playSource(ALuint Source = NULL);
    void pauseSource(ALuint Source = NULL);
    void stopSource(ALuint Source = NULL);
    void updateSource(ALuint Source = NULL, float x=0.0, float y=0.0, float z=0.0);
    void updateSourceLoop(ALuint Source = NULL, ALboolean loop = AL_FALSE);
    void deleteSource(ALuint Source = NULL);
    ALfloat getTemps();
    ALint getStatus();
    void finish();

    typedef enum {
    	ARBRE, CASCADE, CHUTE, EAU, EPEE, MUSIQUE_COMBAT, MUSIQUE_EXPLORATION, NAGE, OISEAU, PAS, PORTE, SAUT, TONNERRE, VENT
    } typeSon;

private:
    ALuint Buffer;
    ALuint Source;

////////////////////////////////////////////////////////////
/// Initialise OpenAL (ouvre un device et crée un contexte audio)
///
/// \param DeviceName : Nom du device à ouvrir (NULL pour le device par défaut)
///
/// \return AL_TRUE si tout s'est bien passé, AL_FALSE en cas d'erreur
///
////////////////////////////////////////////////////////////
ALboolean initOpenAL(const char* DeviceName = NULL)
{
    // Ouverture du device
    ALCdevice* Device = alcOpenDevice(DeviceName);
    if (!Device)
    {
    	std::cerr << "Impossible d'ouvrir le device : " << DeviceName << std::endl;
        return AL_FALSE;
    }

    // Création du contexte
    ALCcontext* Context = alcCreateContext(Device, NULL);
    if (!Context)
    {
        std::cerr << "Impossible de creer un contexte audio" << std::endl;
        return AL_FALSE;
    }

    // Activation du contexte
    if (!alcMakeContextCurrent(Context))
    {
        std::cerr << "Impossible d'activer le contexte audio" << std::endl;
        return AL_FALSE;
    }

    return AL_TRUE;
}

////////////////////////////////////////////////////////////
/// Récupère la liste des noms des devices disponibles
///
/// \param Devices : Tableau de chaînes à remplir avec les noms des devices
///
////////////////////////////////////////////////////////////
void getDevices(std::vector<std::string> Devices)
{
	// Vidage de la liste
	std::cout << "Vidage de la liste" << std::endl;
	Devices.clear();

	// Récupération des devices disponibles
	std::cout << "Recuperation des devices disponibles" << std::endl;
	const ALCchar* DeviceList = alcGetString(NULL, ALC_DEVICE_SPECIFIER);

	if (DeviceList)
	{

		// Extraction des devices contenus dans la chaîne renvoyée
		std::cout << "Extraction des devices contenus dans la chaine renvoyee" << std::endl;
		while (strlen(DeviceList) > 0)
		{
			Devices.push_back(DeviceList);
			DeviceList += strlen(DeviceList) + 1;
		}

	} else {

		std::cerr << "Impossible de recuperer la liste des devices" << std::endl;

	}
}

////////////////////////////////////////////////////////////
/// Choisit un device parmi ceux disponibles
///
////////////////////////////////////////////////////////////
void chooseDevice()
{
	// Récupération des devices disponibles
	std::vector<std::string> Devices;
	getDevices(Devices);

	// On affiche la liste à l'utilisateur
	std::cout << "Veuillez choisir un device :" << std::endl << std::endl;
	for (std::size_t i = 0; i < Devices.size(); ++i)
	{
		std::cout << "[" << i << "] " << Devices[i] << std::endl;
	}

	// Et on le laisse choisir
	int Choice;
	std::cin >> Choice;

	// Initialisation d'OpenAL avec le device sélectionné
	initOpenAL(Devices[Choice].c_str());
}

////////////////////////////////////////////////////////////
/// Crée un tampon OpenAL à partir d'un fichier audio
///
/// \param Filename : Nom du fichier audio à charger
///
/// \return Identificateur du tampon OpenAL (0 si échec)
///
////////////////////////////////////////////////////////////
ALuint loadSound(const std::string Filename)
{
    // Ouverture du fichier audio avec libsndfile
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
    {
        std::cerr << "Impossible d'ouvrir le fichier audio : " << Filename.c_str() << std::endl;
        return 0;
    }

    // Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
    ALsizei NbSamples  = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

    // Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
    std::vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
    {
        std::cerr << "Impossible de lire les echantillons stockes dans le fichier audio" << std::endl;
        return 0;
    }

    // Fermeture du fichier
    int close = sf_close(File);

    if (close != 0)
    {
    	std::cerr << "Impossible de fermer le fichier audio : " << Filename.c_str() << std::endl;
    	return 0;
    }

    // Détermination du format en fonction du nombre de canaux
    ALenum Format;
    // bool IsMultiChannelSupported = alIsExtensionPresent("AL_EXT_MCFORMATS");

    switch (FileInfos.channels)
    {
        case 1 : Format = AL_FORMAT_MONO16; break;
        case 2 : Format = AL_FORMAT_STEREO16; break;
    /*
        if (IsMultiChannelSupported == AL_TRUE)
        {
			case 4 : Format = alGetEnumValue("AL_FORMAT_QUAD16");  break;
			case 6 : Format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
			case 7 : Format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
			case 8 : Format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
        }
	*/
        default :
            std::cerr << "Format audio non supporte (plus de 2 canaux)" << std::endl;
            return 0;
    }

    // Création du tampon OpenAL
    ALuint Buffer;
    alGenBuffers(1, &Buffer);

    // Remplissage avec les échantillons lus
    alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

    // Vérification des erreurs
    if (alGetError() != AL_NO_ERROR)
    {
        std::cerr << "Impossible de remplir le tampon OpenAL avec les echantillons du fichier audio" << std::endl;
        return 0;
    }

    return Buffer;
}

////////////////////////////////////////////////////////////
/// Ferme proprement OpenAL
///
////////////////////////////////////////////////////////////
void shutdownOpenAL()
{
    // Récupération du contexte et du device
    ALCcontext* Context = alcGetCurrentContext();
    ALCdevice*  Device  = alcGetContextsDevice(Context);

    // Désactivation du contexte
    alcMakeContextCurrent(NULL);

    // Destruction du contexte
    alcDestroyContext(Context);

    // Fermeture du device
    alcCloseDevice(Device);
}

};

#endif /* AUDIO_H_ */
