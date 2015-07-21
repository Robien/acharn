#include "Bouton.h"

using namespace std;

Bouton::Bouton(InterfaceInfo * inter,
			   irr::core::position2d<irr::s32> coord,
			   int largeur,
			   int hauteur,
               string image,
               string texte,
               irr::gui::IGUIWindow* parent)
	{
		//initialisation des éléments
		pilote = inter->getPilote();
		skin = inter->getSkin();
		bouton = inter->getGui()->addButton(irr::core::rect<irr::s32>(coord.X,coord.Y,coord.X+largeur,coord.Y+hauteur),parent);
		bouton->setDrawBorder(true);
		bouton->setUseAlphaChannel(true);
		if (image!="") setBoutonImage(image);
		if (texte!="") setBoutonTexte(texte);
	}

void Bouton::setBoutonImage(string image){
//méthode pour changer l'image du bouton
	bouton->setImage(pilote->getTexture(skin->getSkinTexture(image)));
}

void Bouton::setBoutonTexte(string texte){
//méthode pour changer le texte du bouton
	string * txt = new string(texte);
	bouton->setText(irr::core::stringw(txt->c_str()).c_str());
}

irr::gui::IGUIButton * Bouton::getBouton(){
	return bouton;
}
