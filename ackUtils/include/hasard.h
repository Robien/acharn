#ifndef HASARD_H_INCLUDED
#define HASARD_H_INCLUDED

#include "../include/Referenced.h"
#include <vector>

class Random: public Referenced
{
public:
    Random(int init = 0);
    virtual ~Random();
    int generer(int min, int max);
    int genererParJoueur(int min, int max, int numero = 0, int initialisateur = 0); // initialisateur du joueur et numero du nombre aléatoire demandé

    //Utilisez l'objet SequenceAleatoire, c'est plus mieux fort bien
    std::vector<int>* sequenceAleatoire(int taille); // retourne un vecteur de taille nombres organisé dans un ordre aléatoire.

    inline int getNumero() // numero du PROCHAIN nombre demandé
    {
        return _numero;
    }
private:
    int _init;
    int _numero;
};

int hasard(int min, int max); // pour la compatibilité ... ne plus utiliser


#endif // HASARD_H_INCLUDED
