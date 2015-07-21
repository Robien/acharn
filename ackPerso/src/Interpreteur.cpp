/*
 * Interpreteur.cpp
 *
 *  Created on: 12 juin 2010
 *      Author: cephise
 */

#include "Interpreteur.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include "base.h"
#include "Caracteristique.h"
#include "hasard.h"
using namespace std;

Interpreteur::Interpreteur(Caracteristique* src, Random* randsrc, Caracteristique* cib, const string atq, bool sousatt) :
    ls(atq), attaque()
{
    saveAttaque = atq;
    sAttaque = "<";
    m_verification = true;
    reversible = false;
    justIncant = false;
    critique = false;
    if (sousatt)
    {
        attaque = new SousAttaque();
    }
    else
    {
        attaque = new Attaque();
    }
    SsAtt = sousatt;
    source = src;
    cible = cib;
    randomSource = randsrc;
    attri.affect = "vie";
    attri.affectcout = "radiation";
    attri.cout = 0;
    attri.degat = 0;
    attri.nom = "attaquevide";
    attri.pas = 1;
    attri.tps = 0;
    attri.type = 0;
    attri.cooldown = 0;
    attri.parcoup = 0;
    attri.reverse = 0;
    attri.incantation = 0;
    attri.portee = -1;
    attri.crit = 2;
}

Interpreteur::Interpreteur(Caracteristique* src, Random* randsrc, const string atq, bool sousatt) :
    ls(atq), attaque()
{
    saveAttaque = atq;
    sAttaque = "<";
    m_verification = true;
    reversible = false;
    justIncant = true;
    critique = false;
    if (sousatt)
    {
        attaque = new SousAttaque();
    }
    else
    {
        attaque = new Attaque();
    }
    SsAtt = sousatt;
    source = src;
    cible = NULL;
    randomSource = randsrc;
    attri.affect = "vie";
    attri.affectcout = "radiation";
    attri.cout = 0;
    attri.degat = 0;
    attri.nom = "attaquevide";
    attri.pas = 1;
    attri.tps = 0;
    attri.type = 0;
    attri.cooldown = 0;
    attri.parcoup = 0;
    attri.reverse = 0;
    attri.incantation = 0;
    attri.portee = -1;
    attri.crit = 2;
}

bool Interpreteur::analyseIncantation(float &incantation, int &type, float &portee)
{
    incantation = 0;
    type = 0;
    portee = -1;
    bool erreur = false;
    LecteurSymbole lects(saveAttaque);

    while (!erreur && lects.getSymCour() != ">" && lects.getSymCour() != "<FINDATTAQUE>")
    {
        if (lects.getSymCour() == "<ATTRIBUT>")
        {
            if (lects.getSymCour() == "#incant")
            {
                lects.suivant();
                if (lects.getSymCour() != "=")
                {
                    cout << endl << "-------- Erreur: Attendu : = Trouvé " << lects.getSymCour().getChaine() << endl;
                    erreur = true;
                }
                lects.suivant();
                incantation = expression();
            }
            else if (lects.getSymCour() == "#type")
            {
                lects.suivant();
                if (lects.getSymCour() != "=")
                {
                    cout << endl << "-------- Erreur: Attendu : = Trouvé " << lects.getSymCour().getChaine() << endl;
                    erreur = true;
                }
                lects.suivant();
                type = expression();
            }
            else if (lects.getSymCour() == "#port")
            {
                lects.suivant();
                if (lects.getSymCour() != "=")
                {
                    cout << endl << "-------- Erreur: Attendu : = Trouvé " << lects.getSymCour().getChaine() << endl;
                    erreur = true;
                }
                lects.suivant();
                portee = expression();

            }
            else
            {
                lects.suivant();
            }

        }
        else
        {
            lects.suivant();
        }
    }

    if (portee == -1)
    {
        if (type >= 10)
        {
            portee = 10;
        }
        else
        {
            portee = 1;
        }
    }
    cout << "ICI::" << erreur << endl;
    return erreur;
}

SousAttaque* Interpreteur::analyse()
{//	<affectation> ::= {<attribut> = <expression> | <sousAttaque> } >


    while (ls.getSymCour() != ">" && ls.getSymCour() != "<FINDATTAQUE>")
    {
        if (ls.getSymCour() == "<ATTRIBUT>")
        {

            sAttaque += ls.getSymCour().getChaine();

            if (ls.getSymCour() == "#nom")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.nom = getChaine();
            }
            else if (ls.getSymCour() == "#affect")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.affect = getChaine();
                if (attri.reverse == 0 && attri.affect != "vie" && attri.affect != "radiation" && attri.affect != "occupe")
                {
                    attri.reverse = 20;
                    reversible = reversible || (attri.reverse > 0 ? true : false);
                }
            }
            else if (ls.getSymCour() == "#affectcout")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.affectcout = getChaine();

            }
            else if (ls.getSymCour() == "#degat")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.degat = expression();
            }
            else if (ls.getSymCour() == "#tps")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.tps = expression();
            }
            else if (ls.getSymCour() == "#type")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.type = expression();
            }
            else if (ls.getSymCour() == "#pas")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.pas = expression();
            }
            else if (ls.getSymCour() == "#cooldown")
            {
                cout << "!!!!!!!!!!!!J'ai ton cd" << endl;
                ls.suivant();
                sauterSymCour("=");
                attri.cooldown = expression();
            }
            else if (ls.getSymCour() == "#cout")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.cout = expression();
            }
            else if (ls.getSymCour() == "#rever")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.reverse = expression();
                reversible = reversible || (attri.reverse > 0 ? true : false);
            }
            else if (ls.getSymCour() == "#incant")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.incantation = expression();
            }
            else if (ls.getSymCour() == "#port")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.portee = expression();
            }
            else if (ls.getSymCour() == "#crit")
            {
                ls.suivant();
                sauterSymCour("=");
                expression();

            }
            else if (ls.getSymCour() == "#critcoef")
            {
                ls.suivant();
                sauterSymCour("=");
                attri.crit = expression();
            }
            else
            {
                cout << "erreur aucune attribut trouvé3";
            }

        }
        else if (ls.getSymCour() == "<SOUSATTAQUE>" && !SsAtt)
        {
            Interpreteur interSSAtt(source, randomSource, cible, ls.getSymCour().getChaine());
            SousAttaque att = *(interSSAtt.analyse());
            reversible = reversible || interSSAtt.isReverse();
            ((Attaque*) attaque)->ajouterEffet(att);
            sAttaque += interSSAtt.getAttaqueString();
            ls.suivant();
            //crée une autre attaque
        }
    }

    if (attri.portee == -1)
    {
        if (attri.type >= 10)
        {
            attri.portee = 10;
        }
        else
        {
            attri.portee = 1;
        }
    }
    if (!critique)
    {
        attri.crit = 1;
    }

    attaque->setAttribut(attri);
    sAttaque += ">";

    return attaque;
}

void Interpreteur::setCible(Caracteristique* cib)
{
    cible = cib;
    justIncant = false;
    reinitialiser();
}

void Interpreteur::reinitialiser()
{
    ls = LecteurSymbole(saveAttaque);

    sAttaque = "<";
    m_verification = true;
    reversible = false;
    critique = false;
    attaque = new Attaque();
    SsAtt = false;
    attri.affect = "vie";
    attri.affectcout = "radiation";
    attri.cout = 0;
    attri.degat = 0;
    attri.nom = "attaquevide";
    attri.pas = 1;
    attri.tps = 0;
    attri.type = 0;
    attri.cooldown = 0;
    attri.parcoup = 0;
    attri.reverse = 0;
    attri.incantation = 0;
    attri.portee = -1;
    attri.crit = 2;
}

SousAttaque* Interpreteur::getAttaque()
{
    return attaque;
}

std::string Interpreteur::getAttaqueString()
{
    return sAttaque;
}

bool Interpreteur::getVerification()
{
    return m_verification;
}

bool Interpreteur::isReverse()
{
    return reversible;
}

SousAttaque* Interpreteur::getReverse()
{
    if (isReverse())
    {
        t_attribut attreverse;
        t_attribut att = attaque->getAttribut();
        Attaque* reverseAttaque = new Attaque();
        if (att.reverse > 0)
        {
            attreverse.degat = -att.degat;
            attreverse.tps = att.reverse;
            attreverse.type = att.type;
            attreverse.pas = 1;
            attreverse.nom = "reverse_" + att.nom;
            attreverse.affect = att.affect;
            attreverse.cout = 0;
            attreverse.affectcout = att.affectcout;
            attreverse.cooldown = 0;
            attreverse.reverse = 0;
            attreverse.incantation = 0;
            attreverse.parcoup = 0;
            if (critique)
            {
                attreverse.crit = att.crit;
            }
            else
            {
                attreverse.crit = 1;
            }
            attri.portee = att.portee;
        }
        else
        {
            attreverse.degat = 0;
            attreverse.tps = 0;
            attreverse.type = att.type;
            attreverse.pas = 0;
            attreverse.nom = "reverse_" + att.nom;
            attreverse.affect = att.affect;
            attreverse.cout = 0;
            attreverse.affectcout = att.affectcout;
            attreverse.cooldown = 0;
            attreverse.reverse = 0;
            attreverse.incantation = 0;
            attreverse.parcoup = 0;
            attreverse.crit = 1;
            attri.portee = 1;
        }

        reverseAttaque->setAttribut(attreverse);
        vector<SousAttaque>* sousattaques = ((Attaque*) attaque)->getEffet();
        for (unsigned int i = 0; i < sousattaques->size(); i++)
        {
            if (sousattaques->at(i).getReverse() > 0)
            {
                SousAttaque reverseSousAttaque;
                t_attribut ssattreverse;
                t_attribut ssatt = sousattaques->at(i).getAttribut();
                ssattreverse.degat = -ssatt.degat;
                ssattreverse.tps = ssatt.reverse;
                ssattreverse.type = ssatt.type;
                ssattreverse.pas = 1;
                ssattreverse.nom = "reverse_" + ssatt.nom;
                ssattreverse.affect = ssatt.affect;
                ssattreverse.cout = 0;
                ssattreverse.affectcout = ssatt.affectcout;
                ssattreverse.cooldown = 0;
                ssattreverse.reverse = 0;
                ssattreverse.incantation = 0;
                ssattreverse.parcoup = 0;
                ssattreverse.crit = ssatt.crit;
                if (critique)
                {
                    ssattreverse.crit = ssatt.crit;
                }
                else
                {
                    ssattreverse.crit = 1;
                }
                ssattreverse.portee = ssatt.portee;
                reverseSousAttaque.setAttribut(ssattreverse);
                reverseAttaque->ajouterEffet(reverseSousAttaque);
            }
        }

        return reverseAttaque;
    }
    else
    {
        return NULL;
    }
}

float Interpreteur::expression()
{//	<expression> ::=   <terme> { + | - | * | / | %   <terme>}
    float resultat = 0.0, verif = 0.0;
    bool verification = false;

    if (ls.getSymCour() == "<CARACTERISTIQUE>" || ls.getSymCour() == "<VALEUR>" || ls.getSymCour() == "(" || ls.getSymCour() == "Random(")
    {
        resultat = terme();
        while (ls.getSymCour() == "<MOTCLE>" && ls.getSymCour() != ")")
        {
            sAttaque += ls.getSymCour().getChaine();
            if (ls.getSymCour() == "+")
            {
                ls.suivant();
                resultat += terme();
            }
            else if (ls.getSymCour() == "-")
            {
                ls.suivant();
                resultat -= terme();
            }
            else if (ls.getSymCour() == "*")
            {
                ls.suivant();
                resultat *= terme();
            }
            else if (ls.getSymCour() == "==")
            {
                ls.suivant();
                critique = (resultat == terme());
                resultat = (critique ? 0 : -1);
            }
            else if (ls.getSymCour() == "<=")
            {
                ls.suivant();
                critique = (resultat <= terme());
                resultat = (critique ? 0 : -1);
            }
            else if (ls.getSymCour() == ">=")
            {
                ls.suivant();
                critique = (resultat >= terme());
                resultat = (critique ? 0 : -1);
            }
            else if (ls.getSymCour() == "/")
            {
                ls.suivant();
                float tmp = terme();
                if (tmp != 0)
                    resultat = resultat / tmp;
            }
            else if (ls.getSymCour() == "=")//verification
            {
                float signe = 1;
                ls.suivant();
                if (ls.getSymCour() == "-")
                {
                    ls.suivant();
                    signe = -1;
                }
                verif = terme() * signe;
                verification = true;
            }
            else
            {
                ls.suivant();
                cout << "erreur dans l'attaque, probleme attend un motclé" << endl;
            }

        }

    }

    if (verification)
    {
        if (resultat != verif)
        {
            cout << "Erreur dans la verification trouvé: " << converstr(resultat) << " au lieu de: " << converstr(verif) << endl;
        }
        m_verification = m_verification && (resultat == verif);
    }
    else
    {
        sAttaque += "=";
        sAttaque += converstr(resultat);
    }
    return resultat;
}

////////////

float Interpreteur::terme()
{//	<terme> ::=   <caracteristique> | <valeur> | ( <terme>%<expression> ) | Random(<terme>[<terme>])

    float res = -1;
    if (ls.getSymCour() == "<CARACTERISTIQUE>")
    {
        string chaine;
        sAttaque += ls.getSymCour().getChaine();
        chaine = ls.getSymCour().getChaine();
        if (chaine[0] == '$')
        {//caracteristique de la source
            //cara =source.getCaracteristique();
            chaine.erase(chaine.begin());
            res = source->recherche(chaine);
        }
        else if (chaine[0] == '@')
        {//caracteristique de la cible
            //cara =cible.getCaracteristique();
            chaine.erase(chaine.begin());
            res = cible->recherche(chaine);
        }

        ls.suivant();
    }
    else if (ls.getSymCour() == "<VALEUR>")
    {
        sAttaque += ls.getSymCour().getChaine();
        res = converfl(ls.getSymCour().getChaine());
        ls.suivant();
    }
    else if (ls.getSymCour() == "<MOTCLE>")
    {
        if (ls.getSymCour() == "(")
        {
            sauterSymCour("(");
            float pourcent = terme() / 100;
            sauterSymCour("%");
            res = expression() * pourcent;
            sauterSymCour(")");
        }
        else if (ls.getSymCour() == "Random(")
        {
            sauterSymCour("Random(");
            float valeur = terme();
            if (ls.getSymCour() == "[") //normalement juste quand il y a une verification
            {
                sauterSymCour("[");
                res = randomSource->genererParJoueur(0, valeur, terme(), cible->m_init);//recuperartion du meme random que la cible
                sauterSymCour("]");
            }
            else
            {
                sAttaque += "[";
                sAttaque += converstr(randomSource->getNumero());
                sAttaque += "]";
                res = randomSource->genererParJoueur(0, valeur);
            }

            sauterSymCour(")");
        }
    }
    else
    {
        cout << "erreur dans l'attaque(2) attendu motclé '(' ou valeur ou caracteristique" << endl;
    }

    return res;
}

std::string Interpreteur::getChaine()
{
    string chaine, res;
    sAttaque += ls.getSymCour().getChaine();
    chaine = ls.getSymCour().getChaine();
    res.append(chaine, 1, chaine.size() - 2);
    ls.suivant();
    return res;
}

bool Interpreteur::testerSymCour(string ch)
{

    if (ls.getSymCour() != ch)
    {
        cout << endl << "-------- Erreur: Attendu : " << ch << " Trouvé " << ls.getSymCour().getChaine() << endl;
        return false;
    }
    else
        return true;
}

////////////////////////////////////////////////////////////////////////////////
bool Interpreteur::sauterSymCour(string ch)
{
    bool rep = testerSymCour(ch);
    sAttaque += ls.getSymCour().getChaine();
    ls.suivant();
    return rep;
}
