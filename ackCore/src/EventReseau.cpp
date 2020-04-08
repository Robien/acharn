/*
 * EventReseau.cpp
 *
 *  Created on: 31 juil. 2010
 *      Author: romain
 */

#include "../include/EventReseau.h"
#include "../include/ObjetManager.h"

EventReseau::EventReseau(ackCore::Appli* app) :
    _app(app)
{
    _joueur = NULL;
}

EventReseau::~EventReseau()
{
}

void EventReseau::setJoueur(MainPerso* joueur)
{
    _joueur = joueur;
}

void EventReseau::connexionReussie(int init, string info)
{
    if (_joueur)
    {
        _joueur->setInfo(info, init);
        std::cout << "Connexion réussi" << std::endl;
    }
    else
    {
        std::cout << "setInit dans ER, sans setJoueur" << std::endl;
    }
}
void EventReseau::connexionRefusee(string msgerror)
{
    std::cout << msgerror << std::endl;
    exit(0);
}

void EventReseau::connexionNewJoueur(int id, int init, string info)
{
    std::cout << "init du nouveau perso :" << init << std::endl;
    _app->nouveauJoueur(id, irr::core::vector3df(0, 0, 0), init, info);
}

void EventReseau::recevoirMessage(vector<std::string> &message, int source)
{
    if (source == 0)
    {
        std::cout << "message incohérent" << std::endl;
    }
    else
    {
        if (message[0] == "D")
        {
            _app->deplacerJoueur(source, irr::core::vector3df(std::stof(message[1]), std::stof(message[2]), std::stof(message[3])),
                    irr::core::vector3df(std::stof(message[4]), std::stof(message[5]), std::stof(message[6])));
            if (message.size() == 8)
            {
                _app->setAnim(source, (Perso::typeAnim) (std::stoi(message[7])));
            }
        }
        if (message[0] == "M")
        {
            if (message[1] == "/rand")
            {
                Random* rand = PersoManager::get()->getPersoById(source)->getRandom();
                int nb = rand->genererParJoueur(0, 100, (std::stoi(message[2])));
                std::string sourceSTR = std::to_string(source);
                _joueur->getInterface().recevoirMessageChat((sourceSTR) + ", entre 1 et 100, fait " + std::to_string(nb));
                //ça peux segfault si y'a un /rand moins d'une frame après la connexion
            }
            else
            {
                _joueur->getInterface().recevoirMessageChat("<" + PersoManager::get()->getPersoById(source)->getNom() + "> dit : " + message[1]);
            }
        }
        if (message[0] == "A")
        {
            std::vector<AbstractPerso*> perso;
            perso.push_back(_joueur);
            PersoManager::get()->getPersoById(source)->attaquer(_joueur->getDevice()->getTimer()->getTime() / 1000, message[1]);
        }
        if (message[0] == "AF")
        {
            std::vector<AbstractPerso*> perso;
            perso.push_back(_joueur);
            PersoManager::get()->getPersoById(source)->endOfIncantation(perso, _joueur->getDevice()->getTimer()->getTime() / 1000, message[1]);
            irr::core::line3df direction;
            direction.start = PersoManager::get()->getPersoById(source)->getNode()->getPosition();
            direction.end = _joueur->getNode()->getPosition();
            _joueur->pousse(direction);
        }
    }
}

void EventReseau::connexionCompetence(vector<std::string> &l_comp)
{
    for (unsigned int i = 0; i < l_comp.size(); ++i)
    {
        _joueur->newCompetence(l_comp[i]);
    }
}

void EventReseau::deconnexionJoueur(int id)
{
    _app->deletePerso(id);
}

void EventReseau::connexionObjetSac(vector<std::string> &l_objsac)
{
    AbstractObjet* objet;
    for (unsigned int i = 0; i < l_objsac.size(); i++)
    {
        if (l_objsac[i] != "")
        {
            objet = _joueur->creerObjet(l_objsac[i]);
            _joueur->mettreDansSac(objet);
        }
    }

}

void EventReseau::connexionObjetEquipement(int id, vector<std::string> &l_equip)
{
    AbstractObjet* objet;
    for (unsigned int i = 0; i < l_equip.size(); i++)
    {
        if (l_equip[i] != "")
        {
            objet = _joueur->creerObjet(l_equip[i]);
            _joueur->equiper((ObjetEquipement*) objet);
        }
    }
}

void EventReseau::connexionTexture(int id, vector<std::string>* l_texture)
{
    PersoManager::get()->connexionTexture(id, l_texture);
}

void EventReseau::verificationInfo(int id)
{

}

void EventReseau::verificationObjetEquipement(int id)
{

}

void EventReseau::isEtat(string nom, int etat)
{
    if (etat != -1)
    {
        ackCore::ObjetManager::get()->setEtat(nom, etat);
    }
    else
    {
        ackCore::ObjetManager::get()->setEtat(nom, 0);
    }
}

void EventReseau::setTexture(int id, vector<std::string>* l_texture)
{
    PersoManager::get()->connexionTexture(id, l_texture);
}
