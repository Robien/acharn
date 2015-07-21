/*
 * PersoManager.h
 *
 *  Created on: 19 juil. 2010
 *      Author: romain
 */

#ifndef PERSOMANAGER_H_
#define PERSOMANAGER_H_
#include "Singleton.h"
#include "Perso.h"
#include "Tache.h"
#include "PersoJoueur.h"
#include "PersoNonJoueur.h"
#include "PersoQuete.h"
#include "PersoVendeur.h"
#include "../include/PointeurIntelligent.h"

#include "irrlicht.h"

#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include "../include/MainPerso.h"

class PersoManager : public Singleton<PersoManager>
{

public:
	PersoManager()
	{
		_isDeviceDefine = false;
		_mutexTache.reset(new boost::mutex);
	}
	virtual ~PersoManager()
	{
	}
	void setDevice(irr::IrrlichtDevice* device);

	void setMainPerso(MainPerso* perso);
	MainPerso* getMainPerso();
	PersoJoueur* newPerso(std::string infoPerso);// Pas thread safe !
	PersoNonJoueur* newPersoNJ(std::string infoPerso, int typePerso);// Pas thread safe !
	void createPerso(int id, float x, float y, float z, int init, std::string infoPerso);
	void createPerso(int id, irr::core::vector3df position, int init, std::string infoPerso);
	void NSTdeletePerso(int id);
	void deletePerso(int id);
	void teleportPerso(int id, float x, float y, float z, float rx, float ry, float rz);
	void teleportPerso(int id, irr::core::vector3df position, irr::core::vector3df rotation);
	PersoJoueur* getPersoById(int id); // Pas thread safe !
	void addPersoByID(int id, PersoJoueur* perso);
	void maj();
	bool tryMaj();
	void setAnim(int id, Perso::typeAnim typeAnim);
	std::vector<int>& quiEstEnFace(Perso* perso);
	void majAttaqueAllPerso();
	void connexionTexture(int id, std::vector<std::string>* l_texture);

	void addTache(Tache* tache);

private:

	boost::shared_ptr<boost::mutex> _mutexTache;
	map<int,PointeurIntelligent<PersoJoueur> > _lesAutres; // les copains
	irr::IrrlichtDevice*  _device;
	bool _isDeviceDefine;
	std::vector<PointeurIntelligent<Tache> > _aFaire;
	bool isEnFace(irr::scene::ISceneNode* node, irr::core::vector3df position);
	PointeurIntelligent<MainPerso> _joueur;
	std::vector<int> enFace;
};

#endif /* PERSOMANAGER_H_ */
