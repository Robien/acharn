#ifndef DEF_EVENTR
#define DEF_EVENTR
/*
 * =====================================================================================
 *
 *       Filename:  EventReceiver.h
 *
 *    Description:  traite les évenements
 *
 *        Version:  1.0
 *        Created:  14/05/2010 22:00:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <irrlicht.h>
#include "Interface.h"
#include <asio.hpp>
#include "../include/MainPerso.h"
#include "Appli.h"
#include "../include/PointeurIntelligent.h"

using namespace irr;
using namespace std;
using namespace gui;

class EventReceiver: public IEventReceiver, public Referenced
{
public:

	EventReceiver(MainPerso & joueur, ackCore::Appli & app, Protocole* protocole);
	EventReceiver(const EventReceiver&) = delete;

	virtual bool OnEvent(const SEvent& event); //traite les évenements
	void majCam(float delta); //met a jours la position de la camera
	void majCurseur();
	void majPerso(float delta);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;// permet de savoir si la touche donné en paramètre est appuyé

	inline bool isGuiFocus()
	{
		return _isGuiFocus;
	}

	bool avance();

private:
	bool _KeyIsDown[KEY_KEY_CODES_COUNT];
	bool _mIsPressed;
	bool _mIsPressedR;
	bool _mWheel;
	core::vector2d<f32> _positionSouris;
	float _rho, _phi, _theta;
	float _maxRho;
	core::vector3df _poscam;
	core::vector3df _exPoscam;
	core::vector3df _exPosPerso;
	core::vector3df _exRotPerso;
	bool _lock;
	bool _isOnGui;
	bool _isGuiFocus;
	bool _isCurseurVisible;
	void gestionCollisionCamera(float deltaTime);
	bool isEqual(irr::core::vector3df vec1, irr::core::vector3df vec2);

	MainPerso & _joueur;
	ackCore::Appli & _app;
	PointeurIntelligent<Protocole> _protocole;
	IGUIImage* _curseur;
	video::ITexture* _images;
	core::position2d<s32> _exPositionSouris;
};

#endif
