/*
 * IrrAtributeExtractor.cpp
 *
 *  Created on: 7 sept. 2010
 *      Author: romain
 */

#include "../include/IrrAtributeExtractor.h"
#include "../include/DeclencheursManager.h"
#include "../../ackAudio/include/AudioManager.h"
#include "../../ackAudio/include/Audio.h"
#include "../../ackAudio/include/Buffer.h"
#include "../include/ObjetPorte.h"
#include "../include/Animation.h"
#include "../include/SuiteAnimations.h"
#include "../include/ObjetManager.h"

ackCore::IrrAtributeExtractor::IrrAtributeExtractor(Jeu* jeu) :
    irr::scene::ISceneUserDataSerializer(), _jeu(jeu)
{
}

ackCore::IrrAtributeExtractor::~IrrAtributeExtractor()
{

}

void ackCore::IrrAtributeExtractor::OnCreateNode(irr::scene::ISceneNode* node)
{
    _jeu->justOneFrameChargement();

}
void ackCore::IrrAtributeExtractor::OnReadUserData(irr::scene::ISceneNode* forSceneNode, irr::io::IAttributes* userData)
{
    if (userData->existsAttribute("collision"))
    {
        forSceneNode->setID(9999);
    }
    if (userData->existsAttribute("son"))
    {
        AudioManager::get()->play(userData->getAttributeAsString("declencheur").c_str(), userData->getDebugName(), forSceneNode->getPosition(),true);
    }

    if (userData->existsAttribute("water"))
    {
        forSceneNode->setID(9000);
    }

    if (userData->existsAttribute("declencheur"))
    {
        std::string typeDeclencheur(userData->getAttributeAsString("declencheur").c_str());

        if (typeDeclencheur == "LIQUIDE")
        {
            AudioManager::get()->play(Buffer::EAU, "EAU", forSceneNode->getTransformedBoundingBox().getCenter(), true, NULL);
        }
        if (typeDeclencheur == "ACTIONNEUR")
        {
            std::cout << "actionneur found" << std::endl;
            DeclencheursManager::get()->addDeclancheur(new Declencheurs(forSceneNode, userData->getAttributeName(0), userData->getAttributeAsInt(0)));
        }
        else
        {
            DeclencheursManager::get()->addDeclancheur(new Declencheurs(forSceneNode, typeDeclencheur));
        }
    }
    if (userData->existsAttribute("rez"))
    {
        forSceneNode->setID(9998);
    }
    if (userData->existsAttribute("spawn"))
    {
        forSceneNode->setID(9997);
    }
    if (false && userData->existsAttribute("modele"))
    {
        std::string modele = userData->getAttributeAsString("modele").c_str();
        std::string texture = userData->getAttributeAsString("texture").c_str();
        std::string normal = userData->getAttributeAsString("normal").c_str();
        modele = "data/mesh/" + modele;
        texture = "data/mesh/" + texture;
        normal = "data/mesh/" + normal;
        PointeurIntelligent<ObjetPorte> objet = new ObjetPorte(modele.c_str(), texture.c_str(), normal.c_str());
        PointeurIntelligent<SuiteAnimations> animAscenseur = new SuiteAnimations;
        animAscenseur->push_back(new Animation(1, 1, 50));
        ackCore::ObjetManager::get()->addObjet(objet, userData->getAttributeAsString("name").c_str());
        std::cout << "je m'appelle " << userData->getAttributeAsString("name").c_str() << std::endl;
        objet->setSuiteAnimation(animAscenseur);

        int i = 0;
        while (userData->existsAttribute(std::to_string(i).c_str()))
        {
            objet->addEtat(i, new EtatObjet(userData->getAttributeAsInt(std::to_string(i).c_str())));
            ++i;
        }
    }
}
irr::io::IAttributes* ackCore::IrrAtributeExtractor::createUserData(irr::scene::ISceneNode* forSceneNode)
{
    return NULL;
}
