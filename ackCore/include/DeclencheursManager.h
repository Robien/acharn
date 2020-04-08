/*
 * DeclancheursManager.h
 *
 *  Created on: 7 sept. 2010
 *      Author: romain & cephise ;p
 */

#ifndef DECLANCHEURSMANAGER_H_
#define DECLANCHEURSMANAGER_H_

#include "Singleton.h"
#include "Declencheurs.h"
#include <vector>
#include <thread>
#include <mutex>
#include "../include/PointeurIntelligent.h"
#include "../include/MainPerso.h"
#include "../include/TacheStopAnim.h"

class DeclencheursManager: public Singleton<DeclencheursManager>
{
public:
	DeclencheursManager();
	void setJoueur(MainPerso* joueur); // singleton => constructeur par défaut
	virtual ~DeclencheursManager();
	void addDeclancheur(Declencheurs* declancheur);
	bool majJoueur();
	void testDeclencheur();
	void startDeclencheurs();
	void stopDeclencheurs(); // ça essaye de tester encore les déclencheur une fois le jeu détruit,
	//il faut penser appeller cette methode avant d'arréter le jeu


	void setBoutonActionOn();
	void setBoutonActionOff();
	bool getBoutonAction();


private:
	std::thread * threadDeclencheur;
	static void* lanceThread();
	void addTache(Tache* tache);
	std::shared_ptr<std::mutex> _mutexTache;
	std::vector<PointeurIntelligent<Declencheurs> > _declancheurs;
	PointeurIntelligent<MainPerso> _joueur;
	std::vector<PointeurIntelligent<Tache> > _aFaire;
	bool init;

	bool boutonActionAppuye;

};

#endif /* DECLANCHEURSMANAGER_H_ */
