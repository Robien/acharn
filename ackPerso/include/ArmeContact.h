#ifndef DEF_ARMECONTACT
#define DEF_ARMECONTACT
#include <iostream>
#include "AbstractArme.h"
#include "Caracteristique.h"
using namespace std;
class ArmeContact: public AbstractArme
{
public:

	ArmeContact();
	ArmeContact(std::string nom, Caracteristique carac, float degats, float rechg = 1, float portee = 1); //deprecated
	ArmeContact(string infoObjet);

	std::string toSave();
};

#endif

