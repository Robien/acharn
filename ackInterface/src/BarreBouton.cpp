#include "BarreBouton.h"

using namespace std;

BarreBouton::BarreBouton(InterfaceInfo* inter,
						 irr::core::position2d<irr::s32> coord,
						 int largeur,
						 int hauteur,
						 int nbColonne,
						 int nbLigne,
						 irr::gui::IGUIWindow* parent){

	//nombre total de bouton
	nbBouton=nbLigne*nbColonne;

	//position du bouton dans le tableau
	int position=1;

    for (int j = 1; j <= nbLigne; j++) {
        for (int i = 1; i <= nbColonne; i++) {
            Bouton* bouton;
            bouton = new Bouton(inter,
            		irr::core::position2d<irr::s32>(coord.X+2+((i-1)*largeur),
            										coord.Y+1+((j-1)*hauteur)),
            		largeur,hauteur,"","",parent);
            tabBouton[position++] = bouton;
        }
    }
}

void BarreBouton::setBoutonImage(int num, string image){
//méthode pour changer l'image du bouton à la position num
	tabBouton[num]->setBoutonImage(image);
}

void BarreBouton::setBoutonTexte(int num, string nom){
//méthode pour changer le texte du bouton à la position num
	tabBouton[num]->setBoutonTexte(nom);
}

Bouton* BarreBouton::getBouton(int num){
	return tabBouton[num];
}

int BarreBouton::getNbBouton(){
	return nbBouton;
}
