#include "FBarreAction.h"

FBarreAction::FBarreAction(InterfaceInfo * inter):
	Fenetre(inter,irr::core::position2d<irr::s32>(195,530),L"Barre d'action",386,64)
{
	//création de la barre de bouton
	barre = new BarreBouton(inter,irr::core::position2d<irr::s32>(0,0),32,32,12,2,fenetre);

	//association du bouton et de son ID
	for(int i=1;i<(barre->getNbBouton());i++){
		barre->getBouton(i)->getBouton()->setID(i);
	}

	barre->getBouton(1)->setBoutonImage("icon1.png");
	barre->getBouton(2)->setBoutonImage("icon2.png");
	barre->getBouton(3)->setBoutonImage("icon3.png");
	barre->getBouton(4)->setBoutonImage("icon4.png");
	barre->getBouton(5)->setBoutonImage("icon5.png");
	barre->getBouton(6)->setBoutonImage("icon6.png");
	barre->getBouton(7)->setBoutonImage("icon7.png");
	barre->getBouton(8)->setBoutonImage("icon8.png");

	//affichage de l'élément
	afficher();
}
