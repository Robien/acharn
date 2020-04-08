/*
 * Sauvegarde.h
 *
 *  Created on: 24 sept. 2010
 *      Author: cephise
 */

#ifndef SAUVEGARDE_H_
#define SAUVEGARDE_H_

#include "SimpleIni.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;
class Sauvegarde
{
public:
	Sauvegarde();
	Sauvegarde(CSimpleIniCaseA* Filebackup);
	virtual ~Sauvegarde();
	string sauvegardeInfo(string info, string &pseudo);
	string sauvegardeInfoObjetEquipement(string infoequi, string pseudo);
	string sauvegardeInfoObjetSac(string insac, string pseudo);
	string sauvegardeInfoCompetence(string comp, string pseudo);
	string sauvegardeInfoTexture(string text, string pseudo);
	void ajouterErreur(string pseudo);
	bool verifierConnexion(string pseudo, string pwd);
	bool creerCompte(string pseudo, string pwd);
	string recupInfo(string pseudo);
	vector<string> recupComp(string pseudo);
	vector<string> recupObjetSac(string pseudo);
	vector<string> recupObjetEquipement(string pseudo);
	vector<string> recupTexture(string pseudo);
private:
	vector<std::string> split(const char* data, char separateur, bool conforme);

private:
	std::shared_ptr<boost::mutex> mutex;
    CSimpleIniCaseA* File;
};

#endif /* SAUVEGARDE_H_ */
