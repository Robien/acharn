#include "Police.h"
#include <iostream>

using namespace std;

Police::Police(string nom, irr::gui::IGUIEnvironment * gui) {
    m_nom=nom;

    //chargement de la police d'écriture
    cout<<"Chargement de la Police..."<<endl;
    guiSkin = gui->getSkin();
    guiFont = gui->getFont(getPolicePath());
    if(guiFont){
    	guiSkin->setFont(guiFont);
    	cout<<"La Police a bien été chargée"<<endl;
    }
    else{
    	cout<<"Police non chargée."<<endl;
    }
}

Police* Police::getPolice() {
    return (this);
}

irr::io::path Police::getPolicePath() {
    string chemin;
    chemin = "./data/interface/police/"+m_nom;
    return irr::io::path(chemin.c_str());
}

void Police::setPolice(string nom) {
    m_nom=nom;
}
