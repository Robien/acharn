/*
 * SequenceAleatoire.h
 *
 *  Created on: 30 sept. 2010
 *      Author: romain
 */

#ifndef SEQUENCEALEATOIRE_H_
#define SEQUENCEALEATOIRE_H_

#include "Referenced.h"
#include <vector>

class SequenceAleatoire : public std::vector<int>, public Referenced
{
public:
    SequenceAleatoire(int taille);
    virtual ~SequenceAleatoire();

    inline int get(int pos)
    {
        return (*this)[pos];
    }

    void regenerer(int taille = 0); // taille de 0 => réutilise l'ancienne taille


};

#endif /* SEQUENCEALEATOIRE_H_ */
