#ifndef DEF_BarreActive
#define DEF_BarreActive

#include "Bouton.h"

using namespace std;

class BarreActive {
public:
    BarreActive(InterfaceInfo* inter,
                irr::core::position2d<irr::s32> coord,
                int larg, int haut,
                string font, string motif,
                int max, int val,
                irr::gui::IGUIWindow* parent);
	void setVal(int val);
	void setMax(int max);
	
private:
	irr::s32 inPercentOfMax(int val);
	
	Bouton* barreFond;
	Bouton* barreMotif;
	int maximum;
	int valeur;
	int hauteur;
	int largeur;
	irr::core::position2d<irr::s32> coordonee;

};

#endif
