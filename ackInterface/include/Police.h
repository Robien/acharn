#ifndef DEF_Police
#define DEF_Police

#include <irrlicht.h>
#include <string>

using namespace std;

class Police {
public:
    //constructeur
    Police(string nom, irr::gui::IGUIEnvironment * gui);
    //nom    -> nom de la police

    Police* getPolice();
    irr::io::path getPolicePath();
    void setPolice(string chemin);

private:
    string m_nom;
    irr::gui::IGUISkin* guiSkin;
    irr::gui::IGUIFont * guiFont;
};


#endif
