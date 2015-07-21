/*
 * Protocole.h
 *
 *  Created on:
 *      Author: cephise
 */

#ifndef PROTOCOLE_H_
#define PROTOCOLE_H_

#include "Client.h"
#include "AbstractProtocole.h"
#include "../include/Callback.h" 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Protocole: public AbstractProtocole
{

public:

    Protocole(string host, string port, Callback* callback);

    //callback pour client
    void rcvData(char* data);//callback lorsque Client recoit un message

    //méthodes générales
    void envoyerMessage(vector<std::string>* message, int destinataire = 0);//envoie de message au serveur destinataire = pour broadcast
    void envoyerMessage(vector<std::string>* message, vector<int> destinataire);//envoie de message au serveur

    //méthodes spécifiques
    void creationCompte(string pseudo, string pwd);
    void connexion(string pseudo = "dadu", string pwd = "dadu");
    void deconnexion(string info = "1,dadu,1000,500,1,5,50,23,22,21,22,23,24,25", string competence = "", string objsac = "", string objEquip = "", string texture = "texture_tshirt1.png");
    void requeteMJ(string message);
    void verificationErreur(int sourceattaque, string message);
    void VerificationInfo(int joueur, string info);
    void VerificationObjetEquipement(int joueur, string equip);
    void setEtat(string nom, int etat);
    void getEtat(string nom);
    void setTexture(string texture);//mettre les texture separé par un !

public:
    //Ajouter par Romain
    void calculReception(float frameDeltaTime);
    Callback* getCallback();

protected:

    void messageGeneral(char* data);//gere les message general et appel le callback.recevoirmessage
    void gererConnexion(char* data);//gere toutes les requete specifique concernant la connexion
    void gererDeconnexion(char* data);//gere toutes les requete specifique concernant la déconnexion
    void gererVerification(char* data);
    void gererEtatAnimation(char* data);
    void gererTexture(char* data);
    vector<std::string> split(const char* data, char separateur = ';'); //split le message en fonction du separateur

private:

    Client m_client;
    Callback* m_callback;
    int m_identifiant;

};

#endif /* PROTOCOLE_H_*/
