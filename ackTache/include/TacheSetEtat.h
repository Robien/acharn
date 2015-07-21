/*
 * TacheSetEtat.h
 *
 *  Created on: 8 nov. 2010
 *      Author: romain
 */

#ifndef TACHESETETAT_H_
#define TACHESETETAT_H_

#include "Tache.h"
#include "iostream"

class TacheSetEtat : public Tache
{
public:
    TacheSetEtat(std::string name, int etat);
    virtual ~TacheSetEtat();
    void execute();

private:
    std::string _name;
    int _etat;
};

#endif /* TACHESETETAT_H_ */
