#ifndef DEF_PERSO
#define DEF_PERSO
/*
 * =====================================================================================
 *
 *       Filename:  Perso.h
 *
 *    Description: classe gérant l'affichage des personnages 
 *
 *        Version:  1.0
 *        Created:  05/04/2010 18:33:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <irrlicht.h>
#include "const.h"
#include "../include/Referenced.h"

class EventReceiver;

class Perso: public Referenced
{
public:
    typedef enum
    {
        MARCHER, COURRIR, STAND, TOURNE, POSEROBERT, POSECOMBATA2M, FRAPERA2M, POSECOMBATMN, INCANT, INCANT2STAND, JUMP, NAGE, COUPDEPOING, DYING, DEAD, DEMO
    } typeAnim;

    typedef enum
    {
        MAINNUE, ARME2M, MAGIE
    } typeAttaque;
    typedef enum
    {
        DEPLACEMENT, POSECOMBAT, IMMOBILE, COMBAT
    } typeEtat; // pas utilisé encore ....
    typedef enum
    {
        DEPLACEMENT_LENT, DEPLACEMENT_RAPIDE, NAGER, MODE_COMBAT
    } typeAction; // pas utilisé encore ....


    Perso(irr::IrrlichtDevice* n_device);
    virtual ~Perso();

    virtual void afficher(float x, float y, float z, std::string pseudo = "", std::string mesh = "data/mesh/character.b3d", std::string normal = "data/mesh/normal_character.jpg", string texture =
            "data/mesh/texture_character.jpg"); //initialise en position x,y,z, le perso. à faire avant tout !
    void setScale(float x, float y, float z);//definie l'echelle d'affichage du perso, en x,y,z, (1,1,1) est la taille par defaut

    void teleport(float x, float y, float z); // le perso se téléporte à x,y,z
    void tourner(float x, float y, float z); // le perso se tourne instantanément en x,y,z

    void tourner_rel(float x, float y, float z); // le perso se tourne instantanément et relativement à la position actuelle de dx, dy, dz
    void teleport_rel(float x, float y, float z); // le perso se téléporte relativement x,y,z

    void tourner_vers(float x, float y, float z); // le perso va se déplacer en x,y,z, déplacement calculé a chaque calcul_position
    void aller_vers(float x, float y, float z); // idem tourner_vers, mais en translation
    void calcul_position(float delta); // à lancer pour mettre a jours la position après avoir fait un X_vers, dela => temps depuis la dernière maj


    void avancer(float dist, bool enAvant = true);
    void avancerCote(float dist, bool droit = true);

    void deplacement(EventReceiver & receiver, float frameDeltaTime);

    void setAnim(Perso::typeAnim type, bool EnAvant = true);
    const Perso::typeAnim getAnim();
    void setAnimHolded(Perso::typeAnim type, bool EnAvant = true);
    void unLockAnim();
    bool isAnimChanged();

    bool checkIfActionPossible(Perso::typeAnim type);
    void setAnimIfIsPossible(Perso::typeAnim type, bool sens = true);

    void maj(float delta);
    void pousse(irr::core::line3df direction);
    void setDead();
    void setAlive();
    virtual void mortALInstant();
    void setTexture(vector<string>* text);
    void setTexture(string text);
    void setTexture();
    string saveTexture();
    void changeTexture();
    irr::scene::IAnimatedMeshSceneNode* getNode();//geter pour le node (c'est mal)


private:
    //tout ceci est privé !

    irr::IrrlichtDevice* _device;
    irr::scene::IAnimatedMeshSceneNode* _node;
    irr::scene::IAnimatedMeshSceneNode* _nodeEpee;
    bool _enMain;
    irr::video::SMaterial _material;

    //gestion de la rotation du personnage
    float rotx, roty, rotz;
    float frotx, froty, frotz;
    float vrotx, vroty, vrotz;

protected:
    //gestion des déplacement du personnage
    float px, py, pz;
    float fpx, fpy, fpz;
    float vpx, vpy, vpz;

private:
    void addEpee();
    void setFrameAnim(int deb, int fin);
    void setFrameAnim(irr::core::vector2di range);
    void setFramePerSecond(float vitesse);
    const Perso::typeEtat getEtatByAnim(Perso::typeAnim type);
    const irr::core::vector2di getRangeAnimByType(Perso::typeAnim type);
    int getFPS(Perso::typeAnim type);

    //gestion des anims
    float tempsanim;
    int statut;
    bool deplace;
    bool sensAvant;
    bool tourne;

    Perso::typeAnim _ancienAnim;
    bool _isAnimChanged;
    Perso::typeEtat _etat;

    bool _animLocked;
    float _tempsAvantFinMort;

    vector<string>* textureperso;
    string texturecorp;

protected:

    irr::IrrlichtDevice* getDevice();
    float _tempsAvantFinAnim;
};

#endif

