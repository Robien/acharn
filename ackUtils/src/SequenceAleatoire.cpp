/*
 * SequenceAleatoire.cpp
 *
 *  Created on: 30 sept. 2010
 *      Author: romain
 */

#include "../include/SequenceAleatoire.h"
#include "../include/hasard.h"
#include <iostream>

SequenceAleatoire::SequenceAleatoire(int taille)
{
    regenerer(taille);
    /*

     Pour utiliser, faire :

     PointeurIntelligent<SequenceAleatoire> seq = new SequenceAleatoire(10);
     for (unsigned int i; i < seq->size(); ++i)
     {
         std::cout << i << " - " << seq->get(i) << std::endl;
         std::cout << i << " - " << (*seq)[i]<< std::endl;
     }

     pour regénérer la liste :
     seq->regenerer();

     attention : 2 regénérations dans la même seconde sort le même résultat !

     */
}

SequenceAleatoire::~SequenceAleatoire()
{
}

void SequenceAleatoire::regenerer(int taille)
{
    if (taille == 0 && size() != 0)
    {
        regenerer(size());
    }
    else
    {
        clear();
        Random rand;
        std::vector<int> init;
        for (int i = 0; i < taille; ++i)
        {
            init.push_back(i);
        }
        for (int i = 0; i < taille; ++i)
        {
            int pos = rand.generer(0, init.size() - 1);
            push_back(init[pos]);
            init.erase(init.begin() + pos);
        }
    }
}

