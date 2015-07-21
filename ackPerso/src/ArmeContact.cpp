#include <iostream>

#include "ArmeContact.h"

using namespace std;

ArmeContact::ArmeContact() :
	AbstractArme()
{
}

ArmeContact::ArmeContact(string nom, Caracteristique carac, float degats, float rechg, float portee) :
	AbstractArme(nom, carac, AbstractArme::EPEE, degats, rechg, portee)
{
}

ArmeContact::ArmeContact(string infoObjet)
{
	vector<string> info = split(infoObjet.c_str(), ':');
	AbstractArme(info[2], info[3], info[4]);
}

std::string ArmeContact::toSave()
{

	string info = "0";
	info = ":";
	info = info + AbstractArme::toSave();
	return info;
}
