#ifndef DEF_BARREBOUTON
#define DEF_BARREBOUTON

#include "Bouton.h"
#include <map>

using namespace std;

class BarreBouton : public Referenced {
public:
    BarreBouton(InterfaceInfo* inter,
    		irr::core::position2d<irr::s32> coord,
    		int largeur,
    		int hauteur,
    		int nbColonne,
    		int nbLigne,
    		irr::gui::IGUIWindow* parent);
    void setBoutonImage(int num, string image);
    void setBoutonTexte(int num, string texte);
    Bouton* getBouton(int num);
    int getNbBouton();

private:
    map<int,Bouton*> tabBouton;
    int nbBouton;
};

#endif
