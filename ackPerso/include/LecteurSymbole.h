/*
 * LecteurSymbole.h
 *
 *  Created on: 12 juin 2010
 *      Author: C. Louison
 */

/*! \file LecteurSymbole.h
 \brief La spécification de la classe LecteurSymbole
 \author C. Louison
 */

#ifndef LECTEURSYMBOLE_H_
#define LECTEURSYMBOLE_H_

#include <string>
using namespace std;

#include "LecteurCaractere.h"
#include "Symbole.h"

/*! \class LecteurSymbole
 \brief La classe représentant un lecteur de symbole.

 Cette classe permet de parcourir ce fichier symbole par symbole en vue de réaliser son analyse syntaxique
 Les méthodes suivantes sont associées à un objet de type lecteur de symboles :
 <li>LecteurSymbole
 <li>suivant
 <li>getSymCour
 <li>ligneSuivante
 <li>sauterSeparateurs
 <li>sauterCommentaire
 <li>sauterCommentaireMulti
 <li>motSuivant
 */

class LecteurSymbole
{
public:

	/*! \fn LecteurSymbole(string nomFich)
	 \brief Constructeur de la classe LecteurSymbole.

	 construit le lecteur de symbole à partir de la chaine (string) attaque
	 etat initial: symCour = premier symbole de la chaine
	 \param at - attaque
	 */
	LecteurSymbole(string at);

	/*! \fn void suivant()
	 \brief  passe au symbole suivant du fichier.
	 */
	void suivant();

	/*! \fn inline Symbole getSymCour()
	 \brief Retourne le symbole courant
	 \return le symbole courant
	 */
	inline Symbole getSymCour()
	{
		return symCour;
	}

private:
	LecteurCaractere lc; // le lecteur de caracteres
	Symbole symCour; // le symbole courant du lecteur de symboles
	void sauterSeparateurs(); // saute dans lc une suite de separateurs consecutifs
	string motSuivant(); // lit dans lc la chaine du prochain symbole et la renvoie en resultat
};

#endif /* LECTEURSYMBOLE_H_ */
