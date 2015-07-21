#ifndef CALLBACK_H_
#define CALLBACK_H_

#include <vector>
#include "../include/MainPerso.h"

using namespace std;

class Callback
{
public:

	Callback(){}
	virtual ~Callback(){}

	virtual void recevoirMessage(vector<std::string> &message, int source){}
	virtual void retourCreation(bool reussi, string erreur = ""){}
	virtual void connexionReussie(int init, string info){}
	virtual void connexionRefusee(string msgerror){}
	virtual void connexionNewJoueur(int id, int init, string info){}
	virtual void connexionCompetence(vector<std::string> &l_comp){}
	virtual void connexionObjetSac(vector<std::string> &l_objsac){}
	virtual void connexionObjetEquipement(int id, vector<std::string> &l_equip){}
	virtual void connexionTexture(int id, vector<std::string>* l_texture){}
	virtual void deconnexionJoueur(int id){}
	virtual void verificationInfo(int id){}
	virtual void verificationObjetEquipement(int id){}
	virtual void isEtat(string nom,int etat){}
	virtual void setTexture(int id, vector<std::string>* l_texture){}

};

#endif /* PROTOCOLE_H_*/
