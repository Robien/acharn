/*
 * Symbole.h
 *
 *  Created on: 12 juin 2010
 *      Author: C. Louison
 */

/*! \file Symbole.h
 \brief La spécification de la classe Symbole
 \author C. Louison
 \date 19.05.2010
 */

#ifndef SYMBOLE_H_
#define SYMBOLE_H_

#include <iostream>
#include <vector>
using namespace std;

/*! \class Symbole
 \brief La classe représentant un symbole.

 Cette classe permet de représenter sous la forme d'un objet un symbole
 Les méthodes suivantes sont associées à un objet de type symboles :
 <li>Symbole
 <li>getChaine
 <li>operator !=
 <li>operator ==
 <li>operator <<
 <li>isMotCle
 */

class Symbole
{

public:
	/*! \var enum categorieSymbole
	 \brief differente categorie d'un symbole
	 valeur prise: MOTCLE, VARIABLE, ENTIER, INDEFINI, FINDEFICHIER, CHAINE, BOOLEAN, REEL
	 */
	enum categorieSymbole
	{
		MOTCLE, CARACTERISTIQUE, ATTRIBUT, SOUSATTAQUE, INDEFINI, FINDATTAQUE, CHAINE, VALEUR
	};

	/*! \fn Symbole(string s=string(""))
	 \brief Constructeur de la classe Symbole.

	 construit le symbole à partir de la chaine (string) s lue par le lecteur de symbole dans un fichier
	 \param s - chaine du symbole
	 */
	Symbole(string s = string(""));

	/*! \fn bool operator == (string ch)
	 \brief pour tester l'égalité entre le symbole et une chaîne
	 */
	bool operator ==(string ch);

	/*! \fn inline bool operator != (string ch)
	 \brief pour tester la différence...
	 */
	inline bool operator !=(string ch)
	{
		return !(*this == ch);
	}

	/*! \fn inline int getChaine()
	 \brief Retourne le symbole en string.
	 \return le symbole en string
	 */
	inline string getChaine()
	{
		return this->chaine;
	}

	/*! \fn friend ostream & operator <<(ostream & cout, Symbole symb)
	 \brief affiche le symbole sur cout
	 fonction amie pour pouvoir afficher un symbole sur cout
	 */
	//friend ostream & operator <<(ostream & cout, Symbole symb);     // fonction amie pour pouvoir afficher un symbole sur cout


private:
	string chaine; // chaine du symbole
	categorieSymbole categorie; // categorie du symbole (voir type énuméré ci-dessus)
	static bool isMotCle(string s); // méthode de classe : renvoie vrai si s est un mot clé du langage

};

#endif /* SYMBOLE_H_ */
