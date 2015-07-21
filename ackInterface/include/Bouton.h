#ifndef DEF_BOUTON
#define DEF_BOUTON

#include "InterfaceInfo.h"

using namespace std;

class Bouton : public Referenced {
public:
	Bouton(InterfaceInfo * inter,
				   irr::core::position2d<irr::s32> coord,
				   int largeur,
				   int hauteur,
	               string image,
	               string texte,
	               irr::gui::IGUIWindow* parent);
	void setBoutonImage(string image);
	void setBoutonTexte(string texte);
	irr::gui::IGUIButton* getBouton();

private:
	Skin * skin;
	irr::gui::IGUIButton* bouton;
    irr::video::IVideoDriver* pilote;

};

#endif
