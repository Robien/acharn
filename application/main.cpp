#include "Appli.h"
#include "Jeu.h"
#include "Client.h"
#include "PointeurIntelligent.h"

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#ifdef _MSC_VER // pour enlever une erreur de link sous visual
void boost::throw_exception(std::exception const & e)
{
}
#endif

/**
 * @mainpage Acharn MMORPG
 *
 * Acharn est un MMOPRG libre et gratuit<br>
 * <br>
 * @section intro_sec Description générale
 * Acharn est un MMO RPG (Massively multiplayer online role-playing game = jeu de rôle en ligne massivement multijoueur) développé dans le cadre du projet tuteuré de l'IUT2 de Grenoble.
 *<ul>
 * <li>Il est gratuit, libre et multiplateforme.</li>
 * <li>Il est actuellement en version de développement.</li>
 * </ul>
 *<br>
 */

int main(int argc, char *argv[])
{

    PointeurIntelligent<ackCore::Appli> app = new ackCore::Appli();
    PointeurIntelligent<EventReseau> eventReseau = new EventReseau(app);
    PointeurIntelligent<Protocole> protocole;

    if (argc >= 3)
    {
        protocole = new Protocole(std::string(argv[1]), std::string(argv[2]), eventReseau);
    }
    else
    {
        protocole = new Protocole(std::string("localhost"), std::string("10000"), eventReseau);
    }
    std::string pseudo = "dadu";
    std::string mdp = "dadu";
    if (argc >= 5)
    {
        pseudo = argv[3];
        mdp = argv[4];
    }
    if (argc == 6 && argv[5][0] == 'c')
    {
        protocole->creationCompte(pseudo, mdp);
        sleep(5);
    }
    else
    {

        PointeurIntelligent<ackCore::Jeu> jeu = new ackCore::Jeu(*app, protocole, (argc >= 3), pseudo, mdp);

        jeu->run();
    }

    return 0;
}

