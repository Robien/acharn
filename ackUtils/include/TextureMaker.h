/*
 * textureMaker.h
 *
 *  Created on: 2 nov. 2010
 *      Author: romain
 */

#ifndef TEXTUREMAKER_H_
#define TEXTUREMAKER_H_

#include "Singleton.h"
#include <irrlicht.h>
#include <iostream>
#include <vector>

class TextureMaker : public Singleton<TextureMaker>
{
public:
    TextureMaker();
    virtual ~TextureMaker();
    irr::video::ITexture* createTextureByCopy(std::string pathImageFond, std::string pathImageDessus, std::string pathImageMask, irr::IrrlichtDevice* device);
    irr::video::ITexture* createTextureByCopy(std::vector<std::string>* pathImages, std::vector<std::string>* pathImagesMask, irr::IrrlichtDevice* device);

};

#endif /* TEXTUREMAKER_H_ */
