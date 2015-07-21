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
#include "boost/lexical_cast.hpp"

using namespace std;

float converfl(string txt) //convert un string en float
{
    return boost::lexical_cast<float>(txt);
}

int converint(string txt)//convert un string en int
{
    return boost::lexical_cast<int>(txt);
}

std::string converstr(int nb)//convert en string un int
{
    return boost::lexical_cast<std::string>(nb);
}

std::string converstr(float nb)//convert en string un float
{
    return boost::lexical_cast<std::string>(nb);
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
