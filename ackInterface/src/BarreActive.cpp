#include "BarreActive.h"

using namespace std;

BarreActive::BarreActive(InterfaceInfo* inter,
                irr::core::position2d<irr::s32> coord,
                int larg, int haut,
                string font, string motif,
                int max, int val,
                irr::gui::IGUIWindow* parent) {

	// création de la barre de fond insenssible
	barreFond = new Bouton(inter,coord,larg,haut,font,"",parent);
	barreFond->getBouton()->setIsPushButton(false);

	// création de la barre active
	barreMotif = new Bouton(inter,coord,larg,haut,motif,"",parent);
	barreMotif->getBouton()->setIsPushButton(false);

	//initialisation
	coordonee=coord;
	maximum=max;
	largeur=larg;
	hauteur=haut;
	setVal(val);
}

void BarreActive::setVal(int val){
	valeur=val;
	//redimenssionement de la barre active
    barreMotif->getBouton()->setRelativePosition(irr::core::rect<irr::s32 > (coordonee.X,
                                                                      coordonee.Y,
                                                                      coordonee.X+inPercentOfMax(val),
                                                                      coordonee.Y+hauteur));
}

void BarreActive::setMax(int max){
	maximum=max;
	setVal(valeur);
}

irr::s32 BarreActive::inPercentOfMax(int val){
	//calcul du ration val/max pour obtenir la nouvelle largeur de la barre
    irr::s32 ratio = (irr::s32)((signed int) ((((float) val) / ((float) maximum))*largeur));
	return ratio;
}
