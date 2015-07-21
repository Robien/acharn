#include "Skin.h"

using namespace std;

Skin::Skin(string nom) {
    //chemin    -> chemin des éléments du skin

    m_nom=nom;
    m_chemin="./data/interface/skin/"+m_nom+"/";

}

Skin* Skin::getSkin() {
    return (this);
}

string Skin::getSkinNom() {
    return (m_nom);
}

irr::io::path Skin::getSkinPath() {
    return irr::io::path(m_chemin.c_str());
}

irr::io::path Skin::getSkinTexture(string texture) {
        return irr::io::path((m_chemin+texture).c_str());
}

void Skin::setSkinNom(string nom) {
   m_nom=nom;
   setSkinPath("./data/interface/skin/"+m_nom+"/");
}

void Skin::setSkinPath(string chemin) {
    m_chemin=chemin;
}
