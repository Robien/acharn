/*
 * =====================================================================================
 *
 *       Filename:  const.cpp
 *
 *    Description:  implémentation des fonctions communes
 *
 *        Version:  1.0
 *        Created:  12/04/2010 22:23:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "const.h"
#include <string>

using namespace std;

float converfl(string txt) //convert un string en float
{
    return std::stoi(txt);
}

int converint(string txt)//convert un string en int
{
    return std::stoi(txt);
}

std::string converstr(int nb)//convert en string un int
{
    return std::to_string(nb);
}

std::string converstr(float nb)//convert en string un float
{
    return std::to_string(nb);
}

vector<std::string> split(const char* data, char separateur)
{
    vector<std::string> resultat;
    string morceau;
    int i = 0;

    while (data[i] != '\0')
    {
        if (data[i] == separateur && i > 0 && data[i - 1] != '\\')
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

    return resultat;
}
