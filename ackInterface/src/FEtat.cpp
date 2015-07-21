/*
 * FEtat.cpp
 *
 *  Created on: 13 oct. 2010
 *      Author: stahlj
 */

#include "FEtat.h"

using std::basic_string;

FEtat::FEtat(InterfaceInfo* inter):
	Fenetre(inter,irr::core::position2d<irr::s32>(10,10),L"Fenetre d'Etat",200,75)
{
	//avatar du personnage
	avatar = inter->getGui()->addImage(irr::core::rect<irr::s32>(5,5,70,70),fenetre,-1,L"Avatar");
	string ctmp = "./data/interface/avatar.png";
	irr::io::path chemin((ctmp).c_str());
	avatar->setImage(inter->getPilote()->getTexture(chemin));

	//pseudo du personnage
	pseudo = inter->getGui()->addStaticText(L"pseudo",irr::core::rect<irr::s32 > (75,5,173,16),false,false,fenetre);
	pseudo->setTextAlignment(irr::gui::EGUIA_CENTER,irr::gui::EGUIA_CENTER);
	niveau = inter->getGui()->addStaticText(L"niveau",irr::core::rect<irr::s32 > (175,5,195,16),false,false,fenetre);
	niveau->setTextAlignment(irr::gui::EGUIA_CENTER,irr::gui::EGUIA_CENTER);

	//barre de vie
	vie = new BarreActive(inter,irr::core::position2d<irr::s32>(75,18),120,12,"font.png","vie.png",100,100,fenetre);
	//barre de pouvoir
	pouvoir = new BarreActive(inter,irr::core::position2d<irr::s32>(75,32),120,10,"font.png","pouvoir.png",100,100,fenetre);

	//barre d'experience
	experience = new BarreActive(inter,irr::core::position2d<irr::s32>(75,46),120,4,"fontXp.png","experience.png",100,100,fenetre);


	//barre de bouton de menu
	BarreBouton * barre = new BarreBouton(inter,irr::core::position2d<irr::s32>(73,55),20,14,6,1,fenetre);

	barre->setBoutonImage(1,"iconeCaracteristique.png");
	barre->getBouton(1)->getBouton()->setID(9901);
	barre->setBoutonImage(2,"iconeCompetence.png");
	barre->getBouton(2)->getBouton()->setID(9902);
	barre->setBoutonImage(3,"iconeEquipement.png");
	barre->getBouton(3)->getBouton()->setID(9903);
	barre->setBoutonImage(4,"iconeSac.png");
	barre->getBouton(4)->getBouton()->setID(9904);
	barre->setBoutonImage(5,"iconeJournal.png");
	barre->getBouton(5)->getBouton()->setID(9905);
	barre->setBoutonImage(6,"iconeMenu.png");
	barre->getBouton(6)->getBouton()->setID(9906);

	//affichage de l'élément
	afficher();
}

void FEtat::setPseudo(string psd){
	pseudo->setText(irr::core::stringw(psd.c_str()).c_str());
}

void FEtat::setNiveau(string nv){
	niveau->setText(irr::core::stringw(nv.c_str()).c_str());
}

void FEtat::setVieMax(int vieMax) {
	vie->setMax(vieMax);
}

void FEtat::setVieVal(int vieVal) {
	vie->setVal(vieVal);
}

void FEtat::setPouvoirMax(int pvrMax) {
	pouvoir->setMax(pvrMax);
}

void FEtat::setPouvoirVal(int pvrVal) {
	pouvoir->setVal(pvrVal);
}

void FEtat::setExperienceMax(int xpMax) {
	experience->setMax(xpMax);
}

void FEtat::setExperienceVal(int xpVal) {
	experience->setVal(xpVal);
}
