#include "Interface.h"

using namespace std;
using namespace irr;

Interface::Interface(irr::scene::ISceneManager *scene, irr::video::IVideoDriver* dri, int l, int h) :
    lEcran(l), hEcran(h), driver(dri), sceneManager(scene)
{

    //initialisation des attributs
    vieMax = 1;
    vie = 1;
    pouvoirMax = 1;
    pouvoir = 1;
    experienceMax = 10;
    experience = 0;
    pseudo = new string;
    niveau = 1;

    //création des éléments de l'interface
    gui = sceneManager->getGUIEnvironment();
    police = new Police("TrebuchetMSBold.png", gui);
    skin = new Skin("acharn");
    inter = new InterfaceInfo(dri, gui, skin, police);

    //création des fenetres
    fEtat = new FEtat(inter);
    fChat = new FChat(inter);
    fCarac = new FCarac(inter);
    fBarreAction = new FBarreAction(inter);
    fCarac = new FCarac(inter);

    //raffraichissement de l'interface, initialise les variables graphiques
    rafraichir();

    ///////////////////////////////////////////////////////////
    // CODE TOUT POURRI A SUPPRIMER DES QUE POSSIBLE
    ///////////////////////////////////////////////////////////

    lFenetre = 200;
    hFenetre = 100;

    menujeu = gui->addWindow(core::rect<s32>((lEcran / 2) - (lFenetre / 2), // coinHautGauche X
            (hEcran / 2) - (hFenetre / 2), // coinHautGauche Y
            (lEcran / 2) + (lFenetre / 2), // coinBasDroit X
            (hEcran / 2) + (hFenetre / 2)), // coinBasDroit Y
            false, // vrai : les autre fenêtre ne peuvent être utilisées tant que celle-ci n'a pas été supprimée
            L"Menu du Jeu", // titre de la fenêtre
            0, // parent
            0x10000); // id de l'élément gui

    // dissimulation de la barre de titre
    //	menujeu->setDrawTitlebar(false);
    // récupèration puis dissimulation du bouton close
    menujeu->getCloseButton()->setVisible(false);

    Bouton* boutonreprendre;
    boutonreprendre = new Bouton(inter, irr::core::position2d<irr::s32>(10, 20), 180, 20, "", "REPRENDRE", menujeu);
    boutonreprendre->getBouton()->setID(6); // même id que le bouton qui ferme le menu

    Bouton* boutonoption;
    boutonoption = new Bouton(inter, irr::core::position2d<irr::s32>(10, 45), 180, 20, "", "OPTION", menujeu);
    boutonoption->getBouton()->setID(201);

    Bouton* boutonquitter;
    boutonquitter = new Bouton(inter, irr::core::position2d<irr::s32>(10, 70), 180, 20, "", "QUITTER", menujeu);
    boutonquitter->getBouton()->setID(202);

    ////////////////////////////////////////////////////////////////////////////
    //		Fenetre de login
    ////////////////////////////////////////////////////////////////////////////
    // définition de hauteur et largeur de fenêtre
    hFenetre = 100;
    lFenetre = 200;

    // création de la fenêtre
    menulog = gui->addWindow(core::rect<s32>((lEcran / 2) - (lFenetre / 2), // coinHautGauche X
            (hEcran / 2) - (hFenetre / 2), // coinHautGauche Y
            (lEcran / 2) + (lFenetre / 2), // coinBasDroit X
            (hEcran / 2) + (hFenetre / 2)), // coinBasDroit Y
            false, // vrai : les autre fenêtre ne peuvent être utilisées tant que celle-ci n'a pas été supprimée
            L"Login", // titre de la fenêtre
            0, // parent
            0x10000); // id de l'élément gui

    // dissimulation de la barre de titre
    //	menujeu->setDrawTitlebar(false);
    // récupèration puis dissimulation du bouton close
    menulog->getCloseButton()->setVisible(false);

    // création de la zone de saisie de texte
    logTexte = gui->addEditBox(L"", // texte par defaut
            core::rect<s32>(10, // coinHautGauche X
                    20, // coinHautGauche Y
                    lFenetre - 10, // coinBasDroit X
                    40), // coinBasDroit Y
            true, // vrai : affiche les bords en 3D
            menulog); // parent
    logTexte->setMultiLine(false);
    logTexte->setMax(16);
    logTexte->setID(999);

    // création de la zone de saisie de texte
    mdpTexte = gui->addEditBox(L"", // texte par defaut
            core::rect<s32>(10, // coinHautGauche X
                    45, // coinHautGauche Y
                    lFenetre - 10, // coinBasDroit X
                    65), // coinBasDroit Y
            true, // vrai : affiche les bords en 3D
            menulog); // parent
    mdpTexte->setPasswordBox(true, L'*');
    mdpTexte->setWordWrap(false);
    mdpTexte->setMultiLine(false);
    mdpTexte->setMax(16);
    mdpTexte->setID(666);

    Bouton* boutonlog;
    boutonlog = new Bouton(inter, irr::core::position2d<irr::s32>(10, 70), 180, 20, "", "OK", menulog);
    boutonlog->getBouton()->setID(203);

    ///////////////////////////////////////////////////////////
    // FIN DU CODE TOUT POURRI
    ///////////////////////////////////////////////////////////

}

Interface::~Interface()
{
    delete pseudo;
}

void Interface::draw()
{
    //méthode pour dessiner tout les éléments de l'interface,
    //cette méthode dessine mais ne force pas l'affichage
    gui->drawAll();
}

void Interface::setPseudo(string ps)
{
    *pseudo = ps;
    rafraichir();
}

void Interface::setNiveau(int n)
{
    niveau = n;
    rafraichir();
}

void Interface::setVieMax(int vm)
{
    if (vm > 0)
    {
        vieMax = vm;
        rafraichir();
    }
    else
    {
        cout << "Vie max inferieur a 0" << endl;
    }
}

void Interface::setVie(int v)
{
    if (v < 0)
    {
        v = 0;
    }
    else if (v > vieMax)
    {
        v = vieMax;
    }
    vie = v;
    rafraichir();
}

void Interface::setPouvoirMax(int pm)
{
    if (pm > 0)
    {
        pouvoirMax = pm;
        rafraichir();
    }
    else
    {
        cout << "Pouvoir max inferieur a 0" << endl;
    }
}

void Interface::setPouvoir(int p)
{
    if (p >= 0 && p <= pouvoirMax)
    {
        pouvoir = p;
        rafraichir();
    }
    else
    {
        cout << "Pouvoir inferieur a 0 ou superieur a Pouvoir max" << endl;
    }
}

void Interface::setExperienceMax(int em)
{
    if (em > 0)
    {
        experienceMax = em;
        rafraichir();
    }
    else
    {
        cout << "Expérience max inferieur a 0" << endl;
    }
}

void Interface::setExperience(int e)
{
    if (e >= 0 && e <= experienceMax)
    {
        experience = e;
        rafraichir();
    }
    else
    {
        cout << "Expérience inferieur a 0 ou superieur a Expérience max" << endl;
    }
}

string Interface::envoyerMessageChat()
{
    //méthode pour la transmission d'un message envoyé par le Chat
    return fChat->envoyer();
}

void Interface::recevoirMessageChat(string msg)
{
    //méthode pour la transmission d'un message envoyé au Chat
    fChat->recevoir(msg);
}

void Interface::rafraichir()
{
    //méthode pour rafraichir l'interface lorsqu'une
    //variable graphique change de valeur
    fEtat->setPseudo(pseudo->c_str());
    fEtat->setNiveau((converstr(niveau)).c_str());
    fEtat->setVieMax(vieMax);
    fEtat->setVieVal(vie);
    fEtat->setPouvoirMax(pouvoirMax);
    fEtat->setPouvoirVal(pouvoir);
    fEtat->setExperienceMax(experienceMax);
    fEtat->setExperienceVal(experience);
}

void Interface::gagnerNiveau(int nbPoint)
{
    fCarac->gagneNiveau(nbPoint);
}

void Interface::cliquePoint(int id)
{
    fCarac->cliquePoint(id);
}

Caracteristique * Interface::appliquerNiveau()
{
    return fCarac->appliquer();
}

void Interface::majCara(Caracteristique* cara)
{
    fCarac->majCarac(cara);
}

void Interface::afficherCara(bool afficher)
{
    if (afficher)
    {
        fCarac->afficher();
    }
    else
    {
        fCarac->cacher();
    }
}
