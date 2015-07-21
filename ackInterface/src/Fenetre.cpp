#include "Fenetre.h"

using namespace std;

Fenetre::Fenetre(InterfaceInfo* inter,irr::core::position2d<irr::s32> coord,
        		 const wchar_t* titre,int lFenetre,int hFenetre){

	//construction de la fenetre
	gui=inter->getGui();
	pilote=inter->getPilote();
	fenetre=gui->addWindow(irr::core::rect<irr::s32>(coord.X,coord.Y,coord.X+lFenetre,coord.Y+hFenetre),false,titre,0,-1);

	//image de font de la fenetre
	irr::gui::IGUIImage * font = inter->getGui()->addImage(irr::core::rect<irr::s32>(0,0,lFenetre,hFenetre),fenetre,-1,0);
	font->setImage(inter->getPilote()->getTexture(inter->getSkin()->getSkinTexture("fontFenetre.png")));
	font->setUseAlphaChannel(false);

    //Barre menu :
    fenetre->setDrawTitlebar(false);
	fenetre->getCloseButton()->setVisible(false);
			
	//Cacher la fenêtre par défaut
	cacher();
}

void Fenetre::cacher(){
	fenetre->setVisible(false);
}

void Fenetre::afficher(){
	fenetre->setVisible(true);
}
