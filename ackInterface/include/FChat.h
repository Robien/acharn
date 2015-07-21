#ifndef DEF_FChat
#define DEF_FChat

#include "Fenetre.h"
#include "Bouton.h"

using namespace std;

class FChat : public Fenetre {
public:
	FChat(InterfaceInfo* inter);
	string envoyer();
	void recevoir(string message);

private:
    irr::gui::IGUIStaticText * output;
    irr::gui::IGUIEditBox * input;
    string texte;
    Bouton * send;
};


#endif
