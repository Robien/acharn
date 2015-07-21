/*
 * AbstractPerso.h
 *
 * Gestion des personnages
 *
 *  Created on: fort longtemps
 *      Author: céphise
 */

#ifndef ABSTRACTPERSO_H_INCLUDED
#define ABSTRACTPERSO_H_INCLUDED

#include <list>
#include <vector>
#include "hasard.h"
#include "ObjetEquipement.h"
#include "AbstractArme.h"
#include "AbstractObjSimple.h"
#include "ArmeDistance.h"
#include "ArmeContact.h"
#include "ObjetConsommable.h"
#include "Attaque.h"
#include "SousAttaque.h"
#include "Interpreteur.h"
#include "Caracteristique.h"
#include "Equipement.h"
#include "Sac.h"
#include "Perso.h"
#include "CallbackInfoPerso.h"
#include "CallbackIncantation.h"
#include "PointeurIntelligent.h"

using namespace std;
using namespace irr;

class AbstractPerso: public Perso
{
public:
    struct t_degatrecu
    {
        float degat;
        string personne;
        string type;
    };

public:

    //constructeur & destructeur
    /////supprimer les paramettres par défaut pour callback et eventuelement les deplacer!!
    AbstractPerso(IrrlichtDevice* device, int init = 0, CallbackIncantation* callbackIncant = NULL);
    AbstractPerso(IrrlichtDevice* device, string nom, int init = 0, CallbackIncantation* callbackIncant = NULL); //deprecated
    AbstractPerso(string infojoueur, IrrlichtDevice* device, int init, CallbackIncantation* callbackIncant = NULL); //deprecated
    virtual ~AbstractPerso();

    //affichage console
    void affiEtat(); //deprecated

    //Gestion des objets:
    AbstractObjet* creerObjet(string infoObjet);

    ///-Arme
    ////position: 0 pour mains droit, 1 pour mains gauche, 2 pour deux mains
    bool equiperArme(AbstractArme* arme, int position); //retourne vrai si l'arme a pu etre ajouté
    vector<AbstractArme*> changerArme(AbstractArme* arme, int position); //retourne eventuelement les armes deja portées
    AbstractArme* desequiperArme(int position);
    bool isArme2M(); //return true s'il porte une areme a deux mains
    bool haveArme(); //retrun true s'il porte une arme

    ///-Equipement
    void equiper(ObjetEquipement* copie);
    void desequiper(ObjetEquipement::e_Position position);
    void addBonus(Caracteristique add);
    void delBonus(Caracteristique del);
    bool haveEquipement(ObjetEquipement::e_Position position);

    ///-Objet & Sac
    void mettreDansSac(AbstractObjet* item);
    void SortirDeSac(int numitem);

    //Etat Joueur
    bool estVivant();
    bool occupe(float currenttime);
    virtual void isDead();

    //Getters
    Random* getRandom();
    float getOccupe();
    float getArgent();
    virtual float getRadiation();
    virtual float getVie();
    virtual float getRadiationMax();
    virtual float getVieMax();
    float getEndurance();
    virtual int getNiveau();
    int getInit();
    float getArmure();
    float getArmureMag();
    virtual std::string getNom();
    Caracteristique* getCaracteristique();
    int donnexp(AbstractPerso &vainqueur);
    PersoJoueur* getLastAttaquant();

    //sauvegarde
    virtual string saveCara();
    string saveEquip();
    string saveSac();
    string saveComp();

    //setters
    void regeneration();
    void addoccupe(float tpocc, float currenttime);
    void setoccupe(float tpocc, float currenttime);
    virtual void setRadiation(float rad);
    virtual void setVie(float vie);
    virtual void setRadiationMax(float radm);
    virtual void setVieMax(float viem);
    void setInfo(string infojoueur, int init);
    void initocc();
    virtual void addNiveau();
    void addArgent(float money);
    bool delArgent(float money);
    void setCallbackIncantation(CallbackIncantation* callback);
    // void setInit(int init); //deprecated
    void addCaracteristique(Caracteristique* add);

    //Competence
    void newCompetence(std::string atk);
    string afficherCompetences();
    bool deleteCompetence(int i);// resturn false si echec

    //Attaques
    string attaquer(AbstractPerso &cible, float currenttime);//premier attaque //deprecated
    string attaquer(AbstractPerso &cible, int numattaque, float currenttime);//deprecated
    string attaquer(AbstractPerso &cible, string atkbyserveur, float currenttime);//deprecated
    string attaquer(float currenttime, int numattaque = 0);
    string attaquer(float currenttime, string atkbyserveur);
    vector<string>* endOfIncantation(std::vector<AbstractPerso*>& cibles, float currenttime);
    vector<string>* endOfIncantation(std::vector<AbstractPerso*>& cibles, float currenttime, string atkbyserveur);
    void endOfIncantation(); //si l'incantation a été stoppé annule l'incantation en cour
    std::vector<t_degatrecu> effectuerAtk(float time);
    bool isOnIncantation();
    void affecte(Attaque atk, float currentTime);
    void viderliste();


private:

    float recevoirEvenement(float valeur, std::string type, int typeatk, float time);
    float recevoirEvenementMagic(float valeur, std::string type);
    float recevoirEvenementPhysique(float valeur, std::string type);

private:

    Equipement m_Equipement;
    Sac m_sac;
    Caracteristique caractperso;
    float m_argent;
    std::vector<std::string> l_competence;
    std::vector<Attaque> l_atkRecu;
    PointeurIntelligent<CallbackIncantation> _callbackIncantation;
    float finIncantation;
    PointeurIntelligent<Interpreteur> competenceEnIncant;
    //Interpreteur* competenceEnIncant;
    PersoJoueur* lastAttaquant;
    int attaqueASup;

protected:

    //Random* generRando;
    PointeurIntelligent<Random> generRando;

};

#endif // ABSTRACTPERSO_H_INCLUDED
