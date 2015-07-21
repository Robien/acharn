/*
 * MainPerso.h
 *
 *  Created on: 30 juil. 2010
 *      Author: romain
 */

#ifndef MAINPERSO_H_
#define MAINPERSO_H_

#include "PersoJoueur.h"
#include "Interface.h"
#include <irrlicht.h>
#include <boost/noncopyable.hpp>
#include "../include/EventInfoPerso.h"

class MainPerso: public PersoJoueur
{
public:
	MainPerso(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* camera, Interface & interface, int init = 0);
	MainPerso(irr::IrrlichtDevice* device, irr::scene::ICameraSceneNode* camera, Interface & interface, std::string pseudo, EventInfoPerso* eip, int init = 0);
	virtual ~MainPerso();
	void appliqueVitesse(float delta);

	irr::scene::ICameraSceneNode* getCamera();
	Interface& getInterface();
	irr::IrrlichtDevice* getDevice();
	const bool isReady();

	void attaque(Perso::typeAttaque type);
	virtual void afficher(int x, int y, int z);
	void majCam();

	void setVitesseY(float vit);
	void saute();

	std::vector<int>& alloYAQuelquUn();
	void setNodeRez(irr::scene::ISceneNode* nodeRez);
	void setMetaSelector(irr::scene::IMetaTriangleSelector * metaSelector);
	void tpRez();

public:
	// surcharge des setter pour faire les evenements infoPerso
	bool gainxp(float xp);
	void setVie(float vie);
	void addNiveau();
	void setRadiation(float rad);
	void setRadiationMax(float radm);
	void setVieMax(float viem);

	//incant
public:
	void setIncant(float temps, int type, float portee);
private:
	float incantTemps;
	int incanteType;
	float Incantportee;


private:
	irr::scene::ICameraSceneNode* _camera;
	Interface & _interface;
	irr::scene::ISceneNode* _nodeRez;
	irr::scene::IMetaTriangleSelector * _metaSelector;
	PointeurIntelligent<EventInfoPerso> _eip;
};

#endif /* MAINPERSO_H_ */
