/*
 * ServeurV4.h
 *
 *  Created on: 22 sept. 2010
 *      Author: cephise
 */

#ifndef SERVEURV4_H_
#define SERVEURV4_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <list>
#include <time.h>
#include <boost/asio.hpp>
#include <thread>

#include "SimpleIni.h"
#include "Sauvegarde.h"

using boost::asio::ip::udp;
using namespace std;

enum
{
	max_length = 1024
};

struct clients
{
	udp::endpoint pt; // adresse
	string info; //permet de donnée au nouveau
	int initRand; //init de random
};

class Serveur
{
public:
	Serveur(boost::asio::io_service& io_service, short port);
	virtual ~Serveur();
	void ecoute();

protected:
	float converfl(std::string txt);
	int converint(std::string txt);
	std::string converstr(int nb);
	std::string converstr(float nb);
	int random(int min, int max);
	int nouveauId(list<int> &prochainid, int nb_personne_co);
	void insertri(list<int>::iterator it, list<int> *prochainid, int iddeco);
	vector<std::string> split(const char* data, char separateur = ';', bool conforme = true);

protected:
	//fichier
	//bool verifierConnexion(string pseudo, string pwd);
	static void* sauvegardeTh(Sauvegarde* sauv, string info, string infoequi, string insac, string comp, string text);
	static void* sauvegardeThtex(Sauvegarde* sauv, string pseudo, string text);
private:
	std::thread* ThreadSauv; //thread sauvegarde
	//std::thread* ThreadAbs; //thread Absence

	Sauvegarde backup;
	CSimpleIniCaseA File;
	time_t timestamp;
	char buffertime[256];
	list<int> prochainid;
	map<int, clients> mapconnecte;
	udp::socket sock;// on ouverture en udp et ipv4 sur le port <port> de argv
	map<int, string> waitVerif;
	map<string, int> map_etat;
	map<int, string> waitVerifequi;
};

#endif /* SERVEURV4_H_ */
