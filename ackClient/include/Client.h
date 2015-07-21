#ifndef DEF_CLIENT
#define DEF_CLIENT

#include <iostream>
#include <boost/asio.hpp>
#include "AbstractProtocole.h"
#include <irrlicht.h>
#include "const.h"
#include <boost/thread/thread.hpp>
#include "PointeurIntelligent.h"

using namespace std;
using boost::asio::ip::udp;

class Client
{

public:

	Client(const char* host, const char* port, AbstractProtocole* p_proto); //ProtocoleV2//
	~Client();
	int connexion();
	int information();
	int mouvement(float x, float y, float z);
	int attaque(int cible, float dg);
	int reception();
	int texte(string txt, int idr);
	void deconnexion();
	bool getconnect();
	udp::socket* getsocket();
	void setjoueurs(int nb, joueur* tabjou);
	void addjoueurs(joueur newjoueur);
	void modjoueurs(joueur modjoueur);
	void supjoueurs(int deljoueur);
	joueur *getjoueurs(int* nbjoueur);
	joueur *getjoueurs(int &nbjoueur);//j'ai surchargé avec une référence au lieu du pointeur ....

	void envoyer(const char* data); //envoie message sans l'analyser


public:
	//by Romain
	bool _threadActif;
	int debRecep();
	int finRecep();
	int calculReception(float tempsEcoule);
	std::string getMessage();
	std::string getIdMessage();
	int getMode();
	int idDeplace();
	irr::core::vector3df getCoordDeplacement();

private:

	void* ecouter(void*);
	inline float converfl(std::string txt);
	inline int converint(std::string txt);

	//getteur normaux
	int getIdMessageR(); // en cas de messages, de la part de qui ?
	std::string getMessageReception(); // le message

	//setteur
	void setFini(bool fin);

	static void* recup(Client* cli);

private:

	//AbstractProtocole* m_protocole; //ProtocoleV2//
	PointeurIntelligent<AbstractProtocole> m_protocole; //ProtocoleV2//
	boost::asio::io_service io_service; //service: io_service
	udp::socket* m_socket; //socket: s
	udp::resolver* resolver;
	udp::resolver::iterator iterator;
	bool m_connect;
	int m_id;
	joueur* m_joueurs;
	int m_nbj;

private:
	//by Romain	
	float m_tempsRestant;
	boost::thread * UnThread;
	//boost::thread * bt;
	std::string messageReception; // le message
	int idMessage; // en cas de messages, de la part de qui ?
	bool fini; // gestion du ping
	int mode; // mais que-est ce donc qu'on a reçu ?
	int idDeplacement; //qui c'est qui bouge ?
	float recevX, recevY, recevZ; // des coordonnées ?
	irr::core::vector3df coordDeplacement;

};

/* WTF?
 quarantaine

 Reception::Reception* recep; //pointeur obligatoire si je dois faire une déclaration anticipé
 //cpp

 recep = new Reception();
 delete recep;

 */

#endif

