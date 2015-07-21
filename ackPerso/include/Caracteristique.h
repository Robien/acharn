/*
 * Caracteristique.h
 *
 *  Created on: 15 juin 2010
 *      Author: cephise
 */

#ifndef CARACTERISTIQUE_H_
#define CARACTERISTIQUE_H_

#include "const.h"
#include "hasard.h"

struct Caracteristique
{
public:

    Caracteristique()
    {
        m_nom = "";
        m_radiation = 0;
        m_radiationMax = 0;
        m_niveau = 0;
        m_vitessemv = 0;
        m_ccombat = 0;
        m_force = 0;
        m_endurance = 0;
        m_initiative = 0;
        m_volonte = 0;
        m_inteligence = 0;
        m_ctir = 0;
        m_agilite = 0;
        m_puissance = m_force;
        m_bouclier = 0;
        m_intouchable = 0;
        m_vie = 0;
        m_vieMax = 0;
        initialised = false;
    }

    float recherche(std::string cara)
    {
        if (cara == "vie")
            return m_vie;
        else if (cara == "vieMax")
            return m_vieMax;
        else if (cara == "radiation")
            return m_radiation;
        else if (cara == "radiationMax")
            return m_radiationMax;
        else if (cara == "vitessemv")
            return m_vitessemv;
        else if (cara == "ccombat")
            return m_ccombat;
        else if (cara == "ctir")
            return m_ctir;
        else if (cara == "force")
            return m_force;
        else if (cara == "endurance")
            return m_endurance;
        else if (cara == "agilite")
            return m_agilite;
        else if (cara == "initiative")
            return m_initiative;
        else if (cara == "volonte")
            return m_volonte;
        else if (cara == "inteligence")
            return m_inteligence;
        else if (cara == "niveau")
            return (float) m_niveau;
        else if (cara == "initialisateur")
            return (float) m_init;
        else if (cara == "puissance")
            return (float) m_puissance;
        else if (cara == "bouclier")
            return (float) m_bouclier;
        else if (cara == "intouchable")
            return (float) m_intouchable;

        else
            return -1;
    }

    void setAttribut(std::string cara, float val)
    {
        if (cara == "vie")
            m_vie = val;
        else if (cara == "vieMax")
            m_vieMax = val;
        else if (cara == "radiation")
            m_radiation = val;
        else if (cara == "radiationMax")
            m_radiationMax = val;
        else if (cara == "vitessemv")
            m_vitessemv = val;
        else if (cara == "ccombat")
            m_ccombat = val;
        else if (cara == "ctir")
            m_ctir = val;
        else if (cara == "force")
            m_force = val;
        else if (cara == "endurance")
            m_endurance = val;
        else if (cara == "agilite")
            m_agilite = val;
        else if (cara == "initiative")
            m_initiative = val;
        else if (cara == "volonte")
            m_volonte = val;
        else if (cara == "inteligence")
            m_inteligence = val;
        else if (cara == "niveau")
            m_niveau = (int) val;
        else if (cara == "puissance")
            m_puissance = val;
        else if (cara == "bouclier")
            m_bouclier = val;
        else if (cara == "intouchable")
            m_intouchable = val;

    }

    void setAttribut(vector<std::string> vectcarac)
    {
        if (vectcarac.size() >= 15)
        {
            m_nom = vectcarac[0];
            m_vie = converfl(vectcarac[1]);
            m_vieMax = converfl(vectcarac[2]);
            m_radiation = converfl(vectcarac[3]);
            m_radiationMax = converfl(vectcarac[4]);
            m_niveau = (int) converfl(vectcarac[5]);
            m_vitessemv = converfl(vectcarac[6]);
            m_ccombat = converfl(vectcarac[7]);
            m_force = converfl(vectcarac[8]);
            m_endurance = converfl(vectcarac[9]);
            m_initiative = converfl(vectcarac[10]);
            m_volonte = converfl(vectcarac[11]);
            m_inteligence = converfl(vectcarac[12]);
            m_ctir = converfl(vectcarac[13]);
            m_agilite = converfl(vectcarac[14]);
            m_puissance = m_force;
            initialised = true;
        }

    }

    string enChaine(bool withoutname = false)
    {
        string info;
        if (!withoutname)
        {
            info = m_nom + ",";
        }
        info += converstr(m_vie) + ",";
        info += converstr(m_vieMax) + ",";
        info += converstr(m_radiation) + ",";
        info += converstr(m_radiationMax) + ",";
        info += converstr(m_niveau) + ",";
        info += converstr(m_vitessemv) + ",";
        info += converstr(m_ccombat) + ",";
        info += converstr(m_force) + ",";
        info += converstr(m_endurance) + ",";
        info += converstr(m_initiative) + ",";
        info += converstr(m_volonte) + ",";
        info += converstr(m_inteligence) + ",";
        info += converstr(m_ctir) + ",";
        info += converstr(m_agilite);

        return info;
    }

    void opeCaracteristique(Caracteristique cara2, bool add)
    {
        if (add)
        {
            m_vie += cara2.m_vie;
            m_vieMax += cara2.m_vieMax;
            m_radiation += cara2.m_radiation;
            m_radiationMax += cara2. m_radiationMax;
            m_vitessemv += cara2.m_vitessemv;
            m_ccombat += cara2.m_ccombat;
            m_ctir += cara2. m_ctir;
            m_force += cara2.m_force;
            m_endurance += cara2.m_endurance;
            m_agilite += cara2. m_agilite;
            m_initiative += cara2.m_initiative;
            m_volonte += cara2.m_volonte;
            m_inteligence += cara2.m_inteligence;
            m_niveau += cara2.m_niveau;
            m_puissance += cara2.m_puissance;

        }
        else
        {
            m_vie -= cara2.m_vie;
            m_vieMax -= cara2.m_vieMax;
            m_radiation -= cara2.m_radiation;
            m_radiationMax -= cara2. m_radiationMax;
            m_vitessemv -= cara2.m_vitessemv;
            m_ccombat -= cara2.m_ccombat;
            m_ctir -= cara2. m_ctir;
            m_force -= cara2.m_force;
            m_endurance -= cara2.m_endurance;
            m_agilite -= cara2. m_agilite;
            m_initiative -= cara2.m_initiative;
            m_volonte -= cara2.m_volonte;
            m_inteligence -= cara2.m_inteligence;
            m_niveau -= cara2.m_niveau;
            m_puissance -= cara2.m_puissance;

        }
    }

    void opePuissance(float puissance, bool add)
    {
        if (add)
        {
            m_puissance += puissance;
        }
        else
        {
            m_puissance -= puissance;
        }
    }

    std::string toString()
    {
        string str;
        if (m_vie != 0)
            str += "vie:" + converstr(m_vie) + "\n";
        if (m_vieMax != 0)
            str += "vie max:" + converstr(m_vieMax) + "\n";
        if (m_radiation != 0)
            str += "radiation" + converstr(m_radiation) + "\n";
        if (m_radiationMax != 0)
            str += "radiationMax" + converstr(m_radiationMax) + "\n";
        if (m_vitessemv != 0)
            str += "vitessemv" + converstr(m_vitessemv) + "\n";
        if (m_ccombat != 0)
            str += "ccombat" + converstr(m_ccombat) + "\n";
        if (m_ctir != 0)
            str += "ctir" + converstr(m_ctir) + "\n";
        if (m_force != 0)
            str += "force" + converstr(m_force) + "\n";
        if (m_endurance != 0)
            str += "endurance" + converstr(m_endurance) + "\n";
        if (m_agilite != 0)
            str += "agilite" + converstr(m_agilite) + "\n";
        if (m_initiative != 0)
            str += "initiative" + converstr(m_initiative) + "\n";
        if (m_volonte != 0)
            str += "volonte" + converstr(m_volonte) + "\n";
        if (m_inteligence != 0)
            str += "inteligence" + converstr(m_inteligence) + "\n";
        if (m_niveau != 0)
            str += "niveau" + converstr(m_niveau) + "\n";
        if (m_puissance != 0)
            str += "m_puissance" + converstr(m_puissance) + "\n";

        return str;
    }

    bool isInitialised()
    {
        return initialised;
    }

    float m_vie; //vie du personnage (départ:150)
    float m_vieMax;
    float m_radiation; // permet de lancer des sort(équivalent au mana) (départ:100)
    float m_radiationMax;
    float m_vitessemv; //vitesse de mouvement du personnage (départ:)
    float m_ccombat; //capacité combat chance de touché l'adversaire en combat corps à corps (départ:) sur 100
    float m_ctir; //capacité de tir chance de touché l'adversaire a distance (départ:)
    float m_force; //Puissance de force en corps a corps (départ:50/100)
    float m_endurance; //capacité à recevoir les coups (départ:50/100)
    float m_agilite; //rapidité de réaction (éviter les coups) (départ:)
    float m_initiative; //d'enchainé les attaques (départ:) sur 100
    float m_volonte; //résistance mental et magie (départ:)
    float m_inteligence; //permet de calculer la radiation et attaque magique (départ:)
    float m_occupe;
    float m_puissance;
    float m_bouclier; //la valeur en positif correspond a la valeur absorbé
    int m_intouchable;//chaque point en positif est une attaque bloqué completement
    int m_niveau; //niveau du personnage (départ:)
    std::string m_nom;
    int m_init;
private:
    bool initialised;
};
#endif /* CARACTERISTIQUE_H_ */
