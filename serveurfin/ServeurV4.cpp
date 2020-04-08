/*
 * ServeurV4.cpp
 *
 *  Created on: 22 sept. 2010
 *      Author: cephise
 */

#include "ServeurV4.h"

#include <thread>
using namespace std;

Serveur::Serveur(boost::asio::io_service& io_service, short port) :
    File(true, false, true), sock(io_service, udp::endpoint(udp::v4(), port)), backup(&File)
{
    File.LoadFile("sauvegarde.dadu");
    // TODO Auto-generated constructor stub

}

Serveur::~Serveur()
{
    // TODO Auto-generated destructor stub
    delete ThreadSauv;
    cout << "!!!fini" << endl;
}

void Serveur::ecoute()
{
    for (;;)
    {
        char data[max_length];
        udp::endpoint sender_endpoint;
        size_t length = sock.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
        data[length] = '\0';

        vector<std::string> donnee = split(data); //decoupage des données
        if (donnee.size() > 0)
        {
            ///////////////////////////////message general(pas d'analyse)///////////////////////////////////////
            if (donnee[0] == "mg" && donnee.size() > 3)
            {
                int source = converint(donnee[1]);
                int destination = converint(donnee[2]);

                if (destination == 0)//broadcast
                {
                    for (map<int, clients>::iterator it = mapconnecte.begin(); it != mapconnecte.end(); it++)
                    {
                        if ((*it).first != source)
                        {
                            sock.send_to(boost::asio::buffer(data, length), (*it).second.pt);//(on renvoi les même data)
                        }
                    }

                }
                else//un destinataire
                {
                    map<int, clients>::iterator it = mapconnecte.find(destination);
                    sock.send_to(boost::asio::buffer(data, length), (*it).second.pt);
                }

            }
            ///////////////////////////////message general(pas d'analyse)///////////////////////////////////////
            else if (donnee[0] == "mm" && donnee.size() > 3)
            {
                vector<std::string> destinataire = split(donnee[2].c_str(), ',', false); //decoupage des données

                if (destinataire.size() > 0)//broadcast
                {
                    map<int, clients>::iterator it;
                    for (unsigned int i = 0; i < destinataire.size(); i++)//pour tout les destinataire
                    {
                        int dest = converint(destinataire.at(i));
                        it = mapconnecte.find(dest);
                        sock.send_to(boost::asio::buffer(data, length), (*it).second.pt);
                    }

                }
                else//un destinataire
                {
                    timestamp = time(NULL);
                    strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X.", localtime(&timestamp));
                    std::cout << "(" << buffertime << ")**Erreur: Message multiple: nb destinataire <=0 " << "(ip: " << sender_endpoint << ")" << std::endl;
                }

            }
            //////////////////////////////////////message spécial:requete mj////////////////////////////////////////////////
            else if (donnee[0] == "mj" && donnee.size() > 2)
            {
                std::cout << "(" << buffertime << ")**Requete MJ: (id: " << donnee[1] << ") " << donnee[2] << "(ip: " << sender_endpoint << ")" << std::endl;
            }
            //////////////////////////////////////message spécial: verification attaque erreur////////////////////////////////////////////////
            else if (donnee[0] == "ma" && donnee.size() > 3)
            {
                std::cout << "(" << buffertime << ")**Erreur attaque: attaque de id: " << donnee[2] << " " << donnee[3] << " detecté par id: " << donnee[1] << "(ip: " << sender_endpoint << ")"
                        << std::endl;
            }
            //////////////////////////////////////message spécial: Setter etat      ////////////////////////////////////////////////
            else if (donnee[0] == "es" && donnee.size() > 3)
            {
                int source = converint(donnee[1]);

                map_etat[donnee[2]] = converint(donnee[3]);

                string chaine = "ei;";
                chaine += donnee[2] + ";";
                chaine += donnee[3];

                const char* answer = chaine.c_str();
                for (map<int, clients>::iterator it = mapconnecte.begin(); it != mapconnecte.end(); it++)
                {
                    if ((*it).first != source)
                    {
                        sock.send_to(boost::asio::buffer(answer, std::strlen(answer)), (*it).second.pt);
                    }
                }
            }
            //////////////////////////////////////message spécial: Getter etat      ////////////////////////////////////////////////
            else if (donnee[0] == "eg" && donnee.size() > 2)
            {
                int etat;
                map<string, int>::iterator it = map_etat.find(donnee[2].c_str());
                if (it == map_etat.end())
                {
                    etat = -1;
                    etat = it->second;
                }
                else
                {
                    etat = it->second;
                }

                string chaine = "ei;";
                chaine += donnee[2] + ";";
                chaine += etat;

                const char* answer = chaine.c_str();
                sock.send_to(boost::asio::buffer(answer, std::strlen(answer)), sender_endpoint);

            }
            //////////////////////////////////////message spécial: Getter etat      ////////////////////////////////////////////////
            else if (donnee[0] == "ts" && donnee.size() > 2)
            {
                int source = converint(donnee[1]);
                        std::cout << "source : " << source << std::endl;
                //sauvegarde
                map<int, clients>::iterator it = mapconnecte.find(source);
                vector<string> info = split((*it).second.info.c_str(), ',', false);
                string pseudo = info[1];
                ThreadSauv = new std::thread(&Serveur::sauvegardeThtex, &backup, pseudo, donnee[2]);
                //

                string chaine4 = "ct;";
                chaine4 += converstr(source) + ";";
                chaine4 += donnee[2];
                const char* answer4 = chaine4.c_str();
                for (map<int, clients>::iterator it = mapconnecte.begin(); it != mapconnecte.end(); it++)
                {
                    if ((*it).first != source)
                    {
                        sock.send_to(boost::asio::buffer(answer4, std::strlen(answer4)), (*it).second.pt);
                    }
                }

            }
            //////////////////////////////////////message spécial: verification info////////////////////////////////////////////////
            else if (donnee[0] == "vi" && donnee.size() > 3)
            {
                int idverifby = converint(donnee[1]);
                int idwhoisverif = converint(donnee[2]);

                map<int, string>::iterator it = waitVerif.find(idwhoisverif);
                if (it != waitVerif.end())
                {
                    string info = "";
                    info += (*it).second[0];
                    int nb = converint(info.c_str());
                    info += donnee[3];
                    if ((*it).second == info)
                    {
                        cout << "debug--verification correcte" << endl;
                    }
                    else if (nb < 2 && waitVerif.size() > 1)//deuxieme verification
                    {
                        //recherche d'un id different de idverifby
                        map<int, clients>::iterator iter = mapconnecte.begin();
                        while (iter != mapconnecte.end() && (*iter).first == idverifby)
                        {
                            iter++;
                        }
                        string chaine = "ve;" + converstr(idwhoisverif);
                        const char* newverif = chaine.c_str();
                        sock.send_to(boost::asio::buffer(newverif, std::strlen(newverif)), (*iter).second.pt);//(on renvoi les même data)
                        (*it).second[0] = converstr(nb + 1)[0];
                        //ajouterErreur(pseudo???);
                    }
                    else
                    {
                        std::cout << "(" << buffertime << ")**Erreur Verification info: info de id: " << donnee[2] << " = " << info << " Differente de id: " << donnee[1] << " = " << (*it).second
                                << "(ip: " << sender_endpoint << ")" << std::endl;
                        //ajouterErreur(pseudo???);
                    }
                }
            }
            //////////////////////////////////////message spécial: verification info equipement////////////////////////////////////////////////
            else if (donnee[0] == "ve" && donnee.size() >= 4)
            {
                int idverifby = converint(donnee[1]);
                int idwhoisverif = converint(donnee[2]);

                map<int, string>::iterator it = waitVerifequi.find(idwhoisverif);
                if (it != waitVerifequi.end())
                {
                    string info = "";
                    info += (*it).second[0];
                    int nb = converint(info.c_str());
                    info += donnee[3];

                    if ((*it).second == info)
                    {
                        cout << "debug--verification correcte" << endl;
                    }
                    else if (nb < 2 && waitVerifequi.size() > 1)//deuxieme verification
                    {
                        //recherche d'un id different de idverifby
                        map<int, clients>::iterator iter = mapconnecte.begin();
                        while (iter != mapconnecte.end() && (*iter).first == idverifby)
                        {
                            iter++;
                        }
                        string chaine = "ve;" + converstr(idwhoisverif);
                        const char* newverif = chaine.c_str();
                        sock.send_to(boost::asio::buffer(newverif, std::strlen(newverif)), (*iter).second.pt);//(on renvoi les même data)
                        (*it).second[0] = converstr(nb + 1)[0];
                        //ajouterErreur(pseudo???);
                    }
                    else
                    {
                        std::cout << "(" << buffertime << ")**Erreur Verification info: info de id: " << donnee[2] << " = " << info << " Differente de id: " << donnee[1] << " = " << (*it).second
                                << "(ip: " << sender_endpoint << ")" << std::endl;
                        //ajouterErreur(pseudo???);
                    }
                }

            }
            ////////////////////////////////////message special: concernant la connexion////////////////////////////////////
            else if (donnee[0] == "cx" && donnee.size() >= 3)
            {
                string erreur;
                if (backup.verifierConnexion(donnee[1], donnee[2]))
                {
                    //trouver id non utilisé
                    int newid = nouveauId(prochainid, (int) mapconnecte.size());
                    int rando = random(123, 100000);
                    string infojoueur = backup.recupInfo(donnee[1]);
                    vector<string> competences = backup.recupComp(donnee[1]);
                    vector<string> sac = backup.recupObjetSac(donnee[1]);
                    vector<string> equipement = backup.recupObjetEquipement(donnee[1]);
                    vector<string> texture = backup.recupTexture(donnee[1]);

                    if (infojoueur == "")
                    {
                        erreur = "Erreur: recuperation des données, login(" + donnee[1] + ")";
                    }

                    clients newclient;
                    newclient.pt = sender_endpoint;
                    newclient.initRand = rando;
                    newclient.info = infojoueur;
                    mapconnecte.insert(pair<int, clients> (newid, newclient));

                    //conversion int en string
                    string nouveauid, initialisateur;
                    nouveauid = converstr(newid);
                    initialisateur = converstr(rando);

                    timestamp = time(NULL);
                    strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
                    std::cout << "(" << buffertime << ")--Connexion: (id: " << nouveauid << ") pseudo: " << donnee[1] << " (ip: " << sender_endpoint << ")" << std::endl;

                    //Pour le nouveau joueur
                    //connexion reussi
                    string chaine = "ca;";
                    chaine += nouveauid + ";";
                    chaine += initialisateur + ";";
                    chaine += infojoueur;

                    const char* answer = chaine.c_str();
                    sock.send_to(boost::asio::buffer(answer, std::strlen(answer)), sender_endpoint);

                    //competence
                    if (!competences.empty())
                    {
                        string chaine4 = "cs;";
                        chaine4 += competences[0];
                        for (int j = 1; j < (int) competences.size(); j++)
                        {
                            chaine4 += "!" + competences[j];
                        }
                        const char* answer4 = chaine4.c_str();
                        sock.send_to(boost::asio::buffer(answer4, std::strlen(answer4)), sender_endpoint);
                    }

                    if (!sac.empty())
                    {
                        string chaine4 = "co;";
                        chaine4 += sac[0];
                        for (int j = 1; j < (int) sac.size(); j++)
                        {
                            chaine4 += "!" + sac[j];
                        }
                        const char* answer4 = chaine4.c_str();
                        sock.send_to(boost::asio::buffer(answer4, std::strlen(answer4)), sender_endpoint);
                    }

                    //pour les autres joueur
                    string chaine2 = "cn;";
                    chaine2 += nouveauid + ";";
                    chaine2 += initialisateur + ";";
                    chaine2 += infojoueur;

                    const char* answer2 = chaine2.c_str();

                    for (map<int, clients>::iterator it = mapconnecte.begin(); it != mapconnecte.end(); it++)
                    {
                        if ((*it).first != newid)
                        {
                            sock.send_to(boost::asio::buffer(answer2, std::strlen(answer2)), (*it).second.pt);

                            //on dit qui etait deja connecté avant son arrivée
                            string chaine3 = "cn;";
                            chaine3 += converstr((*it).first) + ";";
                            chaine3 += converstr((*it).second.initRand) + ";";
                            chaine3 += (*it).second.info;
                            const char* answer3 = chaine3.c_str();
                            sock.send_to(boost::asio::buffer(answer3, std::strlen(answer3)), sender_endpoint);

                            vector<string> inf = split((*it).second.info.c_str(), ',', false);
                            vector<string> textu = backup.recupTexture(inf[1]);
                            string chaine5 = "ct;" + converstr((*it).first) + ";";
			    if (textu.size() > 0)
			    {
				    chaine5 += textu[0];
				    for (int j = 1; j < (int) textu.size(); j++)
				    {
					    chaine5 += "!" + textu[j];
				    }
			    }
                            const char* answer5 = chaine5.c_str();
                            sock.send_to(boost::asio::buffer(answer5, std::strlen(answer5)), sender_endpoint);
                        }
                    }

                    if (!equipement.empty())
                    {
                        string chaine4 = "ce;" + nouveauid + ";";
                        chaine4 += equipement[0];
                        for (int j = 1; j < (int) equipement.size(); j++)
                        {
                            chaine4 += "!" + equipement[j];
                        }
                        const char* answer4 = chaine4.c_str();
                        for (map<int, clients>::iterator it = mapconnecte.begin(); it != mapconnecte.end(); it++)
                        {
                            sock.send_to(boost::asio::buffer(answer4, std::strlen(answer4)), (*it).second.pt);//envoie a tous
                        }
                    }

                    if (!texture.empty())
                    {
                        string chaine4 = "ct;" + nouveauid + ";";
                        chaine4 += texture[0];
                        for (int j = 1; j < (int) texture.size(); j++)
                        {
                            chaine4 += "!" + texture[j];
                        }
                        const char* answer4 = chaine4.c_str();
                        for (map<int, clients>::iterator it = mapconnecte.begin(); it != mapconnecte.end(); it++)
                        {
                            sock.send_to(boost::asio::buffer(answer4, std::strlen(answer4)), (*it).second.pt);//envoie a tous
                        }
                    }

                }
                else
                {
                    erreur = "Erreur: Echec de verification ou déja connecté, verifier votre login(" + donnee[1] + ")/password";
                }

                if (!erreur.empty())//echec de connexion
                {
                    timestamp = time(NULL);
                    strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
                    std::cout << "(" << buffertime << ")**" << erreur << "(ip: " << sender_endpoint << ")" << endl;

                    string chaine5 = "cr;" + erreur;

                    const char* answer5 = chaine5.c_str();
                    sock.send_to(boost::asio::buffer(answer5, std::strlen(answer5)), sender_endpoint);
                }

            }
            ////////////////////////////////////message special: concernant la creation d'un compte////////////////////////////////////
            else if (donnee[0] == "cc" && donnee.size() >= 3)
            {
                string erreur;
                string chaine;
                if (backup.creerCompte(donnee[1], donnee[2]))
                {
                    timestamp = time(NULL);
                    strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
                    std::cout << "(" << buffertime << ")--Creation compte login: " << donnee[1] << "(ip: " << sender_endpoint << ")" << endl;
                    chaine = "cv;ok";

                }
                else
                {
                    timestamp = time(NULL);
                    strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
                    erreur = "Erreur: Echec Creation Compte: login(" + donnee[1] + ") deja utilisé";
                    std::cout << "(" << buffertime << ")**" << erreur << "(ip: " << sender_endpoint << ")" << endl;
                    chaine = "cv;" + erreur;
                }
                const char* answer = chaine.c_str();
                sock.send_to(boost::asio::buffer(answer, std::strlen(answer)), sender_endpoint);

            }
            ////////////////////////////////////message special: concernant la déconnexion////////////////////////////////////
            else if (donnee[0] == "dc" && donnee.size() >= 6)
            {
                int source = converint(donnee[1]);

                map<int, clients>::iterator itdeco = mapconnecte.find(source);
                if (itdeco != mapconnecte.end()) //si cette personne a ete trouvé
                {
                    mapconnecte.erase(itdeco);
                    insertri(prochainid.begin(), &prochainid, source);
                    //sauvegarde threadé
                    string info = donnee[2];
                    string comp = donnee[3];
                    string insac = donnee[4];
                    string infoequi = donnee[5];
                    string text = donnee[6];

                    ThreadSauv = new std::thread(std::bind(Serveur::sauvegardeTh, &backup, info, infoequi, insac, comp, text));

                    //prevenir les joueurs de la deconnexion
                    timestamp = time(NULL);
                    strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
                    std::cout << "(" << buffertime << ")--Deconnexion id: " << source << endl;

                    if (mapconnecte.size() > 0)// verification
                    {
                        map<int, clients>::iterator iter = mapconnecte.begin();
                        string chaine = "vi;" + converstr(source);
                        const char* newverif = chaine.c_str();
                        sock.send_to(boost::asio::buffer(newverif, std::strlen(newverif)), (*iter).second.pt);//(on renvoi les même data)
                        waitVerif.insert(pair<int, string> (source, '1' + donnee[2]));
                        chaine = "ve;" + converstr(source);
                        newverif = chaine.c_str();
                        sock.send_to(boost::asio::buffer(newverif, std::strlen(newverif)), (*iter).second.pt);//(on renvoi les même data)
                        waitVerifequi.insert(pair<int, string> (source, '1' + donnee[3]));
                    }

                    for (map<int, clients>::iterator it = mapconnecte.begin(); it != mapconnecte.end(); it++)
                    {
                        sock.send_to(boost::asio::buffer(data, length), (*it).second.pt);//(même data)
                    }

                }
                else
                {
                    timestamp = time(NULL);
                    strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
                    std::cout << "(" << buffertime << ")**Erreur: tentative de Deconnexion d'une personne inconnu" << "(ip: " << sender_endpoint << ")" << endl;
                }
            }
            /////////////////////////////Erreur/////////////////////////////////////////
            else
            {
                timestamp = time(NULL);
                strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
                std::cout << "(" << buffertime << ")**Erreur: type de trame inconnu ou non conforme, type: " << donnee[0] << "(ip: " << sender_endpoint << ")" << std::endl;
            }

        }
        else
        {
            timestamp = time(NULL);
            strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
            std::cout << "(" << buffertime << ")**Erreur: trame non conforme" << "(ip: " << sender_endpoint << ")" << std::endl;
        }

    }
}

float Serveur::converfl(string txt) //convert un string en float
{
    return std::stof(txt);
}

int Serveur::converint(string txt)//convert un string en int
{
    return std::stoi(txt);
}

std::string Serveur::converstr(int nb)//convert en string un int
{
    return std::to_string(nb);
}

std::string Serveur::converstr(float nb)//convert en string un float
{
    return std::to_string(nb);
}

int Serveur::random(int min, int max)
{
    boost::mt19937 rng;
    boost::uniform_int<> six(min, max);
    rng.seed(std::time(0));
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(rng, six);
    return die();
}

int Serveur::nouveauId(list<int> &prochainid, int nb_personne_co)
{
    int idn;
    if (prochainid.empty())
    {
        idn = nb_personne_co + 1;
    }
    else
    {
        idn = prochainid.front();
        prochainid.pop_front();
    }

    return idn;
}

void Serveur::insertri(list<int>::iterator it, list<int> *prochainid, int iddeco)
{ // insère dans une liste trié
    if (it == prochainid->end() || (*it) >= iddeco)
    {
        prochainid->insert(it, iddeco);
    }
    else
    {
        it++;
        list<int>::iterator idt = it;
        insertri(idt, prochainid, iddeco);
    }
}

vector<std::string> Serveur::split(const char* data, char separateur, bool conforme)
{

    vector<std::string> resultat;

    //verification de conformitée: au moins deux caracteres puis un separateur
    if ((data[0] != '\0' && data[0] != separateur) && ((!conforme) || (data[0] != '\0' && data[1] != '\0' && data[2] != '\0' && data[2] == separateur)))
    {

        string morceau;
        int i = 0;

        while (data[i] != '\0')
        {
            if (data[i] == separateur && data[i - 1] != '\\')
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
    }//sinon retour d'un vecteur vide
    return resultat;
}

void* Serveur::sauvegardeTh(Sauvegarde* sauv, string info, string infoequi, string infosac, string comp, string text)
{
    char bufferti[256];
    time_t tistamp;
    string pseudo;
    string erreur = sauv->sauvegardeInfo(info, pseudo);
    if (erreur != "")
    {
        tistamp = time(NULL);
        strftime(bufferti, sizeof(bufferti), "%d/%m/%Y - %X", localtime(&tistamp));
        std::cout << "(" << bufferti << ")**" << erreur << "(joueur: " << pseudo << ")" << endl;
    }
    erreur = sauv->sauvegardeInfoObjetSac(infosac, pseudo);
    if (erreur != "")
    {
        tistamp = time(NULL);
        strftime(bufferti, sizeof(bufferti), "%d/%m/%Y - %X", localtime(&tistamp));
        std::cout << "(" << bufferti << ")**" << erreur << "(joueur: " << pseudo << ")" << endl;
    }
    erreur = sauv->sauvegardeInfoObjetEquipement(infoequi, pseudo);
    if (erreur != "")
    {
        tistamp = time(NULL);
        strftime(bufferti, sizeof(bufferti), "%d/%m/%Y - %X", localtime(&tistamp));
        std::cout << "(" << bufferti << ")**" << erreur << "(joueur: " << pseudo << ")" << endl;
    }
    erreur = sauv->sauvegardeInfoCompetence(comp, pseudo);
    if (erreur != "")
    {
        tistamp = time(NULL);
        strftime(bufferti, sizeof(bufferti), "%d/%m/%Y - %X", localtime(&tistamp));
        std::cout << "(" << bufferti << ")**" << erreur << "(joueur: " << pseudo << ")" << endl;
    }
    erreur = sauv->sauvegardeInfoTexture(text, pseudo);
    if (erreur != "")
    {
        tistamp = time(NULL);
        strftime(bufferti, sizeof(bufferti), "%d/%m/%Y - %X", localtime(&tistamp));
        std::cout << "(" << bufferti << ")**" << erreur << "(joueur: " << pseudo << ")" << endl;
    }

    return NULL;
}

void* Serveur::sauvegardeThtex(Sauvegarde* sauv, string pseudo, string text)
{
    char bufferti[256];
    time_t tistamp;
    string erreur = sauv->sauvegardeInfoTexture(text, pseudo);
    if (erreur != "")
    {
        tistamp = time(NULL);
        strftime(bufferti, sizeof(bufferti), "%d/%m/%Y - %X", localtime(&tistamp));
        //refaire//std::cout << "(" << bufferti << ")**" << erreur << "(ip: " << sender_endpoint << ")" << endl;
    }
    return NULL;
}
