/*
 * EventReseau.h
 *
 *  Created on: 31 juil. 2010
 *      Author: romain
 */

#ifndef EVENTRESEAU_H_
#define EVENTRESEAU_H_

#include "Callback.h"
#include "../include/MainPerso.h"
#include "Appli.h"
#include "../include/Referenced.h"

#include <asio.hpp>

class EventReseau: public Callback, public Referenced
{
public:

    EventReseau(ackCore::Appli* app);
    virtual ~EventReseau();
    void recevoirMessage(vector<std::string> &message, int source);
    void connexionReussie(int init, string info);
    void connexionRefusee(string msgerror);
    void connexionNewJoueur(int id, int init, string info);
    void connexionCompetence(vector<std::string> &l_comp);
    void connexionObjetSac(vector<std::string> &l_objsac);
    void connexionObjetEquipement(int id, vector<std::string> &l_equip);
    void connexionTexture(int id, vector<std::string>* l_texture);
    void verificationInfo(int id);
    void verificationObjetEquipement(int id);
    void isEtat(string nom, int etat);
    void setTexture(int id, vector<std::string>* l_texture);
    void deconnexionJoueur(int id);
    void setJoueur(MainPerso* joueur);

private:

    PointeurIntelligent<MainPerso> _joueur;
    PointeurIntelligent<ackCore::Appli> _app;
};

#endif /* EVENTRESEAU_H_ */
