#ifndef DEF_ARMEDISTANCE
#define DEF_ARMEDISTANCE
#include <iostream>
#include "AbstractArme.h"
#include "Caracteristique.h"
using namespace std;
class ArmeDistance: public AbstractArme
{
public:
	typedef enum
	{
		FLECHE, CARREAU, BALLE
	} e_TypeMunition;

	ArmeDistance();
	ArmeDistance(std::string nom, Caracteristique carac, float degats, std::string typemuni, float rechg = 1, float portee = 15); //deprecated
	ArmeDistance(string infoObjet);
	std::string getTypeMunition(); //deprecated

	std::string toSave();

private:

	e_TypeMunition m_typemunition; //crée class munition?


};

#endif

