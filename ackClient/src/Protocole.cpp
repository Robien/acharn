/*
 * Protocole.h
 *
 *  Created on:
 *      Author: cephise
 */

#include "Protocole.h"

using namespace std;

Protocole::Protocole(string host, string port, Callback* callback) :
    m_client(host.c_str(), port.c_str(), this)
{
    m_callback = callback;
}

//-->C//appeler par Client lorsqu'il recois un message
void Protocole::rcvData(char* data)//doit comprendre au moins 2caractere
{
    //verification de identifiant (deux premier caractere)
    if (data[0] == 'm' && (data[1] == 'g' || data[1] == 'm'))//messages géneraux
    {
        messageGeneral(data);
    }
    else if (data[0] == 'c')//message concernant la connexion
    {
        gererConnexion(data);
    }
    else if (data[0] == 'd' && data[1] == 'c')// message de deconnexion
    {
        gererDeconnexion(data);
    }
    else if (data[0] == 'v')//message concernant une verification
    {
        gererVerification(data);
    }
    else if (data[0] == 'e')//message concernant une verification
    {
        gererEtatAnimation(data);
    }

    //-->C//mettre l'analyse de data
}

void Protocole::messageGeneral(char* data)
{
    vector<std::string> information = split(data);
    int source = converint(information[1]);
    if (data[1] == 'g')
    {
        int destination = converint(information[2]);
        if (destination == m_identifiant || destination == 0) //verification que le message nous est bien adressé
        {
            vector<std::string> message;
            for (unsigned int i = 3; i < information.size(); i++)
            {
                message.push_back(information.at(i));
            }

            m_callback->recevoirMessage(message, source);
        }
    }
    else
    {
        vector<std::string> message;
        for (unsigned int i = 3; i < information.size(); i++)
        {
            message.push_back(information.at(i));
        }

        m_callback->recevoirMessage(message, source);
    }
}

//message concernant les connexions
void Protocole::gererConnexion(char* data)
{
    vector<std::string> information = split(data);
    if (information[0] == "ca")//connexion reussies(format de la trame attendue: 'ca,id,initialisateur,caracteristiquejoueur')
    {
        m_identifiant = converint(information[1]);
        int init = converint(information[2]);
        string info = information[3];

        m_callback->connexionReussie(init, info);
    }
    else if (information[0] == "cr")//connexion refusée(format de la trame attendue: 'cr,messagederreur')
    {
        string erreur = information[1];

        m_callback->connexionRefusee(erreur);
    }
    else if (information[0] == "cn")//connexion recuperation des données d'un personnage(format de la trame attendue: 'cn,id,init,caracteristique')
    {
        int id = converint(information[1]);
        int init = converint(information[2]);
        string info = information[3];
        m_callback->connexionNewJoueur(id, init, info);
    }
    else if (information[0] == "cv")//creation de compte(format de la trame attendue: 'cv;message')
    {
        string msg = information[1];
        if (msg == "ok")
        {
            m_callback->retourCreation(true);
        }
        else
        {
            m_callback->retourCreation(false, msg);
        }
    }
    else if (information[0] == "cs")//recuperation competence(format de la trame attendue: 'cs;competence')
    {
        vector<std::string> comp = split(information[1].c_str(), '!');
        m_callback->connexionCompetence(comp);
    }
    else if (information[0] == "co")//recuperation objet sac(format de la trame attendue: 'co;objet')
    {
        vector<std::string> comp = split(information[1].c_str(), '!');
        m_callback->connexionObjetSac(comp);
    }
    else if (information[0] == "ce")//recuperation objet equipement(format de la trame attendue: 'ce;id;equipment')
    {
        int id = converint(information[1]);
        vector<std::string> comp = split(information[2].c_str(), '!');
        m_callback->connexionObjetEquipement((id == m_identifiant ? 0 : id), comp);
    }
    else if (information[0] == "ct")//recuperation objet equipement(format de la trame attendue: 'ct;id;texture')
    {
        std::cout << "0 : " << information[0] << " 1 : " << information[1] << " 2 : " << information[2] << std::endl;
        int id = converint(information[1]);
        vector<std::string>* texture = new vector<string> (split(information[2].c_str(), '!'));
        m_callback->connexionTexture((id == m_identifiant ? 0 : id), texture);

    }
}

//message concernant les déconnexions
void Protocole::gererDeconnexion(char* data)
{
    vector<std::string> information = split(data);
    int source = converint(information[1]);
    m_callback->deconnexionJoueur(source);
}

void Protocole::gererVerification(char* data)
{
    vector<std::string> information = split(data);
    if (information[0] == "vi")//verification info d'un joueur
    {
        m_callback->verificationInfo(converint(information[1]));

    }
    else if (information[0] == "ve")//verification equipement d'un joueur
    {
        m_callback->verificationObjetEquipement(converint(information[1]));
    }
}

void Protocole::gererEtatAnimation(char* data)
{
    vector<std::string> information = split(data);
    if (information[0] == "ei")//verification equipement d'un joueur
    {
        m_callback->isEtat(information[1], converint(information[2]));
    }
}

void Protocole::gererTexture(char* data)
{
    vector<std::string> information = split(data);
    int id = converint(information[1]);
    if (information[0] == "ts") //verification equipement d'un joueur
    {
        vector<std::string>* texture = new vector<string> (split(information[2].c_str(), '!'));
        m_callback->setTexture((id == m_identifiant ? 0 : id), texture);
    }

}

//-->C// Envoie des données au serveur pour un ou tout les joueurs
void Protocole::envoyerMessage(vector<std::string>* message, int destinataire)
{
    //debug//cout <<"msg general"<<endl;

    string chaine = "mg;"; //message non verifié id src et dst= (0 si broadcast)

    chaine += converstr(m_identifiant) + ";";
    chaine += converstr(destinataire);

    for (unsigned int i = 0; i < message->size(); i++)
    {
        chaine += ";" + message->at(i);
    }

    const char* request = NULL;
    request = chaine.c_str();
    m_client.envoyer(request);

}

//-->C// Envoie des données au serveur pour les joueur indiqués dans la liste
void Protocole::envoyerMessage(vector<std::string>* message, vector<int> destinataire)//envoie de message au serveur
{
    if (destinataire.size() > 0)
    {
        string chaine = "mm;"; //message non verifié id src et dst= (0 si broadcast)
        chaine += converstr(m_identifiant) + ";";
        chaine += converstr(destinataire.at(0));
        for (unsigned int i = 1; i < destinataire.size(); i++)
        {
            chaine += "," + converstr(destinataire.at(i));
        }

        for (unsigned int i = 0; i < message->size(); i++)
        {
            chaine += ";" + message->at(i);
        }

        const char* request = NULL;
        request = chaine.c_str();
        m_client.envoyer(request);
    }
    else
        cout << "Erreur message multiple: Il faut au moins un destinataire" << endl;

}

//méthodes spécifiques
void Protocole::creationCompte(string pseudo, string pwd)
{
    cout << "Ceation d'un compte" << endl;//debug//

    string chaine = "cc;";
    chaine += pseudo + ";";
    chaine += pwd;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);

}

void Protocole::connexion(string pseudo, string pwd)
{
    cout << "Connexion" << endl;//debug//

    string chaine = "cx;"; //connexion client id src = (inconnu) dst= (serveur)

    chaine += pseudo + ";";
    chaine += pwd;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);

}

void Protocole::deconnexion(string info, string competence, string objsac, string objEquip, string texture)
{
    cout << "deconnexion" << endl;//debug//
    string chaine = "dc;";
    chaine += converstr(m_identifiant) + ";";
    chaine += info + ";";
    chaine += competence + ";";
    chaine += objsac + ";";
    chaine += objEquip + ";";
    chaine += texture;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);

}

void Protocole::requeteMJ(string message)
{
    cout << "requete MJ" << endl;//debug//
    string chaine = "mj;";
    chaine += converstr(m_identifiant) + ";";
    chaine += message;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);
}

void Protocole::verificationErreur(int sourceattaque, string message)
{
    cout << "erreur verification" << endl;//debug//
    string chaine = "ma;";
    chaine += converstr(m_identifiant) + ";";
    chaine += converstr(sourceattaque) + ";";
    chaine += message;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);
}

void Protocole::VerificationInfo(int joueur, string info)
{
    cout << "requete verif info" << endl;//debug//
    string chaine = "vi;";
    chaine += converstr(m_identifiant) + ";";
    chaine += converstr(joueur) + ";";
    chaine += info;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);
}

void Protocole::VerificationObjetEquipement(int joueur, string equip)
{
    cout << "requete verif equipe" << endl;//debug//
    string chaine = "ve;";
    chaine += converstr(m_identifiant) + ";";
    chaine += converstr(joueur) + ";";
    chaine += equip;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);
}

void Protocole::setEtat(string nom, int etat)
{
    string chaine = "es;";
    chaine += converstr(m_identifiant) + ";";
    chaine += nom + ";";
    chaine += converstr(etat);

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);
}

void Protocole::getEtat(string nom)
{
    string chaine = "eg;";
    chaine += converstr(m_identifiant) + ";";
    chaine += nom;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);
}

void Protocole::setTexture(string texture)//mettre les texture separé par un !
{
    string chaine = "ts;";
    chaine += converstr(m_identifiant) + ";";
    chaine += texture;

    const char* request = NULL;
    request = chaine.c_str();

    m_client.envoyer(request);
}

void Protocole::calculReception(float frameDeltaTime)
{
    m_client.calculReception(frameDeltaTime);
}

Callback* Protocole::getCallback()
{
    return m_callback;
}

vector<std::string> Protocole::split(const char* data, char separateur)
{
    vector<std::string> resultat;
    string morceau;
    int i = 0;

    while (data[i] != '\0')
    {
        if (data[i] == separateur && i != 0 && data[i - 1] != '\\')
        {
            resultat.push_back(morceau);
            morceau.clear();
        }
        else
        {
            morceau += data[i];

        }
        i++;
    }
    resultat.push_back(morceau);

    return resultat;
}

