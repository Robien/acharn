#include <iostream>
#include "base.h"

using namespace std;

bool vivant(std::list<AbstractPerso*>::iterator ideb, std::list<AbstractPerso*>::iterator iend)
{
	bool life = true;
	for (std::list<AbstractPerso*>::iterator i = ideb; i != iend; i++)
	{
		if (!(*i)->estVivant())
			life = false;
	}
	return life; //retourne false si une personne de la liste est mort
}

void vainqueur(PersoJoueur &pj, PersoNonJoueur &pnj)
{
	if (pj.estVivant() && !pnj.estVivant())
	{
		cout << "      " << pj.getNom() << " sort victorieux du combat contre " << pnj.getNom() << endl;
		int xpgagne = pnj.donnexp(pj);
		cout << "      " << pj.getNom() << " gagne: " << xpgagne << "xp" << endl;
		//gain xp
		if (pj.gainxp(xpgagne))
			cout << "      " << "   !! " << pj.getNom() << " change de niveau" << " !!" << endl;
	}
	else if (pnj.estVivant() && !pj.estVivant())
	{
		cout << pnj.getNom() << " sort victorieux du combat contre " << pj.getNom() << endl;
		//réduit usure du perdant
	}
}

void vainqueur(PersoJoueur &pj1, PersoJoueur &pj2)
{
	if (pj1.estVivant() && !pj2.estVivant())
	{
		cout << "      " << pj1.getNom() << " sort victorieux du combat contre " << pj2.getNom() << endl;
		int xpgagne = pj2.donnexp(pj1);
		cout << "      " << pj1.getNom() << " gagne: " << xpgagne << "xp" << endl;
		//gain xp
		if (pj1.gainxp(xpgagne))
			cout << "   !! " << pj1.getNom() << " change de niveau" << " !!" << endl;
	}
	else if (pj2.estVivant() && !pj1.estVivant())
	{
		cout << "      " << pj2.getNom() << " sort victorieux du combat contre " << pj1.getNom() << endl;
		int xpgagne = pj1.donnexp(pj2);
		cout << "      " << pj2.getNom() << " gagne: " << xpgagne << "xp" << endl;
		//gain xp
		if (pj2.gainxp(xpgagne))
			cout << "   !! " << pj2.getNom() << " change de niveau" << " !!" << endl;
	}
}

void vainqueur(PersoNonJoueur &pnj1, PersoNonJoueur &pnj2)
{
	if (pnj1.estVivant() && !pnj2.estVivant())
	{
		cout << "      " << pnj1.getNom() << " sort victorieux du combat contre " << pnj2.getNom() << endl;
	}
	else if (pnj2.estVivant() && !pnj1.estVivant())
	{
		cout << "      " << pnj2.getNom() << " sort victorieux du combat contre " << pnj1.getNom() << endl;
	}
}

/* 
 float converfl(std::string txt) //convert un string en float
 {float res = 9999;
 istringstream istr;
 istr.str(txt);
 istr >> res;

 return res;
 }

 int converint(std::string txt)//convert un string en int
 { int res = 9999;
 istringstream istr;
 istr.str(txt);
 istr >> res;

 return res;
 }
 std::string converstr(int nb)//convert un string en int
 {	std::ostringstream oss;
 oss << nb;
 return oss.str();
 }

 std::string converstr(float nb)
 {
 std::ostringstream oss;
 oss << nb;
 return oss.str();
 }
 */
