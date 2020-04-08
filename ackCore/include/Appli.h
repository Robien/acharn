#ifndef DEF_APPLI
#define DEF_APPLI
/*
 * =====================================================================================
 *
 *       Filename:  Appli.h
 *
 *    Description:  permet d'envoyer des messages a la couche graphique 
 *
 *        Version:  1.0
 *        Created:  05/04/2010 18:25:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <memory>
#include <thread>

#include "PersoManager.h"
#include "Protocole.h"
#include "../include/Referenced.h"

//
//NB :
// pour creer facilement un vector3df on peut utiliser son constructeur dans l'appel des fonctions :
//
// nouveauJoueur(23, irr::core::vector3df(1,2,3));
//
namespace ackCore
{

class Appli: public Referenced
{
public:
    Appli();

public:
    // SafeThread
    void nouveauJoueur(int id, irr::core::vector3df position, int init, std::string infoJoueur);// enregiste un nouveau joueur avec un id unique, et l'affiche a la position position.
    void deplacerJoueur(int id, irr::core::vector3df position, irr::core::vector3df rotation);//deplace le joueur id a la position position
    void attaque(int id, Protocole* protocole);
    void setAnim(int id, Perso::typeAnim typeAnim);
    void deletePerso(int id);

public:
    // vers le réseau
    void envoyerDeplacement(irr::core::vector3df position, irr::core::vector3df rot, Protocole* protocole);
    void envoyerDeplacement(irr::core::vector3df position, irr::core::vector3df rot, Protocole* protocole, Perso::typeAnim typeAnim);
    void envoyerMessage(std::string mess, Protocole* protocole, int numero = 0);
    void attaqueFinale(int id, Protocole* protocole);

private:

    int _nbConnecte;

    static void majAll(Appli* app);
    std::shared_ptr<std::thread> threadMaj;

};

} // namespace ackCore

#endif
