/*
 * =====================================================================================
 *
 *       Filename:  Appli.cpp
 *
 *    Description:  implementation de Appli.h -> permet d'envoyer des mesasges à la couche graphique.
 *
 *        Version:  1.0
 *        Created:  05/04/2010 18:27:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "Appli.h"
#include "../include/Protocole.h"
#include "boost/lexical_cast.hpp"

void ackCore::Appli::nouveauJoueur(int id, irr::core::vector3df position, int init, std::string infoJoueur)
{
    _nbConnecte++;
    if (_nbConnecte == 152385)//ho-ho, ça va lancer un thread qui va se teminer tout de suite si y'a 152 385 personnes qui se connecte a acharn en même temps !
    {
        threadMaj.reset(new boost::thread(&Appli::majAll, this));
    }

    PersoManager::get()->createPerso(id, position, init, infoJoueur);

}
void ackCore::Appli::deplacerJoueur(int id, irr::core::vector3df position, irr::core::vector3df rotation)
{
    PersoManager::get()->teleportPerso(id, position, rotation);
}

ackCore::Appli::Appli()
{
    _nbConnecte = 0;
}

void ackCore::Appli::envoyerDeplacement(irr::core::vector3df position, irr::core::vector3df rot, Protocole* protocole)
{
    boost::shared_ptr<std::vector<std::string> > message(new std::vector<std::string>);
    message->push_back("D");
    message->push_back(boost::lexical_cast<std::string>((float) position.X));
    message->push_back(boost::lexical_cast<std::string>((float) position.Y));
    message->push_back(boost::lexical_cast<std::string>((float) position.Z));
    message->push_back(boost::lexical_cast<std::string>((float) rot.X));
    message->push_back(boost::lexical_cast<std::string>((float) rot.Y));
    message->push_back(boost::lexical_cast<std::string>((float) rot.Z));
    protocole->envoyerMessage(message.get());
}
void ackCore::Appli::envoyerDeplacement(irr::core::vector3df position, irr::core::vector3df rot, Protocole* protocole, Perso::typeAnim typeAnim)
{
    boost::shared_ptr<std::vector<std::string> > message(new std::vector<std::string>);
    message->push_back("D");
    message->push_back(boost::lexical_cast<std::string>((float) position.X));
    message->push_back(boost::lexical_cast<std::string>((float) position.Y));
    message->push_back(boost::lexical_cast<std::string>((float) position.Z));
    message->push_back(boost::lexical_cast<std::string>((float) rot.X));
    message->push_back(boost::lexical_cast<std::string>((float) rot.Y));
    message->push_back(boost::lexical_cast<std::string>((float) rot.Z));
    message->push_back(boost::lexical_cast<std::string>((int) typeAnim));
    protocole->envoyerMessage(message.get());
}
void ackCore::Appli::envoyerMessage(std::string mess, Protocole* protocole, int numero)
{
    boost::shared_ptr<std::vector<std::string> > message(new std::vector<std::string>);
    message->push_back("M");
    message->push_back(mess);
    message->push_back(boost::lexical_cast<std::string>(numero));

    protocole->envoyerMessage(message.get());
}
void ackCore::Appli::deletePerso(int id)
{
    PersoManager::get()->deletePerso(id);
}

void ackCore::Appli::setAnim(int id, Perso::typeAnim typeAnim)
{
    PersoManager::get()->setAnim(id, typeAnim);
}

void ackCore::Appli::majAll(Appli *app)
{
}

void ackCore::Appli::attaque(int id, Protocole* protocole)
{

    const irr::u32 time = PersoManager::get()->getMainPerso()->getDevice()->getTimer()->getTime() / 1000;
    if (!PersoManager::get()->getMainPerso()->occupe(time))
    {
        //        std::string info = PersoManager::get()->getMainPerso()->attaquer(*PersoManager::get()->getPersoById(id), time);
        std::string info = PersoManager::get()->getMainPerso()->attaquer(time);
        std::vector<std::string> infoAEnvoyer;
        infoAEnvoyer.push_back("A");
        infoAEnvoyer.push_back(info);
        protocole->envoyerMessage(&infoAEnvoyer, id);
    }

}

void ackCore::Appli::attaqueFinale(int id, Protocole* protocole)
{

    const irr::u32 time = PersoManager::get()->getMainPerso()->getDevice()->getTimer()->getTime() / 1000;
    if (!PersoManager::get()->getMainPerso()->occupe(time))
    {
        //        std::string info = PersoManager::get()->getMainPerso()->attaquer(*PersoManager::get()->getPersoById(id), time);
        std::vector<AbstractPerso*> perso;
        perso.push_back(PersoManager::get()->getPersoById(id));
        std::vector<std::string>* info = PersoManager::get()->getMainPerso()->endOfIncantation(perso, time);
        std::vector<std::string> infoAEnvoyer;
        infoAEnvoyer.push_back("AF");
        infoAEnvoyer.push_back((*info)[0]);
        protocole->envoyerMessage(&infoAEnvoyer, id);
    }

}
