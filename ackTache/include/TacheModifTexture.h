/*
 * TacheModifTexture.h
 *
 *  Created on: 9 nov. 2010
 *      Author: romain
 */

#ifndef TACHEMODIFTEXTURE_H_
#define TACHEMODIFTEXTURE_H_

#include "Tache.h"
#include <vector>
#include <iostream>

class TacheModifTexture : public Tache
{
public:
    TacheModifTexture(int id, std::vector<std::string>* textures);
    virtual ~TacheModifTexture();
    void execute();

private:
    std::vector<std::string>* _textures;
};

#endif /* TACHEMODIFTEXTURE_H_ */
