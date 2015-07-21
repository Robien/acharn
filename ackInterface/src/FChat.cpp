#include "FChat.h"

FChat::FChat(InterfaceInfo * inter):
	Fenetre(inter,irr::core::position2d<irr::s32>(10,416),L"Fenetre de dialogue",280,110)
{
	//texte de sortie, c'est là que s'affiche le dialogue
    output = inter->getGui()->addStaticText(L"Le monde d'Acharn vous attend...\n\n\n",
            							 irr::core::rect<irr::s32>(10,10,270,85),
           							 	 true,true,fenetre,-1,true);
    output->setTextAlignment(irr::gui::EGUIA_UPPERLEFT, irr::gui::EGUIA_LOWERRIGHT);

    //texte d'entrer, c'est là que le joueur écrit son texte
    input = inter->getGui()->addEditBox(L"",irr::core::rect<irr::s32>(10,87,230,105),true,fenetre);
    input->setMax(160);
    input->setID(707);

    //bouton d'envoie de texte
    send = new Bouton(inter,irr::core::position2d<irr::s32>(232,87),38,18,"","SEND",fenetre);
    send->getBouton()->setID(1337);

    //attribut qui va contenir tout le texte du chat vu par le joueur
    texte="";

    //affichage de l'élément
    afficher();
}

string FChat::envoyer(){
//méthode pour l'envoi du texte saisie par le joueur
    irr::core::stringw msgS;
    string msgE;

    msgS=input->getText();

    for (int i=0;msgS[i]!='\0';i++){
        msgE+=(char)msgS[i];
    }

    string vide = "";
    input->setText(irr::core::stringw(vide.c_str()).c_str());

    return msgE;
}

void FChat::recevoir(string message){
//méthode de réception d'un message et d'affichage du dialogue
    if (message!=""){
        texte+="\n"+message;
        output->setText(irr::core::stringw(texte.c_str()).c_str());
    }
}
