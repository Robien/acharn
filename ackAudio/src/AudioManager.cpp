/*
 * AudioManager.cpp
 *
 *  Created on: 26 sept. 2010
 *      Author: david
 */

#include "AudioManager.h"

AudioManager::AudioManager()
{
    std::cerr << "Création d'un objet AUDIO_MANAGER" << std::endl;
	this->_contexte = new Contexte();
}

AudioManager::~AudioManager()
{
    std::cerr << "Destruction d'un objet AUDIO_MANAGER" << std::endl;
	this->drop();
    std::cerr << "Objet AUDIO_MANAGER détruit !" << std::endl;
}

Son* AudioManager::getSon (std::string nomSon)
{
	std::map<std::string, PointeurIntelligent<Son> >::iterator it = this->_dicoSons.find(nomSon);

	if (it == this->_dicoSons.end())
	{
		std::cout << "AUDIO_MANAGER : le son : " << nomSon << " n'existe pas" << std::endl;
		return NULL;
	} else {
		return it->second;
	}
}

void AudioManager::setCoordonneesEcouteur(float x, float y, float z)
{
	this->_contexte->getEcouteur()->setCoordonnees(x, y, z);
}

void AudioManager::setCoordonneesSon(std::string nomSon, float x, float y, float z)
{
	this->getSon(nomSon)->setCoordonneesSource(x, y, z);
}

void AudioManager::addSound(std::string nomSon, Son* son)
{
	std::pair<std::map<std::string, PointeurIntelligent<Son> >::iterator,bool> elementInsere = this->_dicoSons.insert(std::pair<std::string, PointeurIntelligent<Son> >(nomSon, son));

	if (elementInsere.second == false)
	{
		std::cerr << "AUDIO_MANAGER : le son \"" << nomSon << "\" existe déjà !" << std::endl;
	} else {
		std::cerr << "AUDIO_MANAGER : le son \"" << nomSon << "\" a été ajouté à l'AUDIO_MANAGER" << std::endl;
	}
}

void AudioManager::deleteSound(std::string nomSon)
{
	this->_dicoSons.erase(nomSon);
}

void AudioManager::play(Buffer::typeSon typeSon, std::string nomSon, float x, float y, float z, bool loop, const char* DeviceName)
{
	std::map<std::string, PointeurIntelligent<Son> >::iterator it = this->_dicoSons.find(nomSon);

	if (it == this->_dicoSons.end())
	{
		Son* son = new Son(typeSon, nomSon, x, y, z, loop, DeviceName);
		this->addSound(nomSon, son);
	}

	it = this->_dicoSons.find(nomSon);
	it->second->play();
}

void AudioManager::play(std::string typeSon, std::string nomSon, float x, float y, float z, bool loop, const char* DeviceName)
{
	std::map<std::string, PointeurIntelligent<Son> >::iterator it = this->_dicoSons.find(nomSon);

	if (it == this->_dicoSons.end())
	{
		Son* son = new Son(typeSon, nomSon, x, y, z, loop, DeviceName);
		this->addSound(nomSon, son);
	}

	it = this->_dicoSons.find(nomSon);
	it->second->play();
}

void AudioManager::pause(std::string nomSon)
{
	this->getSon(nomSon)->pause();
}

void AudioManager::stop(std::string nomSon)
{
	this->getSon(nomSon)->stop();
}

void AudioManager::rewind(std::string nomSon)
{
	this->getSon(nomSon)->rewind();
}

void AudioManager::drop()
{

/*
	std::vector <ALuint> Sources;
	std::map<std::string, PointeurIntelligent<Son> >::iterator it;

	for (std::size_t i=0; i < this->_dicoSons.size(); i++)
	{
		Sources.push_back(*it[i]);
	}

	alDeleteSources(this->_dicoSons.size(), Sources);
	alDeleteBuffers(NUM_BUFFERS, buffers);
*/

	size_t nbElementsDico = this->_dicoSons.size();

	std::cerr << "Destruction de " << nbElementsDico << " objet(s) SON du dico" << std::endl;
	this->_dicoSons.clear();
	std::cerr << nbElementsDico << " objet(s) SON ont été enlevé(s) du dico" << std::endl;

	delete this->_contexte;
}
