#include "hasard.h"
#include <boost/random.hpp>
#include <ctime>

int Random::generer(int min, int max)
{

//    boost::mt19937 rng;
 //   boost::uniform_int<> six(min, max);
 //   rng.seed(std::clock);
  //  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(rng, six);
  //  return die();



  std::time_t now = std::time(0);
  boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};
	int res = gen()%(max-min) + min;
	return res;

}
int Random::genererParJoueur(int min, int max, int numero, int initialisateur) // initialisateur du joueur et numero du nombre aléatoire demandé
{
    if (numero == 0)
    {
        numero = ++_numero;
    }
    if (initialisateur == 0)
    {
        initialisateur = _init;
    }
    boost::mt19937 rng;
    int maxNombre = 300000000;
    boost::uniform_int<> six(0, maxNombre);
    rng.seed(initialisateur);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(rng, six);
    for (int i = 0; i < numero - 1; i++) //provisoire ....
    {
        die();
    }
    return ((die() % (max - min)) + min);

}
Random::Random(int init)
{
    _init = init;
    _numero = 1;
}

Random::~Random()
{

}

int hasard(int min, int max) // pour la compatibilité ... ne plus utiliser
{
    std::cout << "C'est mal" << std::endl;
    return Random().generer(min, max);
}

std::vector<int>* Random::sequenceAleatoire(int taille)
{
    std::vector<int> init;
    std::vector<int>* result = new std::vector<int>;
    for (int i = 0; i < taille; ++i)
    {
        init.push_back(i);
    }
    for (int i = 0; i < taille; ++i)
    {
        int pos = generer(0, init.size() - 1);
        result->push_back(init[pos]);
        init.erase(init.begin() + pos);
    }
    return result;
}
