#ifndef DEF_INTER
#define DEF_INTER

#include <iostream>

#include "FEtat.h"
#include "FBarreAction.h"
#include "FChat.h"
#include "FCarac.h"

#include "Fenetre.h"
#include "Bouton.h"

using namespace std;

class Interface : public Referenced {
public:
    Interface(irr::scene::ISceneManager *scene, // map
            irr::video::IVideoDriver* dri, // driver video
            int l = 800, //largeur d'écran par defaut
            int h = 600); //hauteur d'écran par defaut
    ~Interface();

    void draw(); // dessine l'interface à l'écran

    string envoyerMessageChat();
    void recevoirMessageChat(string msg);

    inline int getVie(){return vie;}
    inline int getPouvoir(){return pouvoir;}
    inline int getExperience(){return experience;}
    inline void setLogVisible(bool visible){menulog->setVisible(visible);}
    inline void setMenuJeuVisible(bool visible){menujeu->setVisible(visible);}
    inline void switchLogVisible(bool visible){menulog->setVisible(!menulog->isVisible());}
    inline void switchMenuJeuVisible(bool visible){menujeu->setVisible(!menujeu->isVisible());}

    void setVieMax(int vm);
    void setVie(int v);
    void setPouvoirMax(int pm);
    void setPouvoir(int p);
    void setExperienceMax(int em);
    void setExperience(int e);
    void setPseudo(string ps);
    void setNiveau(int n);

    void gagnerNiveau(int nbPoint);
    void cliquePoint(int id);
    Caracteristique * appliquerNiveau();
    void majCara(Caracteristique* cara);
    void afficherCara(bool afficher);

private:

    void rafraichir();

    irr::gui::IGUIEnvironment * gui;
    irr::video::IVideoDriver * driver;
    irr::scene::ISceneManager * sceneManager;

    Police* police;
    Skin* skin;
    InterfaceInfo* inter;

    FEtat* fEtat;
    FChat * fChat;
    FCarac * fCarac;
    FBarreAction * fBarreAction;

    int lEcran, hEcran;

    int vieMax;
    int vie;
    int pouvoirMax;
    int pouvoir;
    int experienceMax;
    int experience;
    string* pseudo;
    int niveau;


    int lFenetre, hFenetre;
    irr::gui::IGUIWindow* menujeu;
    irr::gui::IGUIWindow* menulog;
    irr::gui::IGUIEditBox *logTexte;
    irr::gui::IGUIEditBox *mdpTexte;
    irr::gui::IGUIStaticText *pseudoTexte;

};

#endif
