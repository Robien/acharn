/*
 * Sauvegarde.cpp
 *
 *  Created on: 24 sept. 2010
 *      Author: cephise
 */

#include "Sauvegarde.h"
using namespace std;
Sauvegarde::Sauvegarde()
{
    // TODO Auto-generated constructor stub
    mutex.reset(new boost::mutex);

}
Sauvegarde::Sauvegarde(CSimpleIniCaseA* Filebackup)
{
    // TODO Auto-generated constructor stub
    File = Filebackup;
    mutex.reset(new boost::mutex);
}
Sauvegarde::~Sauvegarde()
{
    CSimpleIniCaseA::TNamesDepend listpersonnes;
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        File->GetAllSections(listpersonnes);
    }
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        CSimpleIniCaseA::TNamesDepend::iterator it;
        for (it = listpersonnes.begin(); it != listpersonnes.end(); it++)
        {
            File->SetBoolValue(it->pItem, "isconnect", false);
        }
    }
    // TODO Auto-generated destructor stub
}

string Sauvegarde::sauvegardeInfo(string info, string &pseudo)
{
    pseudo = "";
    vector<std::string> infojoueur = split(info.c_str(), ',', false);
    if (infojoueur.size() >= 16)
    {
        int existe;
        {
            boost::mutex::scoped_lock lock(*mutex.get());
            existe = File->GetSectionSize(infojoueur[1].c_str());
        }
        if (existe != -1)//n'existe pas, sauvegarde possible
        {
            pseudo = infojoueur[1];
            {
                boost::mutex::scoped_lock lock(*mutex.get());
                File->SetValue(pseudo.c_str(), "PointExperience", infojoueur[0].c_str());
                File->SetValue(pseudo.c_str(), "Vie", infojoueur[2].c_str());
                File->SetValue(pseudo.c_str(), "VieMax", infojoueur[3].c_str());
                File->SetValue(pseudo.c_str(), "Radiation", infojoueur[4].c_str());
                File->SetValue(pseudo.c_str(), "RadiationMax", infojoueur[5].c_str());
                File->SetValue(pseudo.c_str(), "Niveau", infojoueur[6].c_str());
                File->SetValue(pseudo.c_str(), "Vitesse", infojoueur[7].c_str());
                File->SetValue(pseudo.c_str(), "CapaCombat", infojoueur[8].c_str());
                File->SetValue(pseudo.c_str(), "Force", infojoueur[9].c_str());
                File->SetValue(pseudo.c_str(), "Endurance", infojoueur[10].c_str());
                File->SetValue(pseudo.c_str(), "Initiative", infojoueur[11].c_str());
                File->SetValue(pseudo.c_str(), "Volonte", infojoueur[12].c_str());
                File->SetValue(pseudo.c_str(), "Inteligence", infojoueur[13].c_str());
                File->SetValue(pseudo.c_str(), "CapaTir", infojoueur[14].c_str());
                File->SetValue(pseudo.c_str(), "Agilite", infojoueur[15].c_str());
                File->SetBoolValue(pseudo.c_str(), "isconnect", false);
                File->SaveFile("sauvegarde.dadu");
            }
            cout << "-->Sauvegarde du personnage " <<pseudo << " reussi" << endl;
            return "";
        }
        else
        {
            return "Erreur: Sauvegarde impossible, login(" + pseudo + ") inexistant";
        }
    }
    else
    {
        return "Erreur: Sauvegarde impossible, nombre de donnée insuffisant";
    }

}

string Sauvegarde::sauvegardeInfoCompetence(string comp, string pseudo)
{
    string err = "";
    {
        boost::mutex::scoped_lock lock(*mutex.get());

        int existe = File->GetSectionSize(pseudo.c_str());
        if (existe != -1)//n'existe pas création possible
        {
            vector<std::string> compjoueur = split(comp.c_str(), '!', false);
            if (compjoueur.size() > 0)
            {
                string competences = compjoueur[0];
                for (int i = 1; i < (int) compjoueur.size(); i++)
                {
                    competences += "\n" + compjoueur[i];
                }
                File->SetValue(pseudo.c_str(), "Competences", competences.c_str());
                File->SaveFile("sauvegarde.dadu");
            }

        }
        else
        {
            err = "Erreur: Sauvegarde impossible, login(" + pseudo + ") inexistant";
        }
    }
    return err;
}

string Sauvegarde::sauvegardeInfoTexture(string text, string pseudo)
{
    string err = "";
        {
            boost::mutex::scoped_lock lock(*mutex.get());
            int existe = File->GetSectionSize(pseudo.c_str());
            if (existe != -1)//n'existe pas création possible
            {
                vector<std::string> texturejoueur = split(text.c_str(), '!', false);
                if (texturejoueur.size() > 0)
                {
                    string tex = texturejoueur[0];
                    for (int i = 1; i < (int) texturejoueur.size(); i++)
                    {
                        tex += "\n" + texturejoueur[i];
                    }
                    File->SetValue(pseudo.c_str(), "Texture", tex.c_str());
                    File->SaveFile("sauvegarde.dadu");
                }

            }
            else
            {
                err = "Erreur: Sauvegarde impossible, login(" + pseudo + ") inexistant";
            }
        }
        return err;
}

string Sauvegarde::sauvegardeInfoObjetSac(string insac, string pseudo)
{
    string err = "";
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        int existe = File->GetSectionSize(pseudo.c_str());
        if (existe != -1)//n'existe pas création possible
        {
            vector<std::string> objjoueur = split(insac.c_str(), '!', false);
            if (objjoueur.size() > 0)
            {
                string sac = objjoueur[0];
                for (int i = 1; i < (int) objjoueur.size(); i++)
                {
                    sac += "\n" + objjoueur[i];
                }
                File->SetValue(pseudo.c_str(), "Sac", sac.c_str());
                File->SaveFile("sauvegarde.dadu");
            }

        }
        else
        {
            err = "Erreur: Sauvegarde impossible, login(" + pseudo + ") inexistant";
        }
    }
    return err;
}

string Sauvegarde::sauvegardeInfoObjetEquipement(string infoequi, string pseudo)
{
    string err = "";
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        int existe = File->GetSectionSize(pseudo.c_str());
        if (existe != -1)//n'existe pas création possible
        {
            vector<std::string> equipjoueur = split(infoequi.c_str(), '!', false);
            if (equipjoueur.size() > 0)
            {
                string equip = equipjoueur[0];
                for (int i = 1; i < (int) equipjoueur.size(); i++)
                {
                    equip += "\n" + equipjoueur[i];
                }
                File->SetValue(pseudo.c_str(), "Equipement", equip.c_str());
                File->SaveFile("sauvegarde.dadu");
            }
        }
        else
        {
            err = "Erreur: Sauvegarde impossible, login(" + pseudo + ") inexistant";
        }
    }
    return err;
}

vector<std::string> Sauvegarde::split(const char* data, char separateur, bool conforme)
{

    vector<std::string> resultat;

    //verification de conformitée: au moins deux caracteres puis un separateur
    if ((data[0] != '\0' && data[0] != separateur) && ((!conforme) || (data[0] != '\0' && data[1] != '\0' && data[2] != '\0' && data[2] == separateur)))
    {

        string morceau;
        int i = 0;

        while (data[i] != '\0')
        {
            if (data[i] == separateur && data[i - 1] != '\\')
            {
                resultat.push_back(morceau);
                morceau.clear();
            }
            else
            {
                morceau += data[i];
            }
            i++;
        }
        resultat.push_back(morceau);
    }//sinon retour d'un vecteur vide
    return resultat;
}

//////////Recuperation d'information


string Sauvegarde::recupInfo(string pseudo)
{
    string info = "";
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        int existe = File->GetSectionSize(pseudo.c_str());
        if (existe != -1)//n'existe pas création possible
        {
            const CSimpleIniCaseA::TKeyVal* mymm = File->GetSection(pseudo.c_str());
            info = mymm->find("PointExperience")->second;
            info += ",";
            info += pseudo + ",";
            info += mymm->find("Vie")->second;
            info += ",";
            info += mymm->find("VieMax")->second;
            info += ",";
            info += mymm->find("Radiation")->second;
            info += ",";
            info += mymm->find("RadiationMax")->second;
            info += ",";
            info += mymm->find("Niveau")->second;
            info += ",";
            info += mymm->find("Vitesse")->second;
            info += ",";
            info += mymm->find("CapaCombat")->second;
            info += ",";
            info += mymm->find("Force")->second;
            info += ",";
            info += mymm->find("Endurance")->second;
            info += ",";
            info += mymm->find("Initiative")->second;
            info += ",";
            info += mymm->find("Volonte")->second;
            info += ",";
            info += mymm->find("Inteligence")->second;
            info += ",";
            info += mymm->find("CapaTir")->second;
            info += ",";
            info += mymm->find("Agilite")->second;

        }
    }
    return info;
}

vector<string> Sauvegarde::recupComp(string pseudo)
{
    string competences;
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        competences = File->GetValue(pseudo.c_str(), "Competences", "");
    }
    vector<string> v_comp;
    if (competences != "")
    {
        v_comp = split(competences.c_str(), '\n', false);
    }

    //recupere du fichier!!
    return v_comp;

}

vector<string> Sauvegarde::recupObjetSac(string pseudo)
{
    string sac;
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        sac = File->GetValue(pseudo.c_str(), "Sac", "");
    }
    vector<string> v_sac;
    if (sac != "")
    {
        v_sac = split(sac.c_str(), '\n', false);
    }

    //recupere du fichier!!
    return v_sac;

}

vector<string> Sauvegarde::recupObjetEquipement(string pseudo)
{
    string equi;
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        equi = File->GetValue(pseudo.c_str(), "Equipement", "");
    }
    vector<string> v_equi;
    if (equi != "")
    {
        v_equi = split(equi.c_str(), '\n', false);
    }

    //recupere du fichier!!
    return v_equi;

}

vector<string> Sauvegarde::recupTexture(string pseudo)
{
    string tex;
       {
           boost::mutex::scoped_lock lock(*mutex.get());
           tex = File->GetValue(pseudo.c_str(), "Texture", "");
       }
       vector<string> v_tex;
       if (tex != "")
       {
           v_tex = split(tex.c_str(), '\n', false);
       }

       //recupere du fichier!!
       return v_tex;
}

////////////Creation de compte // Connexion
bool Sauvegarde::creerCompte(string pseudo, string pwd)
{
    int existe;
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        existe = File->GetSectionSize(pseudo.c_str());
    }
    if (existe == -1)//n'existe pas création possible
    {
        {
            boost::mutex::scoped_lock lock(*mutex.get());
            File->SetValue(pseudo.c_str(), "password", pwd.c_str());
            File->SetLongValue(pseudo.c_str(), "PointExperience", 0);
            File->SetLongValue(pseudo.c_str(), "Vie", 500);
            File->SetLongValue(pseudo.c_str(), "VieMax", 500);
            File->SetLongValue(pseudo.c_str(), "Radiation", 400);
            File->SetLongValue(pseudo.c_str(), "RadiationMax", 400);
            File->SetLongValue(pseudo.c_str(), "Niveau", 1);
            File->SetLongValue(pseudo.c_str(), "Vitesse", 5);
            File->SetLongValue(pseudo.c_str(), "CapaCombat", 50);
            File->SetLongValue(pseudo.c_str(), "CapaTir", 50);
            File->SetLongValue(pseudo.c_str(), "Force", 23);
            File->SetLongValue(pseudo.c_str(), "Endurance", 23);
            File->SetLongValue(pseudo.c_str(), "Agilite", 23);
            File->SetLongValue(pseudo.c_str(), "Initiative", 23);
            File->SetLongValue(pseudo.c_str(), "Volonte", 23);
            File->SetLongValue(pseudo.c_str(), "Inteligence", 23);
            File->SetBoolValue(pseudo.c_str(), "isconnect", false);
            File->SaveFile("sauvegarde.dadu");
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Sauvegarde::verifierConnexion(string pseudo, string pwd)
{
    bool isconnect = false;
    const char* mdp;
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        isconnect = File->GetBoolValue(pseudo.c_str(), "isconnect", false);
        mdp = File->GetValue(pseudo.c_str(), "password");
    }
    if (mdp != NULL)
    {
        string mdpstring(mdp);
        if (!isconnect && pwd == mdpstring)
        {
            {
                boost::mutex::scoped_lock lock(*mutex.get());
                File->SetBoolValue(pseudo.c_str(), "isconnect", true);
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Sauvegarde::ajouterErreur(string pseudo)
{
    int existe;
    {
        boost::mutex::scoped_lock lock(*mutex.get());
        existe = File->GetSectionSize(pseudo.c_str());
        if (existe == -1)//n'existe pas création possible
        {
            File->SetLongValue(pseudo.c_str(), "Erreur", File->GetLongValue(pseudo.c_str(), "Erreur", 0) + 1);
        }

    }

}

