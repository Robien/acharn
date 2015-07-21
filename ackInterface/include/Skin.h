#ifndef DEF_Skin
#define DEF_Skin

#include <irrlicht.h>
#include <string>

using namespace std;

class Skin {
public:
    //constructeur
    Skin(string chemin);
    //chemin    -> chemin du dossier des éléments du skin
    //exemple : "interface/monskin/"


    Skin* getSkin();
    string getSkinNom();
    irr::io::path getSkinPath();
    irr::io::path getSkinTexture(string texture);
    void setSkinNom(string nom);
    void setSkinPath(string chemin);
    
private:
    string m_chemin;
    string m_nom;
    // initialisation par le chemin par defaut
};


#endif
