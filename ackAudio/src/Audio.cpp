/*
 * Audio.cpp
 *
 *  Created on: 14 sept. 2010
 *      Author: David
 */

#include "Audio.h"
#include "hasard.h"
#include <memory>
#include <sndfile.h>

/* Audio::Audio()
 {

 // initialisation avec choix du device par l'utilisateur (ne marche pas)

 // Récupération des devices disponibles
 std::vector<std::string> Devices;
 getDevices(Devices);

 // On affiche la liste à l'utilisateur
 std::cout << "Veuillez choisir un device :" << std::endl << std::endl;
 for (std::size_t i = 0; i < Devices.size(); ++i)
 std::cout << "[" << i << "] " << Devices[i] << std::endl;

 // Et on le laisse choisir
 int Choice;
 std::cin >> Choice;

 // Initialisation d'OpenAL
 initOpenAL(Devices[Choice].c_str());

 } */

Audio::Audio()
{
    initOpenAL();
}

Audio::~Audio()
{
    shutdownOpenAL();
}

////////////////////////////////////////////////////////////
/// Crée une source sonore.
///
/// \param Source : identificateur de la source à créer
/// \param x : coordonnées de la source sur l'axe des x
/// \param y : coordonnées de la source sur l'axe des y
/// \param z : coordonnées de la source sur l'axe des z
/// \param loop : mode de répétition (AL_FALSE = normal, AL_TRUE = en boucle)
///
/// \return Identificateur de la source (0 si échec)
///
////////////////////////////////////////////////////////////
ALuint Audio::creerSource(ALuint Source, float x, float y, float z, ALboolean loop)
{
    // Création d'une source
    alGenSources(1, &Source);

    if (alGetError() != AL_NO_ERROR)
    {
        std::cerr << "Impossible de creer la source" << std::endl;
        return 0;
    }

    // Définition des coordonnées de la source
    alSource3f(Source, AL_POSITION, x, y, z);

    // Définition du mode de lecture de la source
    alSourcei(Source, AL_LOOPING, loop);

    /*
     // On peut modifier les propriétés de la source avant sa lecture

     // mise à jour des coordonnées de l'écouteur
     alListener3i(AL_POSITION, 0, 0, 0);

     // active la lecture en boucle
     alSourcei(Source, AL_LOOPING, AL_TRUE);

     // mise à jour des coordonnées de la source
     alSource3i(Source, AL_POSITION, 30, 30, 30);

     // permet de régler le taux d'atténuation du son de la source
     // alSourcei(Source, AL_REFERENCE_DISTANCE, 50);
     alSourcei(Source, AL_SOURCE_RELATIVE, AL_TRUE);
     */

    return Source;
}

ALuint Audio::creerBuffer(const std::string Filename)
{
    // Ouverture du fichier audio avec libsndfile
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
    {
        std::cerr << "Impossible d'ouvrir le fichier audio : " << Filename.c_str() << std::endl;
        return 1;
    }

    // Lecture du nombre d'échantillons et du taux d'échantillonnage (nombre d'échantillons à lire par seconde)
    ALsizei NbSamples = static_cast<ALsizei> (FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei> (FileInfos.samplerate);

    // Lecture des échantillons audio au format entier 16 bits signé (le plus commun)
    std::vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
    {
        std::cerr << "Impossible de lire les echantillons stockes dans le fichier audio" << std::endl;
        return 1;
    }

    // Fermeture du fichier
    int close = sf_close(File);

    if (close != 0)
    {
        std::cerr << "Impossible de fermer le fichier audio : " << Filename.c_str() << std::endl;
        return 1;
    }

    // Détermination du format en fonction du nombre de canaux
    ALenum Format;
    // bool IsMultiChannelSupported = alIsExtensionPresent("AL_EXT_MCFORMATS");

    switch (FileInfos.channels)
    {
    case 1:
        Format = AL_FORMAT_MONO16;
        break;
    case 2:
        Format = AL_FORMAT_STEREO16;
        break;
        /*
         if (IsMultiChannelSupported == AL_TRUE)
         {
         case 4 : Format = alGetEnumValue("AL_FORMAT_QUAD16");  break;
         case 6 : Format = alGetEnumValue("AL_FORMAT_51CHN16"); break;
         case 7 : Format = alGetEnumValue("AL_FORMAT_61CHN16"); break;
         case 8 : Format = alGetEnumValue("AL_FORMAT_71CHN16"); break;
         }
         */
    default:
        std::cerr << "Format audio non supporte (plus de 2 canaux)" << std::endl;
        return 1;
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
        return 1;
    }

    return Buffer;
}

ALuint Audio::creerBufferArbre()
{
    return creerBuffer("./data/sound/fallscream.wav");
}

ALuint Audio::creerBufferCascade()
{
    return creerBuffer("./data/sound/fallscream.wav");
}

ALuint Audio::creerBufferChute()
{
    return creerBuffer("./data/sound/fallscream.wav");
}

ALuint Audio::creerBufferCri()
{
    return creerBuffer("./data/sound/thunder_clap.wav");
}

ALuint Audio::creerBufferEau()
{
    return creerBuffer("./data/sound/fallscream.wav");
}

ALuint Audio::creerBufferEpee()
{
    Random rand;
    int numero = rand.generer(1, 2);
    ALuint Buffer;

    switch (numero)
    {
    case 1:
        Buffer = creerBuffer("./data/sound/knife_slash1.wav");
        break;
    case 2:
        Buffer = creerBuffer("./data/sound/knife_slash2.wav");
        break;
    default:
        std::cerr << "erreur de random en carton c'est la faute a cephise !" << std::endl;
    }

    return Buffer;
}

ALuint Audio::creerBufferMusiqueCombat()
{
    return creerBuffer("./data/sound/26.wav");
}

ALuint Audio::creerBufferMusiqueExploration()
{
    return creerBuffer("./data/sound/26.wav");
}

ALuint Audio::creerBufferNage()
{
    Random rand;
    int numero = rand.generer(1, 4);
    ALuint Buffer;

    switch (numero)
    {
    case 1:
        Buffer = creerBuffer("./data/sound/swim1.wav");
        break;
    case 2:
        Buffer = creerBuffer("./data/sound/swim2.wav");
        break;
    case 3:
        Buffer = creerBuffer("./data/sound/swim3.wav");
        break;
    case 4:
        Buffer = creerBuffer("./data/sound/swim4.wav");
        break;
    default:
        std::cerr << "erreur de random en carton c'est la faute a cephise !" << std::endl;
    }

    return Buffer;
}

ALuint Audio::creerBufferOiseau()
{
    return creerBuffer("./data/sound/thunder_clap.wav");
}

ALuint Audio::creerBufferPas()
{
    Random rand;
    int numero = rand.generer(1, 4);
    ALuint Buffer;

    switch (numero)
    {
    case 1:
        Buffer = creerBuffer("./data/sound/step1.wav");
        break;
    case 2:
        Buffer = creerBuffer("./data/sound/step2.wav");
        break;
    case 3:
        Buffer = creerBuffer("./data/sound/step3.wav");
        break;
    case 4:
        Buffer = creerBuffer("./data/sound/step4.wav");
        break;
    default:
        std::cerr << "erreur de random en carton c'est la faute a cephise !" << std::endl;
    }

    return Buffer;
}

ALuint Audio::creerBufferPorte()
{
    return creerBuffer("./data/sound/thunder_clap.wav");
}

ALuint Audio::creerBufferSaut()
{
    return creerBuffer("./data/sound/thunder_clap.wav");
}

ALuint Audio::creerBufferTonnerre()
{
    return creerBuffer("./data/sound/thunder_clap.wav");
}

ALuint Audio::creerBufferVent()
{
    return creerBuffer("./data/sound/wind.wav");
}

ALboolean Audio::addBufferToSource(ALuint Buffer, ALuint Source)
{
    ALint nbBuffers = 0;
    alGetSourcei(Source, AL_BUFFERS_QUEUED, &nbBuffers);

    if (nbBuffers == 0)
    {
        alSourcei(Source, AL_BUFFER, Buffer);
    }
    else
    {
        alSourceQueueBuffers(Source, 1, &Buffer);
    }

    return AL_TRUE;
}

ALboolean Audio::deleteBufferFromSource(ALuint Buffer, ALuint Source)
{
    alSourceUnqueueBuffers(Source, 1, &Buffer);
    return AL_TRUE;
}

ALuint Audio::playFichier(const std::string Filename, ALboolean loop)
{
    // Chargement du fichier audio
    Buffer = creerBuffer(Filename);

    if (Buffer == 0)
    {
        return EXIT_FAILURE;
    }

    // Création d'une source
    alGenSources(1, &Source);

    // On attache le tampon contenant les échantillons audio à la source
    alSourcei(Source, AL_BUFFER, Buffer);

    // Définition du mode de lecture de la source
    alSourcei(Source, AL_LOOPING, loop);

    // Lecture du son
    alSourcePlay(Source);

    return 0;
}

void Audio::playSource(ALuint Source)
{
    alSourcePlay(Source);
}

void Audio::pauseSource(ALuint Source)
{
    alSourcePause(Source);
}

void Audio::stopSource(ALuint Source)
{
    alSourceRewind(Source);
}

void Audio::updateSource(ALuint Source, float x, float y, float z)
{
    // Définition des coordonnées de la source
    alSource3f(Source, AL_POSITION, x, y, z);

}

void Audio::updateSourceLoop(ALuint Source, ALboolean loop)
{
    // Définition du mode de lecture de la source
    alSourcei(Source, AL_LOOPING, loop);
}

void Audio::deleteSource(ALuint Source)
{
    alDeleteSources(1, &Source);
}

ALfloat Audio::getTemps()
{
    ALfloat Seconds = 0.f;
    alGetSourcef(Source, AL_SEC_OFFSET, &Seconds);
    return Seconds;
}

ALint Audio::getStatus()
{
    ALint Status;
    alGetSourcei(Source, AL_SOURCE_STATE, &Status);
    return Status;
}

void Audio::finish()
{
    // Destruction du tampon
    alDeleteBuffers(1, &Buffer);

    // Destruction de la source
    alSourcei(Source, AL_BUFFER, 0);
    alDeleteSources(1, &Source);
}
