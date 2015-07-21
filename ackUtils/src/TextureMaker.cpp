/*
 * textureMaker.cpp
 *
 *  Created on: 2 nov. 2010
 *      Author: romain
 */

#include "../include/TextureMaker.h"

TextureMaker::TextureMaker()
{
}

TextureMaker::~TextureMaker()
{
}

irr::video::ITexture* TextureMaker::createTextureByCopy(std::string pathImageFond, std::string pathImageDessus, std::string pathImageMask, irr::IrrlichtDevice* device)
{
    irr::video::IImage* imageFond = device->getSceneManager()->getVideoDriver()->createImageFromFile(pathImageFond.c_str());
    irr::video::IImage* imageDessus = device->getSceneManager()->getVideoDriver()->createImageFromFile(pathImageDessus.c_str());
    irr::video::IImage* imageMask = device->getSceneManager()->getVideoDriver()->createImageFromFile(pathImageMask.c_str());

    if (imageFond == NULL || imageDessus == NULL || imageMask == NULL)
    {
        std::cerr << "Une des textures n'existe pas" << std::endl;
        return NULL;
    }
    else if (imageDessus->getDimension() != imageFond->getDimension() || imageDessus->getDimension() != imageMask->getDimension() || imageMask->getDimension() != imageFond->getDimension())
    {
        std::cerr << "problème de dimensions ou existe pas" << std::endl;
        return NULL;
    }
    else
    {
        irr::video::IImage* imagetmp = device->getSceneManager()->getVideoDriver()->createImage(imageFond->getColorFormat(), imageFond->getDimension());

        irr::core::dimension2d<unsigned int> dimension = imagetmp->getDimension();

        for (unsigned int i = 0; i < dimension.Width; ++i)
        {
            for (unsigned int j = 0; j < dimension.Height; ++j)
            {
                if (imageMask->getPixel(i, j).color == 0)
                {
                    imagetmp->setPixel(i, j, imageFond->getPixel(i, j).color);
                }
                else
                {
                    imagetmp->setPixel(i, j, imageDessus->getPixel(i, j).color);
                }
            }
        }

        return device->getSceneManager()->getVideoDriver()->addTexture(pathImageFond.c_str(), imagetmp);
    }

}

irr::video::ITexture* TextureMaker::createTextureByCopy(std::vector<std::string>* pathImages, std::vector<std::string>* pathImagesMask, irr::IrrlichtDevice* device)
{
    bool noerror = true;
    std::vector<irr::video::IImage*> imagesMask;
    for (unsigned int i = 0; i < pathImagesMask->size() && noerror; ++i)
    {
        std::cout << "i = " << i << std::endl;
        irr::video::IImage* image = device->getSceneManager()->getVideoDriver()->createImageFromFile((*pathImagesMask)[i].c_str());
        noerror = image != NULL && noerror;
        imagesMask.push_back(image);
    }

    std::vector<irr::video::IImage*> images;
    for (unsigned int i = 0; i < pathImages->size() && noerror; ++i)
    {
        std::cout << "i = " << i << std::endl;
        irr::video::IImage* image = device->getSceneManager()->getVideoDriver()->createImageFromFile((*pathImages)[i].c_str());
        noerror = image != NULL && noerror;
        images.push_back(image);
    }

    if (noerror)
    {
        irr::video::IImage* imagetmp = device->getSceneManager()->getVideoDriver()->createImage(images[0]->getColorFormat(), images[0]->getDimension());
        irr::core::dimension2d<unsigned int> dimension = imagetmp->getDimension();

        for (unsigned int i = 0; i < dimension.Width; ++i)
        {
            for (unsigned int j = 0; j < dimension.Height; ++j)
            {
                int z;
                for (z = (int) imagesMask.size() - 1; z >= 0 && imagesMask[(unsigned int) z]->getPixel(i, j).color == 0; --z)
                {
                }
                imagetmp->setPixel(i, j, images[z + 1]->getPixel(i, j).color);
            }

        }
        return device->getSceneManager()->getVideoDriver()->addTexture((*pathImages)[0].c_str(), imagetmp);
    }
    else
    {
        std::cerr << "Une des textures n'existe pas" << std::endl;
        return NULL;
    }
}
