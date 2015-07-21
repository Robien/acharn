/*
 * AbstractPerso.h
 *
 *  Created on: fort longtemps
 *      Author: céphise
 */

#include <iostream>
#include "AbstractPerso.h"
#include "PersoJoueur.h"
#include "Interpreteur.h"

using namespace std;

////////// Constructeur //////////

AbstractPerso::AbstractPerso(IrrlichtDevice* device, int init, CallbackIncantation* callbackIncant) :
    Perso(device), lastAttaquant(NULL)
{
    //initialisation callback
    _callbackIncantation = callbackIncant;

    //initialisation des composant des caracteristique du joueur
    generRando = new Random(init);
    caractperso.m_vie = caractperso.m_vieMax = 1000;
    caractperso.m_radiation = caractperso.m_radiationMax = 100;
    caractperso.m_niveau = 1;
    caractperso.m_occupe = 0;
    caractperso.m_force = 1;
    caractperso.m_endurance = 1;
    caractperso.m_volonte = 1;
    caractperso.m_inteligence = 1;
    caractperso.m_agilite = 1;
    caractperso.m_initiative = 1;
    caractperso.m_ccombat = 1;
    caractperso.m_ctir = 1;
    caractperso.m_init = init;
    caractperso.m_nom = "John Doe";
    //initialisation des composant des attaques
    finIncantation = 0;
    competenceEnIncant = NULL;
    attaqueASup = -2;
    newCompetence("<#nom=\"Attaque de base\"#degat=$puissance#cooldown=2>");

    std::cout << caractperso.m_nom << " ATTENTION CONSTRUCTEUR DEPRECATED +" << std::endl;
}

AbstractPerso::AbstractPerso(IrrlichtDevice* device, string nom, int init, CallbackIncantation* callbackIncant) :
    Perso(device), lastAttaquant(NULL)
{
    //initialisation callback
    _callbackIncantation = callbackIncant;

    //initialisation des composant des caracteristique du joueur
    generRando = new Random(init);
    caractperso.m_vie = caractperso.m_vieMax = 1000;
    caractperso.m_radiation = caractperso.m_radiationMax = 100;
    caractperso.m_niveau = 1;
    caractperso.m_occupe = 0;
    caractperso.m_nom = nom;
    caractperso.m_force = 1;
    caractperso.m_endurance = 1;
    caractperso.m_volonte = 1;
    caractperso.m_inteligence = 1;
    caractperso.m_agilite = 1;
    caractperso.m_init = init;
    caractperso.m_initiative = 1;
    caractperso.m_vitessemv = 23;
    caractperso.m_ctir = 1;
    caractperso.m_ccombat = 1;
    //initialisation des composant des attaques
    attaqueASup = -2;
    finIncantation = 0;
    competenceEnIncant = NULL;
    newCompetence("<#nom=\"Attaque de base\"#degat=$puissance*2#cooldown=2>");
    newCompetence("<#nom=\"Attaque magique\"#degat=$inteligence*2#cout=50>");
    newCompetence("<#nom=\"buff vitesse\"#degat=0-20#affect=\"vitessemv\"#cout=70#rever=30>");
    newCompetence("<#nom=\"brulure\"#degat=60 #tps=0#pas=1#affect=\"radiation\"#cout=80 <#degat=10#nom=\"dot\"#tps=5#pas=10#affect=\"vie\">>");
    newCompetence("<#nom=\"RegenerationVie\"#degat=0-(@vieMax%10)#cooldown=1#cout=10#type=20>");//regene vie
    newCompetence("<#nom=\"RegenerationRad\"#degat=0-(@radiationMax%10)#cooldown=4#affect=\"radiation\"type=20>");//regene

    std::cout << caractperso.m_nom << " ATTENTION CONSTRUCTEUR DEPRECATED" << std::endl;
}

AbstractPerso::AbstractPerso(string infojoueur, IrrlichtDevice* device, int init, CallbackIncantation* callbackIncant) :
    Perso(device), lastAttaquant(NULL)
{
    //initialisation callback
    _callbackIncantation = callbackIncant;

    //initialisation des composant des caracteristique du joueur
    vector<std::string> vcarac = split(infojoueur.c_str(), ',');
    generRando = new Random(init);
    caractperso.setAttribut(vcarac);
    caractperso.m_init = init;

    //initialisation des composant des attaques
    finIncantation = 0;
    competenceEnIncant = NULL;
    newCompetence("<#nom=\"Attaque de base\"#degat=$puissance#cooldown=2>");

}

////////// Destructeur //////////

AbstractPerso::~AbstractPerso()
{
}

////////////////////////////////////////////////////// Méthodes ///////////////////////////////////////////////////

////////// Affichage //////////

void AbstractPerso::affiEtat()
{
    cout << "---------------------------------------------------------" << endl;
    cout << "    " << getNom() << endl;
    cout << "     vie(" << (int) caractperso.m_vie << "/ " << (int) caractperso.m_vieMax << ") Radiation : " << (int) caractperso.m_radiation << "/" << (int) caractperso.m_radiationMax << ")" << endl;
    cout << "---------------------------------------------------------" << endl;
    std::cout << caractperso.m_nom << " ATTENTION METHODE affiEtat DEPRECATED" << std::endl;
}

////////// Getters //////////

float AbstractPerso::getRadiation()
{
    return caractperso.m_radiation;
}

float AbstractPerso::getVie()
{
    return caractperso.m_vie;
}

float AbstractPerso::getRadiationMax()
{
    return caractperso.m_radiationMax;
}

float AbstractPerso::getVieMax()
{
    return caractperso.m_vieMax;
}

float AbstractPerso::getEndurance()
{
    return caractperso.m_endurance;
}

int AbstractPerso::getNiveau()
{
    return caractperso.m_niveau;
}

int AbstractPerso::getInit()
{
    return caractperso.m_init;
}

float AbstractPerso::getOccupe()
{
    return caractperso.m_occupe;
}

float AbstractPerso::getArgent()
{
    return m_argent;
}

std::string AbstractPerso::getNom()
{
    return caractperso.m_nom;
}

Caracteristique* AbstractPerso::getCaracteristique()
{
    return &caractperso;
}

float AbstractPerso::getArmure()
{
    return m_Equipement.getArmure();
}

float AbstractPerso::getArmureMag()
{
    return m_Equipement.getArmureMagique();
}

Random* AbstractPerso::getRandom()
{
    return generRando;
}

int AbstractPerso::donnexp(AbstractPerso &vainqueur)
{
    int xp = caractperso.m_niveau * 5 + 49;
    float diff = caractperso.m_niveau - vainqueur.getNiveau();
    if (diff < 0)
    {
        if (diff > (-9))
            diff = (1 - ((float) (-1 * diff) / 10));
        else
            diff = 0;
    }
    else
    {
        if (diff < (9))
            diff = (1 + (float) (diff / 10));
        else
            diff = 2;
    }

    xp = xp * diff;
    return xp;
}
PersoJoueur* AbstractPerso::getLastAttaquant()
{
    return lastAttaquant;
}

////////// Etat Personnage //////////

bool AbstractPerso::estVivant()
{
    return (caractperso.m_vie > 0);
}

bool AbstractPerso::occupe(float currenttime)
{
    bool occ;
    if (getOccupe() - currenttime > 0)
        occ = true;
    else
    {
        occ = false;
        initocc();
    }
    return occ;
}

void AbstractPerso::isDead()
{
    l_atkRecu.clear();
}

////////// Gestion Objet //////////

AbstractObjet* AbstractPerso::creerObjet(string infodeObjet)
{
    AbstractObjet* objet;
    string typeobjstr;
    if (isdigit(infodeObjet[0]) && isdigit(infodeObjet[1]))
    {
        typeobjstr = infodeObjet[0] + infodeObjet[1];
    }
    else if (isdigit(infodeObjet[0]))
    {
        typeobjstr = infodeObjet[0];
    }
    else
    {
        return NULL;
    }

    int typeobj = converint(typeobjstr);
    switch (typeobj)
    {
    case 0:
        objet = new ArmeContact(infodeObjet);
        break;
    case 1:
        objet = new ArmeDistance(infodeObjet);
        break;
    case 2:
        objet = new ObjetEquipement(infodeObjet);
        break;
    case 10:
        objet = new ObjetEquipement(infodeObjet);
        break;
    default:
        objet = NULL;
    }
    return objet;
}

bool AbstractPerso::equiperArme(AbstractArme* arme, int position)
{
    bool reussi = false;
    if (position != 0 && position != 1)
    {
        if (!m_Equipement.armeAt(0) && !m_Equipement.armeAt(1))
        {
            m_Equipement.ajouterArme(arme, position);
            reussi = true;
            addBonus(arme->getCaracteristique());
            caractperso.opePuissance(arme->getPuissance(), true);
        }
    }
    else
    {
        if (!m_Equipement.armeAt(position) && arme->getPoids() <= getEndurance())
        {
            m_Equipement.ajouterArme(arme, position);
            reussi = true;
            addBonus(arme->getCaracteristique());
            caractperso.opePuissance(arme->getPuissance(), true);
        }
    }
    return reussi;
}

vector<AbstractArme*> AbstractPerso::changerArme(AbstractArme* arme, int position)
{
    vector<AbstractArme*> anciennesArmes;
    if (position == 0 && position == 1 && arme->getPoids() <= getEndurance())//si arme a 1mains et que assez fort pour la porter
    {
        anciennesArmes = m_Equipement.ajouterArme(arme, position);
    }
    else
    {
        anciennesArmes = m_Equipement.ajouterArme(arme, position);
    }

    for (int i = 0; i < (int) anciennesArmes.size(); i++)
    {
        delBonus(anciennesArmes[i]->getCaracteristique());
        caractperso.opePuissance(anciennesArmes[i]->getPuissance(), false);
    }
    addBonus(arme->getCaracteristique());
    caractperso.opePuissance(arme->getPuissance(), true);
    return anciennesArmes;
}

AbstractArme* AbstractPerso::desequiperArme(int position)
{
    AbstractArme* ancienneArme = m_Equipement.enleverArme(position);
    if (ancienneArme != NULL)
    {
        delBonus(ancienneArme->getCaracteristique());
        caractperso.opePuissance(ancienneArme->getPuissance(), false);
    }
    return ancienneArme;
}

bool AbstractPerso::isArme2M()
{
    return m_Equipement.haveArme2M();
}

bool AbstractPerso::haveArme()
{
    return m_Equipement.haveArme();
}

void AbstractPerso::equiper(ObjetEquipement* newequip)
{
    ObjetEquipement* ancienEquip = m_Equipement.ajouter(newequip);

    if (ancienEquip != NULL)
    {
        delBonus(ancienEquip->getCaracteristique());
    }

    addBonus(newequip->getCaracteristique());
}

void AbstractPerso::desequiper(ObjetEquipement::e_Position position)
{
    ObjetEquipement* ancienEquip = m_Equipement.enlever(position);
    if (ancienEquip != NULL)
    {
        delBonus(ancienEquip->getCaracteristique());
        mettreDansSac(ancienEquip);
    }
}

bool AbstractPerso::haveEquipement(ObjetEquipement::e_Position position)
{
    return m_Equipement.getEquippement(position) != NULL;
}

void AbstractPerso::mettreDansSac(AbstractObjet* item)
{
    m_sac.ajouter(item);
}

void AbstractPerso::SortirDeSac(int numitem)
{
    m_sac.enlever(numitem);
}

////////// Setters //////////

void AbstractPerso::setInfo(string infojoueur, int init)
{
    vector<std::string> vcarac = split(infojoueur.c_str(), ',');
    generRando = new Random(init);
    caractperso.setAttribut(vcarac);
    setRadiation(getRadiation());
    setRadiationMax(getRadiationMax());
    setVie(getVie());
    setVieMax(getVieMax());
    caractperso.m_init = init;
}

void AbstractPerso::setRadiation(float rad)
{
    caractperso.m_radiation = rad;
}

void AbstractPerso::setVie(float vie)
{
    caractperso.m_vie = vie;
}

void AbstractPerso::setRadiationMax(float radm)
{
    caractperso.m_radiationMax = radm;
}

void AbstractPerso::setVieMax(float viem)
{
    caractperso.m_vieMax = viem;
}

void AbstractPerso::setoccupe(float tpocc, float currenttime)
{
    caractperso.m_occupe = tpocc + currenttime;
}

void AbstractPerso::addoccupe(float tpocc, float currenttime)
{
    caractperso.m_occupe += tpocc + (occupe(currenttime) ? 0 : currenttime);
}

void AbstractPerso::initocc()
{
    caractperso.m_occupe = 0;
}

void AbstractPerso::addNiveau()
{
    caractperso.m_niveau++;
}

void AbstractPerso::regeneration()
{
    setVie(getVieMax());
    setRadiation(getRadiationMax());
}

void AbstractPerso::addBonus(Caracteristique add)
{
    caractperso.opeCaracteristique(add, true);
    setRadiation(getRadiation());
    setRadiationMax(getRadiationMax());
    setVie(getVie());
    setVieMax(getVieMax());
}

void AbstractPerso::delBonus(Caracteristique del)
{
    caractperso.opeCaracteristique(del, false);
    setRadiation(getRadiation());
    setRadiationMax(getRadiationMax());
    setVie(getVie());
    setVieMax(getVieMax());
}

void AbstractPerso::addArgent(float money)
{
    m_argent += money;
}

bool AbstractPerso::delArgent(float money)
{
    if (m_argent - money >= 0)
    {
        m_argent -= money;
        return true;
    }
    return false;
}

void AbstractPerso::setCallbackIncantation(CallbackIncantation* callback)
{
    _callbackIncantation = callback;
}

void AbstractPerso::addCaracteristique(Caracteristique* add)
{
    caractperso.opeCaracteristique((*add),true);
}
////////// Sauvegarde //////////
string AbstractPerso::saveCara()
{
    return caractperso.enChaine();
}

string AbstractPerso::saveEquip()
{
    return m_Equipement.enChaine();
}

string AbstractPerso::saveSac()
{
    return m_sac.enChaine();
}

string AbstractPerso::saveComp()
{
    string retour = "";
    if (l_competence.size() > 3)
    {
        retour = l_competence[4];
        for (unsigned int i = 5; i < l_competence.size(); i++)
        {
            retour += "!" + l_competence[i];
        }
    }
    return retour;
}

////////// Competence //////////

void AbstractPerso::newCompetence(std::string atk)
{
    l_competence.push_back(atk);
}

bool AbstractPerso::deleteCompetence(int i)
{
    bool rp = true;
    if (i < (int) l_competence.size())
    {
        l_competence.erase(l_competence.begin() + i);
    }
    else
    {
        cout << "cet element n'existe pas, il y a que " << l_competence.size() << endl;
        rp = false;
    }
    return rp;
}

string AbstractPerso::afficherCompetences()
{
    vector<string>::iterator it;

    int i = 0;
    string info = "-----~~~Competences~~~-----\n";
    for (it = l_competence.begin(); it != l_competence.end(); ++it)
    {
        info += i++ + " - " + *it + "\n";

    }
    return info;
}

////////// Gestion des Attaques //////////

string AbstractPerso::attaquer(AbstractPerso &cible, float currenttime)
{
    string rp = "";
    if (!l_competence.empty())
    {
        Interpreteur interp(this->getCaracteristique(), this->getRandom(), cible.getCaracteristique(), l_competence[0]);
        Attaque atk = (*(Attaque*) interp.analyse());
        atk.setAttaquant((PersoJoueur*) this);
        rp = interp.getAttaqueString();

        if (atk.getAffectCout() == "vie")
        {

            if (caractperso.m_vie - atk.getCout() < 0)
            {
                rp = "";
            }
            else
            {
                setVie(getVie() - atk.getCout());
            }
        }
        else if (atk.getAffectCout() == "radiation")
        {
            if (caractperso.m_radiation - atk.getCout() < 0)
            {
                rp = "";
            }
            else
            {
                setRadiation(getRadiation() - atk.getCout());
            }
        }
        else if (atk.getAffectCout() == "occupe")
        {
            addoccupe(atk.getCout(), currenttime);
        }
        else
        {
            cout << " Erreur de type de cout " << atk.getAffectCout() << endl;
            rp = "";
        }

        addoccupe(atk.getCoolDown(), currenttime);

        if (rp != "")
        {
            cout << getNom() << " attaque " << cible.getNom() << endl;
            atk.afficheInfos();
            cible.affecte(atk, currenttime);
            if (interp.isReverse())
            {
                Attaque atkrev = (*(Attaque*) interp.getReverse());
                cout << "Cette attaque a un reverse" << endl;
                atkrev.afficheInfos();
                cible.affecte(atkrev, currenttime);
            }
        }
    }
    else
    {
        cout << "cet element n'existe pas, il y a aucune competence " << endl;
        rp = "";
    }
    //std::cout << caractperso.m_nom << " ATTENTION METHODE attaquer1 DEPRECATED" << std::endl;
    return rp;

}

string AbstractPerso::attaquer(AbstractPerso &cible, int numattaque, float currenttime)
{
    string rp = "";
    if (numattaque < (int) l_competence.size() && numattaque >= 0)
    {
        Interpreteur interp(this->getCaracteristique(), this->getRandom(), cible.getCaracteristique(), l_competence[numattaque]);

        Attaque atk = (*(Attaque*) interp.analyse());
        atk.setAttaquant((PersoJoueur*) this);
        rp = interp.getAttaqueString();

        //atk.afficheInfos();

        if (atk.getAffectCout() == "vie")
        {

            if (caractperso.m_vie - atk.getCout() < 0)
            {
                rp = "";
            }
            else
            {
                setVie(getVie() - atk.getCout());
            }

        }
        else if (atk.getAffectCout() == "radiation")
        {
            if (caractperso.m_radiation - atk.getCout() < 0)
            {
                rp = "";
            }
            else
            {
                setRadiation(getRadiation() - atk.getCout());
            }
        }
        else if (atk.getAffectCout() == "occupe")
        {
            addoccupe(atk.getCout(), currenttime);
        }
        else
        {
            cout << " Erreur de type de cout " << atk.getAffectCout() << endl;
            rp = "";
        }

        addoccupe(atk.getCoolDown(), currenttime);

        if (rp != "")
        {
            cout << getNom() << " attaque " << cible.getNom() << endl;
            atk.afficheInfos();
            cible.affecte(atk, currenttime);
            if (interp.isReverse())
            {
                cout << "Cette attaque a un reverse" << endl;
                cible.affecte((*(Attaque*) interp.getReverse()), currenttime);
            }

        }

    }
    else
    {
        cout << "cet element n'existe pas, il y a que " << l_competence.size() << endl;
        rp = "";
    }
    //std::cout << caractperso.m_nom << " ATTENTION METHODE attaquer2 DEPRECATED" << std::endl;
    return rp;
}

string AbstractPerso::attaquer(AbstractPerso &cible, string atkbyserveur, float currenttime)
{
    string rp = "";
    if (!atkbyserveur.empty())
    {
        Interpreteur interp(this->getCaracteristique(), this->getRandom(), cible.getCaracteristique(), atkbyserveur);

        Attaque atk = (*(Attaque*) interp.analyse());
        atk.setAttaquant((PersoJoueur*) this);

        //atk.afficheInfos();
        if (interp.getVerification())
        {

            if (atk.getAffectCout() == "vie")
            {

                if (caractperso.m_vie - atk.getCout() < 0)
                {
                    rp = "Erreur pas assez de vie";
                }
                else
                {
                    setVie(getVie() - atk.getCout());
                }

            }
            else if (atk.getAffectCout() == "radiation")
            {
                if (caractperso.m_radiation - atk.getCout() < 0)
                {
                    rp = "Erreur pas assez de radiation";
                }
                else
                {
                    setRadiation(getRadiation() - atk.getCout());
                }
            }
            else if (atk.getAffectCout() == "occupe")
            {
                addoccupe(atk.getCout(), currenttime);
            }
            else
            {
                cout << " Erreur de type de cout " << atk.getAffectCout() << endl;
                rp = " Erreur de type de cout: " + atk.getAffectCout();
            }

            addoccupe(atk.getCoolDown(), currenttime);

            if (rp == "")
            {
                cout << getNom() << " attaque " << cible.getNom() << endl;
                atk.afficheInfos();
                cible.affecte(atk, currenttime);
                if (interp.isReverse())
                {
                    Attaque atkrev = (*(Attaque*) interp.getReverse());
                    cout << "Cette attaque a un reverse" << endl;
                    atkrev.afficheInfos();
                    cible.affecte(atkrev, currenttime);
                }
            }

        }
        else
        {
            cout << "Erreur de verification" << endl;
            rp = "Erreur Verification: " + atkbyserveur;
        }

    }
    else
    {
        cout << "Attaque vide" << endl;
        rp = "Erreur attaque vide";
    }
    //std::cout << caractperso.m_nom << " ATTENTION METHODE attaquer3 DEPRECATED" << std::endl;
    return rp;
}

void AbstractPerso::affecte(Attaque atk, float currentTime)
{
    atk.addTps(currentTime);
    l_atkRecu.push_back(atk);

}

string AbstractPerso::attaquer(float currenttime, int numattaque)
{
    /*
     * Methode Attaque appelée lorsqu'une demande d'attaque
     * recupere le temps d'incante et le type.
     * retourne l'attaque pour envoyer sur le reseau sinon ""
     */
    string rp = "";
    if (numattaque < (int) l_competence.size() && numattaque >= 0)
    {
        competenceEnIncant = new Interpreteur(this->getCaracteristique(), this->getRandom(), l_competence[numattaque]);
        rp = l_competence[numattaque];
        float tempsIncant;
        int typeatk;
        float portee;
        if (!competenceEnIncant->analyseIncantation(tempsIncant, typeatk, portee))
        {
            finIncantation = tempsIncant + currenttime;
            cout << "attaquer1: finincant=" << finIncantation << endl;
            //a sup lorsque le callback et que les methode seront utilisé et marcheront/*
            //debut a sup//
            if (_callbackIncantation.get() != NULL)
            {
                //pause a sup//
                _callbackIncantation->incantation(tempsIncant, typeatk, portee);
                //unpause a sup//
                //penser a mettre dans constructeur le callback avant d'essayé d'utiliser
            }
            else
            {
                cout << "!!!STOP!!!ATTENTION ERREUR DANS ATTAQUE1: dans test si callback est null" << endl;
            }

        }
        else
        {
            finIncantation = 0;
            rp = "";
        }

    }
    else
    {
        cout << "cet element n'existe pas, il y a aucune competence " << endl;
        rp = "";
    }
    return rp;
}

string AbstractPerso::attaquer(float currenttime, string atkbyserveur)
{
    /*
     * Methode Attaque appelée apres l'arrivé d'une attaque sur le serveur
     * recupere le temps d'incante et le type.
     * retourne "" si reussi sinon != ""
     */

    string rp = "";
    if (!atkbyserveur.empty())
    {
        competenceEnIncant = new Interpreteur(this->getCaracteristique(), this->getRandom(), atkbyserveur);
        float tempsIncant;
        int typeatk;
        float portee;
        if (!competenceEnIncant->analyseIncantation(tempsIncant, typeatk, portee))
        {
            finIncantation = tempsIncant + currenttime;
            cout << "attaquer2: finincant=" << finIncantation << endl;
        }
        else
        {
            finIncantation = 0;
            rp = "Analyse Incantation echec";
        }
    }
    else
    {
        cout << "Attaque vide, attaque venant du serveur est vide" << endl;
        rp = "Erreur attaque vide";
    }

    return rp;
}

vector<string>* AbstractPerso::endOfIncantation(std::vector<AbstractPerso*>& cibles, float currenttime)
{
    /*
     * Methode endOfIncantation appelée lorsque que l'incantation est fini
     * interprete l'attaque pour toutes les cibles et affecte l'attaque a celle la.
     * retourne le vector d'attaque interpreté pour envoyer sur le reseau sinon ""
     * dans le meme ordre que le vecteur recu en parametre
     */

    vector<string>* allrp = NULL;
    cout << "1Valeur fin incante: " << finIncantation << "current time doit etre <= :" << currenttime << endl;
    if (finIncantation != 0 && finIncantation <= currenttime)
    {
        allrp = new vector<string> ;
        string rp = "";
        for (unsigned int i = 0; i < cibles.size(); i++)
        {

            competenceEnIncant->setCible(cibles[i]->getCaracteristique());
            //Interpreteur interp(this->getCaracteristique(), this->getRandom(), cible.getCaracteristique(), l_competence[numattaque]);
            Attaque atk = (*(Attaque*) competenceEnIncant->analyse());
            rp = competenceEnIncant->getAttaqueString();
            atk.setAttaquant((PersoJoueur*) this);

            if (atk.getAffectCout() == "vie")
            {

                if (caractperso.m_vie - atk.getCout() < 0)
                {
                    rp = "";
                }
                else
                {
                    setVie(getVie() - atk.getCout());
                }

            }
            else if (atk.getAffectCout() == "radiation")
            {
                if (caractperso.m_radiation - atk.getCout() < 0)
                {
                    rp = "";
                }
                else
                {
                    setRadiation(getRadiation() - atk.getCout());
                }
            }
            else if (atk.getAffectCout() == "occupe")
            {
                addoccupe(atk.getCout(), currenttime);
            }
            else
            {
                cout << " Erreur de type de cout " << atk.getAffectCout() << endl;
                rp = "";
            }

            addoccupe(atk.getCoolDown(), currenttime);

            if (rp != "")
            {
                cout << getNom() << " attaque " << cibles[i]->getNom() << endl;
                atk.afficheInfos();
                cibles[i]->affecte(atk, currenttime);
                if (competenceEnIncant->isReverse())
                {
                    cout << "Cette attaque a un reverse" << endl;

                    cibles[i]->affecte((*(Attaque*) competenceEnIncant->getReverse()), currenttime);
                }
            }

            allrp->push_back(rp);
            rp = "";
        }
        competenceEnIncant = NULL;
        finIncantation = 0;
    }
    else
    {
        cout << "Erreur dans l'affectation de l'attaque: aucune attaque en incantation ou incantation pas fini " << endl;
    }

    return allrp;
}

vector<string>* AbstractPerso::endOfIncantation(std::vector<AbstractPerso*>& cibles, float currenttime, string atkbyserveur)
{
    /*
     * Methode endOfIncantation appelée lorsque recoit du serveur une attaque interprété
     * interprete l'attaque pour toutes les cibles et affecte l'attaque a celle la.
     * retourne le vector avec eventuelement des erreurs
     * dans le meme ordre que le vecteur recu en parametre
     */

    vector<string>* allrp = NULL;
    string rp = "";
    if (!atkbyserveur.empty())
    {
        cout << "Valeur fin incante: " << finIncantation << "current time doit etre <= :" << currenttime << endl;
        if (finIncantation != 0 && finIncantation <= currenttime)
        {
            allrp = new vector<string> ;

            for (unsigned int i = 0; i < cibles.size(); ++i)
            {

                competenceEnIncant->setCible(cibles[i]->getCaracteristique());
                Attaque atk = (*(Attaque*) competenceEnIncant->analyse());
                competenceEnIncant->getAttaqueString();
                rp = "";
                atk.setAttaquant((PersoJoueur*) this);
                /////////////////////
                //atk.afficheInfos();
                if (competenceEnIncant->getVerification())
                {

                    if (atk.getAffectCout() == "vie")
                    {

                        if (caractperso.m_vie - atk.getCout() < 0)
                        {
                            rp = "Erreur pas assez de vie";
                        }
                        else
                        {
                            setVie(getVie() - atk.getCout());
                        }

                    }
                    else if (atk.getAffectCout() == "radiation")
                    {
                        if (caractperso.m_radiation - atk.getCout() < 0)
                        {
                            rp = "Erreur pas assez de radiation";
                        }
                        else
                        {
                            setRadiation(getRadiation() - atk.getCout());
                        }
                    }
                    else if (atk.getAffectCout() == "occupe")
                    {
                        addoccupe(atk.getCout(), currenttime);
                    }
                    else
                    {
                        cout << " Erreur de type de cout " << atk.getAffectCout() << endl;
                        rp = " Erreur de type de cout: " + atk.getAffectCout();
                    }

                    addoccupe(atk.getCoolDown(), currenttime);

                    std::cout << "rp = " << rp << std::endl;

                    if (rp == "")
                    {
                        cout << getNom() << " attaque " << cibles[i]->getNom() << endl;
                        atk.afficheInfos();
                        cibles[i]->affecte(atk, currenttime);
                        if (competenceEnIncant->isReverse())
                        {
                            cout << "Cette attaque a un reverse" << endl;
                            cibles[i]->affecte((*(Attaque*) competenceEnIncant->getReverse()), currenttime);
                        }
                    }
                }
                else
                {
                    cout << "Erreur de verification" << endl;
                    rp = "Erreur Verification: " + atkbyserveur;
                }
                /////////////////////
                allrp->push_back(rp);
                rp = "";
            }
            competenceEnIncant = NULL;
            finIncantation = 0;
        }
        else
        {
            cout << "Erreur dans l'affectation de l'attaque2: aucune attaque en incantation ou incantation pas fini " << endl;
            rp = "Erreur dans l'affectation de l'attaque2: aucune attaque en incantation ou incantation pas fini ";
        }
    }
    else
    {
        cout << "Erreur de verification" << endl;
        rp = "Erreur Verification: " + atkbyserveur;
    }
    return allrp;
}

void AbstractPerso::endOfIncantation()
{
    /*
     * Methode endOfIncantation appelée qu'une incantation a echoué
     */

    finIncantation = 0;
    competenceEnIncant = NULL;
}

bool AbstractPerso::isOnIncantation()
{
    /*
     * Methode isOnIncantation permet de savoir si le joueur est en incantation ou non
     */
    return (finIncantation > 0 && competenceEnIncant.get() != NULL);
}

std::vector<AbstractPerso::t_degatrecu> AbstractPerso::effectuerAtk(float time)
{
    attaqueASup = -2;
    /*
     * Methode effectuerAtk execute les attaques
     */

    std::vector<t_degatrecu> rp;
    AbstractPerso::t_degatrecu dgt;
    if (l_atkRecu.size() > 0)
    {
        vector<Attaque>::iterator it;
        it = l_atkRecu.begin();

        for (unsigned int w = 0; w < l_atkRecu.size(); w++)
        {
            it = l_atkRecu.begin() + w;
            if (it->getPas() > 0)
            {
                bool fin = false;
                int i = (it->getPas() - 1);
                while (i >= 0 && !fin)
                {
                    if (time >= (it->getTps() - ((float) i * it->getParCoup())))
                    {
                        dgt.degat = recevoirEvenement(it->getDegat(), it->getAffect(), it->getType(), time); //voire suivant le type
                        lastAttaquant = it->getAttaquant();
                        if (lastAttaquant == NULL)
                        {
                            dgt.personne = "";
                        }
                        else
                        {
                            dgt.personne = lastAttaquant->getNom();
                        }
                        dgt.type = it->getAffect();
                        rp.push_back(dgt);
                        it->supPas();
                        i--;
                    }
                    else
                    {
                        fin = true;
                    }
                }
            }

            if (it->getEffet()->size() > 0)
            {
                vector<SousAttaque>* l_sseffet = it->getEffet();

                vector<SousAttaque>::iterator iteff = l_sseffet->begin();
                for (unsigned int y = 0; y < l_sseffet->size(); y++)
                {

                    iteff = l_sseffet->begin() + y;

                    if (iteff->getPas() > 0)
                    {
                        bool fineff = false;
                        int j = (iteff->getPas() - 1);
                        while (j >= 0 && !fineff)
                        {
                            if (time >= (iteff->getTps() - ((float) j * iteff->getParCoup())))
                            {
                                recevoirEvenement(iteff->getDegat(), iteff->getAffect(), iteff->getType(), time); //voire suivant le type
                                lastAttaquant = iteff->getAttaquant();
                                if (lastAttaquant == NULL)
                                {
                                    dgt.personne = "";
                                }
                                else
                                {
                                    dgt.personne = lastAttaquant->getNom();
                                }
                                dgt.type = iteff->getAffect();
                                iteff->getDegat();
                                rp.push_back(dgt);
                                iteff->supPas();
                                j--;
                            }
                            else
                            {
                                fineff = true;
                            }
                        }
                    }

                    if (!(iteff->getPas() > 0))
                    {
                        l_sseffet->erase(iteff);
                        y--;
                    }

                }
            }

            if (it->getEffet()->size() == 0 && !(it->getPas() > 0))//si l'attaque a été éffectué totalement(pas<=0) et qu'elle n'a plus de sous-effet supprimer l'attaque
            {
                attaqueASup = w;
                //                l_atkRecu.erase(it);
                //                w--;

            }

        }
    }
    viderliste();
    return rp;
}

void AbstractPerso::viderliste()
{
    if (attaqueASup >= 0)
    {
        l_atkRecu.erase(l_atkRecu.begin() + attaqueASup);
        attaqueASup = -2;
    }

}

////////// Gestion des Evenements //////////

float AbstractPerso::recevoirEvenement(float valeur, std::string type, int typeatk, float time)
{
    /*
     * Methode recevoirEvenement gere tout ce qui concerne l'ajout ou la diminution
     * des caracteristiques
     * plusieur cas possible:
     * -evenement concernant l'occupation (directement dans cette methode)
     * -evenement concernant une caracteristique autre que la vie ou la radiation (directement dans cette methode)
     * -evenement physique (appel de recevoirEvenementPhysique)
     * -evenement magique (appel de recevoirEvenementMagic)
     * retourne si a été touché
     */

    float touche = 1;
    if (type == "occupe")
    {
        addoccupe(valeur, time);
        if (caractperso.m_occupe < 0)
        {
            initocc();
        }
        cout << caractperso.m_nom << " reçoit " << (int) valeur << " d'occupation " << endl;
    }
    else if (type == "vie" || type == "radiation")
    {
        if (typeatk >= 0 && typeatk < 10) //Corps a corps
        {
            touche = recevoirEvenementPhysique(valeur, type);
        }
        else if (typeatk >= 10 && typeatk < 20) //Distance

        {
            touche = recevoirEvenementPhysique(valeur, type);
        }
        else if (typeatk >= 20 && typeatk < 30) //magique

        {
            touche = recevoirEvenementMagic(valeur, type);
        }
        else
        {
            cout << " Erreur de typeatk " << type << endl;
            touche = 0;
        }
    }
    else
    {
        if (caractperso.recherche(type) != -1)
        {
            const float carac = caractperso.recherche(type);
            if (carac + valeur >= 0)
            {
                caractperso.setAttribut(type, carac + valeur);
                cout << caractperso.m_nom << " reçoit " << (int) valeur << " de " << type << endl;
            }
            else
            {
                touche = 0;
                cout << "l'effet est trop fort et met une caracteristique en negatif donc impossible d'effectué l'effet" << endl;
            }
        }
        else
        {
            touche = 0;
        }
    }

    return touche;
}

float AbstractPerso::recevoirEvenementMagic(float valeur, std::string type)
{
    /*
     * Methode recevoirEvenementMagic gere tout ce qui concerne l'ajout ou la diminution
     * de vie ou de radiation losqu'il s'agit d'un evenement magique
     * retourne si a été touché
     */

    float touche = 1;
    if (valeur > 0) //magique + degat moins: volonté et ArmureMagique et 10%endu
    {
        if (caractperso.m_intouchable > 0)
        {
            touche = 0;
            caractperso.m_intouchable--;
            caractperso.m_intouchable *= caractperso.m_intouchable > 0 ? 1 : 0;
            cout << caractperso.m_nom << " est intouchable l'attaque ne lui fait rien!(dans les dents)" << endl;
        }
        int rand = generRando->genererParJoueur(1, 100);
        if (rand <= caractperso.m_volonte)// si oui il esquive en partie
        {
            float taux = 1 - rand / 100; //taux d'esquive
            valeur *= taux;//
            cout << caractperso.m_nom << " esquive " << taux << " de l'attaque " << endl;
        }
        if (caractperso.m_bouclier > 0)
        {
            float interboubou = caractperso.m_bouclier - valeur;
            caractperso.m_bouclier = interboubou > 0 ? interboubou : 0;
            valeur = -interboubou;
            valeur *= valeur > 0 ? 1 : 0;

            cout << caractperso.m_nom << " absorbe des degats de l'attaque avec son bouclier." << endl;
        }
        valeur -= getArmureMag() + (0.1 * getEndurance());
        valeur *= valeur > 0 ? 1 : 0;
    }
    if (touche == 1 && valeur != 0)
    {
        if (type == "vie")
        {
            touche = -valeur;
            setVie(getVie() - valeur);//ici enleve vie

            if (caractperso.m_vie < 0)
            {
                setVie(0);
                isDead();
            }
            else if (getVie() > getVieMax())
            {
                setVie(getVieMax());
            }
            cout << caractperso.m_nom << (valeur < 0 ? " gagne " : " perd ") << (int) -valeur << " point de " << type << endl;
        }
        else if (type == "radiation")
        {
            touche = -valeur;
            setRadiation(getRadiation() - valeur);//ici enleve rad
            if (caractperso.m_radiation < 0)
            {
                setRadiation(0);
            }
            else if (getRadiation() > getRadiationMax())
            {
                setRadiation(getRadiationMax());
            }
            cout << caractperso.m_nom << (valeur < 0 ? " gagne " : " perd ") << (int) -valeur << " point de " << type << endl;
        }
        else
        {
            cout << " Erreur de type(ligne~1298AbstractPerso) " << type << endl;
            touche = 0;
        }
    }
    return touche;
}

float AbstractPerso::recevoirEvenementPhysique(float valeur, std::string type)
{
    /*
     * Methode recevoirEvenementPhysique gere tout ce qui concerne l'ajout ou la diminution
     * de vie ou de radiation losqu'il s'agit d'un evenement physique
     * retourne si a été touché
     */

    float touche = 1;
    if (valeur > 0) //physique + degat moins: esquive et armure et 10%endu
    {
        if (caractperso.m_intouchable > 0)
        {
            touche = 0;
            caractperso.m_intouchable--;
            caractperso.m_intouchable *= caractperso.m_intouchable > 0 ? 1 : 0;
            cout << caractperso.m_nom << " est intouchable l'attaque ne lui fait rien!(dans les dents)" << endl;
        }
        int rand = generRando->genererParJoueur(1, 100);
        if (rand <= caractperso.m_agilite)// si oui il esquive en partie
        {
            float taux = 1.0 - rand / 100.0; //taux d'esquive
            valeur *= taux;//
            cout << caractperso.m_nom << " esquive " << (float) taux << " de l'attaque " << endl;
        }
        if (caractperso.m_bouclier > 0)
        {
            float interboubou = caractperso.m_bouclier - valeur;
            caractperso.m_bouclier = interboubou > 0 ? interboubou : 0;
            valeur = -interboubou;
            valeur *= valeur > 0 ? 1 : 0;

            cout << caractperso.m_nom << " absorbe des degats de l'attaque avec son bouclier." << endl;
        }
        valeur -= (getArmure() + 0.1 * getEndurance());
        valeur *= valeur > 0 ? 1 : 0;
    }
    if (touche == 1 && valeur != 0)
    {
        if (type == "vie")
        {
            touche = -valeur;
            setVie(getVie() - valeur);//ici enleve vie

            if (caractperso.m_vie < 0)
            {
                setVie(0);
                isDead();
            }
            else if (getVie() > getVieMax())
            {
                setVie(getVieMax());
            }
            cout << caractperso.m_nom << (valeur < 0 ? " gagne " : " perd ") << (int) -valeur << " point de " << type << endl;
        }
        else if (type == "radiation")
        {
            touche = -valeur;
            setRadiation(getRadiation() - valeur);//ici enleve rad
            if (caractperso.m_radiation < 0)
            {
                setRadiation(0);
            }
            else if (getRadiation() > getRadiationMax())
            {
                setRadiation(getRadiationMax());
            }
            cout << caractperso.m_nom << (valeur < 0 ? " gagne " : " perd ") << (int) -valeur << " point de " << type << endl;
        }
        else
        {
            cout << " Erreur de type(ligne~1376AbstractPerso) " << type << endl;
            touche = 0;
        }
    }

    return touche;
}

