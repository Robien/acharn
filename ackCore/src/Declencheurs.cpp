/*
 * Declancheurs.cpp
 *
 *  Created on: 7 sept. 2010
 *      Author: romain
 */

#include "../include/Declencheurs.h"
#include "../include/TacheSetAnime.h"
#include "../../ackTache/include/TacheSetEtat.h"
#include "../include/DeclencheursManager.h"

Declencheurs::Declencheurs(irr::scene::ISceneNode* nodeDeclencheur, typeDeclancheur type) :
    _nodeDeclancheur(nodeDeclencheur), _type(type), _isActionneurEtat(false)
{
    lastState = false;
}

Declencheurs::Declencheurs(irr::scene::ISceneNode* nodeDeclancheur, std::string typeDeclenche) :
    _nodeDeclancheur(nodeDeclancheur), _isActionneurEtat(false)
{

    if (typeDeclenche == "ACTIONNEUR")
    {
        _type = Declencheurs::ACTIONNEUR;
    }
    else if (typeDeclenche == "SURFACE_GLISSANTE")
    {
        _type = Declencheurs::SURFACE_GLISSANTE;
    }
    else if (typeDeclenche == "SURFACE_COLLANTE")
    {
        _type = Declencheurs::SURFACE_COLLANTE;
    }
    else if (typeDeclenche == "SURFACE_FLUIDE")
    {
        _type = Declencheurs::SURFACE_FLUIDE;
    }
    else if (typeDeclenche == "SURFACE_MOLLE")
    {
        _type = Declencheurs::SURFACE_MOLLE;
    }
    else if (typeDeclenche == "ZONE")
    {
        _type = Declencheurs::ZONE;
    }
    else if (typeDeclenche == "LIQUIDE")
    {
        _type = Declencheurs::LIQUIDE;
    }

    else if (typeDeclenche == "PIEGE")
    {
        _type = Declencheurs::PIEGE;
    }
    else if (typeDeclenche == "PNJ_QUETE")
    {
        _type = Declencheurs::PNJ_QUETE;
    }
    else if (typeDeclenche == "PNJ_VENDEUR")
    {
        _type = Declencheurs::PNJ_VENDEUR;
    }
    else
    {
        _type = Declencheurs::INCONNU;
        std::cout << "Attention type inconnu" << std::endl;
    }
    lastState = false;
}

Declencheurs::Declencheurs(irr::scene::ISceneNode* nodeDeclancheur, std::string name, int etat) :
    _nodeDeclancheur(nodeDeclancheur),  _isActionneurEtat(true), name(name), etat(etat)
{

    _type = Declencheurs::ACTIONNEUR;
    lastState = false;
    std::cout << "constructeur 3 déclencheur" << std::endl;
}
Declencheurs::~Declencheurs()
{
}

bool Declencheurs::test(bool& nothing)
{
    bool resultat = nothing = false;
    if (_type == Declencheurs::ACTIONNEUR)
    {
        resultat = DeclencheursManager::get()->getBoutonAction() && isFace();
    }
    else if (_type == Declencheurs::LIQUIDE)
    {
        resultat = isCenter();
    }
    else if (_type == Declencheurs::SURFACE_MOLLE || _type == Declencheurs::SURFACE_GLISSANTE || _type == Declencheurs::SURFACE_COLLANTE || _type == Declencheurs::SURFACE_FLUIDE)
    {
        resultat = isUpon();
    }
    else if (_type == Declencheurs::ZONE)
    {
        resultat = isIn();
    }
    else if (_type == Declencheurs::PIEGE)
    {
        resultat = isUpon();
    }
    else if (_type == Declencheurs::PNJ_QUETE)
    {
        resultat = isFace();
    }
    else if (_type == Declencheurs::PNJ_VENDEUR)
    {
        resultat = isFace();
    }
    else
    {
        std::cout << "erreur:test: type de declencheur inexistant" << std::endl;
        return false;
    }

    if (resultat == lastState)//si pas dans cube et pas dans cube avant ou si dans cube et deja dedans avant
    //equivaux à: if ((!resultat && !lastState) || (resultat && lastState) )
    {
        nothing = true;//on fait rien
        return resultat;
    }
    else if (!resultat && lastState)//si pas dans cube mais avant oui
    {
        nothing = false;
        lastState = false;
        return resultat;
    }
    else //if(resultat && !lastState)//entre dans un cube
    {
        nothing = false;
        lastState = true;
        return resultat;
    }

}
void Declencheurs::execute()
{
    if (_isActionneurEtat)
    {
        _aFaireEtat->execute();
        std::cout << "exécute état déclencheur" << std::endl;
    }
    _aFaire->execute();
}

void Declencheurs::stop()
{
    //_aFaire->stop();
}

void Declencheurs::setJoueur(Perso* joueur)
{
    _joueur = joueur;
    if (_type == Declencheurs::ACTIONNEUR)
    {
        _aFaire = new TacheSetAnime(0, Perso::COUPDEPOING); // id 0 => perso qui joue
        if (_isActionneurEtat)
        {
            _aFaireEtat = new TacheSetEtat(name, etat);
        }
    }
    else if (_type == Declencheurs::PIEGE)
    {
        _aFaire = new TacheSetAttaque(0, "<#nom=\"Piege de base\"#degat=20#pas=4#tps=3>");
    }
    else if (_type == Declencheurs::LIQUIDE)
    {
        _aFaire = new TacheSetAnime(0, Perso::NAGE);
    }
    else if (_type == Declencheurs::ZONE)
    {
        _aFaire = new TacheSetAnime(0, Perso::POSEROBERT);
    }
    else if (_type == Declencheurs::PNJ_QUETE)
    {
        irr::core::vector3df middle = _nodeDeclancheur->getTransformedBoundingBox().getCenter();
        float hauteurpar2 = (_nodeDeclancheur->getTransformedBoundingBox().MaxEdge.Y - _nodeDeclancheur->getTransformedBoundingBox().MinEdge.Y) / 2;
        float valx = _nodeDeclancheur->getTransformedBoundingBox().MinEdge.Z;
        _aFaire = new TacheTalkPnj(middle.X, middle.Y - hauteurpar2, valx, 1, "");
    }
    else if (_type == Declencheurs::PNJ_VENDEUR)
    {
        irr::core::vector3df middle = _nodeDeclancheur->getTransformedBoundingBox().getCenter();
        float hauteurpar2 = (_nodeDeclancheur->getTransformedBoundingBox().MaxEdge.Y - _nodeDeclancheur->getTransformedBoundingBox().MinEdge.Y) / 2;
        float valx = _nodeDeclancheur->getTransformedBoundingBox().MinEdge.Z;
        _aFaire = new TacheTalkPnj(middle.X, middle.Y - hauteurpar2, valx, 2, "");
    }
    else if (_type == Declencheurs::SURFACE_MOLLE || _type == Declencheurs::SURFACE_GLISSANTE || _type == Declencheurs::SURFACE_COLLANTE || _type == Declencheurs::SURFACE_FLUIDE)
    {
        _aFaire = new TacheSetAnime(0, Perso::MARCHER);
    }
}

Tache* Declencheurs::getTache()
{
    return _aFaire;
}

bool Declencheurs::isIn()
{
    bool inside = false;
    inside = _nodeDeclancheur->getTransformedBoundingBox().intersectsWithBox(_joueur->getNode()->getTransformedBoundingBox());
    return inside;
}

bool Declencheurs::isFace()
{//verifier que declanche quand le devant du player entre dans la zone

    bool inside = false;
    irr::core::vector3df middle = _joueur->getNode()->getTransformedBoundingBox().getCenter();
    irr::core::vector3df diag = middle - _joueur->getNode()->getTransformedBoundingBox().MaxEdge;
    irr::core::line3df diago(middle.X + diag.X, middle.Y - diag.Y, middle.Z + diag.Z, middle.X - diag.X, middle.Y + diag.Y, middle.Z + diag.Z);
    //core::vector3df point =diago.getMiddle();
    //	inside = _nodeDeclancheur->getTransformedBoundingBox().isPointInside(point);
    inside = _nodeDeclancheur->getTransformedBoundingBox().intersectsWithLine(diago);
    return inside;
}

bool Declencheurs::isCenter()
{
    bool inside = false;
    inside = _nodeDeclancheur->getTransformedBoundingBox().isPointTotalInside(_joueur->getNode()->getPosition());
    return inside;
}

bool Declencheurs::isUpon()
{//verifier que declanche quand le dessous du player entre dans la zone

    bool inside = false;

    irr::core::vector3df middle = _joueur->getNode()->getTransformedBoundingBox().getCenter();
    irr::core::vector3df diag = middle - _joueur->getNode()->getTransformedBoundingBox().MaxEdge;
    irr::core::line3df diago(middle.X + diag.X, middle.Y + diag.Y, middle.Z + diag.Z, middle.X - diag.X, middle.Y + diag.Y, middle.Z - diag.Z);
    //core::vector3df point =diago.getMiddle();
    //inside = _nodeDeclancheur->getTransformedBoundingBox().isPointInside(point);
    inside = _nodeDeclancheur->getTransformedBoundingBox().intersectsWithLine(diago);
    return inside;
}

Tache* Declencheurs::getTacheEtat()
{
    return _aFaireEtat;
}
bool Declencheurs::isActionneurEtat()
{
    return _isActionneurEtat;
}
