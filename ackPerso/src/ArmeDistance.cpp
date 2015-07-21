#include <iostream>
#include "ArmeDistance.h"

using namespace std;

ArmeDistance::ArmeDistance() :
	AbstractArme()
{
	m_typemunition = ArmeDistance::FLECHE;
}

ArmeDistance::ArmeDistance(string nom, Caracteristique carac, float degats, std::string typemuni, float rechg, float portee) :
	AbstractArme(nom, carac, AbstractArme::ARC, degats, rechg, portee)
{
	m_typemunition = ArmeDistance::FLECHE;
}
ArmeDistance::ArmeDistance(string infoObjet)
{
	vector<string> info = split(infoObjet.c_str(), ':');

	m_typemunition = (ArmeDistance::e_TypeMunition) converint(info[1].c_str());
	AbstractArme(info[2], info[3], info[4]);
}

std::string ArmeDistance::getTypeMunition()
{
	return "";
}

std::string ArmeDistance::toSave()
{

	string info = "1";
	info = ":" + converstr((int) m_typemunition);
	info = info + AbstractArme::toSave();
	return info;
}
