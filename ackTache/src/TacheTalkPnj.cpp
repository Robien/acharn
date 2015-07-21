/*
 * TacheTalkPnj.cpp
 *
 *  Created on: 2 nov. 2010
 *      Author: cephise
 */

#include "../include/TacheTalkPnj.h"
#include "../include/PersoManager.h"
#include "hasard.h"

//type 1= quete, 2=vendeur
TacheTalkPnj::TacheTalkPnj(float newx, float newy, float newz, int type, std::string infoJoueur):
Tache(0)
{
		_type= type;
		pnj = PersoManager::get()->newPersoNJ(_infoJoueur, type);

            Random hasard;
		    int num = hasard.generer(0,5);
		    switch (num) {
                case 0:
                    pnj->afficher(newx, newy, newz, pnj->getNom(),"data/mesh/robien2.b3d" , "data/mesh/normal_robien.jpg" , "data/mesh/texture_robien_bois.png");
                    break;
                case 1:
                    pnj->afficher(newx, newy, newz, pnj->getNom(),"data/mesh/robien2.b3d" , "data/mesh/normal_robien.jpg" , "data/mesh/texture_robien_burn.png");
                    break;
                case 2:
                    pnj->afficher(newx, newy, newz, pnj->getNom(),"data/mesh/robien2.b3d" , "data/mesh/normal_robien.jpg" , "data/mesh/texture_robien_red.png");
                    break;
                case 3:
                    pnj->afficher(newx, newy, newz, pnj->getNom(),"data/mesh/robien2.b3d" , "data/mesh/normal_robien.jpg" , "data/mesh/texture_robien_weeds3.png");
                    break;
                case 4:
                    pnj->afficher(newx, newy, newz, pnj->getNom(),"data/mesh/robien2.b3d" , "data/mesh/normal_robien.jpg" , "data/mesh/texture_robien_camouflage.png");
                    break;
                case 5:
                    pnj->afficher(newx, newy, newz, pnj->getNom(),"data/mesh/robien2.b3d" , "data/mesh/normal_robien.jpg" , "data/mesh/texture_robien_simple.png");
                    break;
            }
		pnj->tourner(0,180,0);
		//perso->setInfo(_infoJoueur, _init);
		//string nom = perso->getNom();
		//PersoManager::get()->addPersoByID(_id, perso);

}

TacheTalkPnj::~TacheTalkPnj()
{
}

void TacheTalkPnj::execute()
{
	cout << pnj->talk()<< endl;
}
