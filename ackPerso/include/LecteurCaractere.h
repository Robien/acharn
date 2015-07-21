/*
 * LecteurCaractere.h
 *
 *  Created on: 12 juin 2010
 *      Author: C. Louison
 */

/*! \file LecteurCaractere.h
 \brief La spécification de la classe LecteurCaractere
 \author C. Louison
 */

#ifndef LECTEURCARACTERE_H_
#define LECTEURCARACTERE_H_

#include <string>
using namespace std;

/*! \class LecteurCaractere
 \brief La classe représentant un lecteur de caractere.

 Cette classe permet de parcourir l'attaque caractere par caractere
 Les méthodes suivantes sont associées à un objet de type lecteur de caractere :
 <li>LecteurCaractere
 <li>suivant
 <li>getCarCour
 */

class LecteurCaractere
{

	////////////////////////////////////////////////////////////////////////////////
public:

	/*! \fn LecteurCaractere(string attaque)
	 \brief construit le lecteur pour parcourir une attaque

	 construit le lecteur de caractere à partir de la chaine (string) attaque
	 \param at - attaque
	 */
	LecteurCaractere(string at);

	/*! \fn inline char getCarCour()
	 \brief Retourne le caractere courant
	 \return le caractere courant
	 */
	inline char getCarCour()
	{
		return carCour;
	}

	/*! \fn void suivant()
	 \brief  passe au caractere suivant, s'il existe
	 */
	void suivant();

	////////////////////////////////////////////////////////////////////////////////
private:
	string f; // la chaine de texte que l'on parcourt
	char carCour; // le caractere courant
	int pos;
};

#endif /* LECTEURCARACTERE_H_ */
