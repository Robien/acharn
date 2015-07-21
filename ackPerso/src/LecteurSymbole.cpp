/*
 * LecteurSymbole.cpp
 *
 *  Created on: 12 juin 2010
 *      Author: C. Louison
 */

/*! \file LecteurSymbole.cc
 \brief L'implementation de la classe LecteurSymbole
 \author C. Louison
 */
#include "LecteurSymbole.h"
#include <ctype.h>
#include <string.h>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
LecteurSymbole::LecteurSymbole(string at) :
	lc(at), symCour("")
{
	if (lc.getCarCour() == '<')
	{
		lc.suivant();
		suivant();
	}
	else
	{
		cout << "Erreur l'attaque ne commence pas par '<'" << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////
void LecteurSymbole::suivant()
{
	sauterSeparateurs();
	// on est maintenant positionne sur le premier caractère d'un symbole
	symCour = Symbole(motSuivant()); // on reconstruit symCour avec le nouveau mot lu

}

////////////////////////////////////////////////////////////////////////////////
void LecteurSymbole::sauterSeparateurs()
{
	while (lc.getCarCour() == ' ' || lc.getCarCour() == '\t' || lc.getCarCour() == '\r' || lc.getCarCour() == '\n')
		lc.suivant();
}

////////////////////////////////////////////////////////////////////////////////
string LecteurSymbole::motSuivant()
{
	static string s;
	s = "";

	if (isdigit(lc.getCarCour()))
	{// c'est le début d'une valeur
		do
		{
			s = s + lc.getCarCour();
			lc.suivant();
		} while (isdigit(lc.getCarCour()) || lc.getCarCour() == '.');
	}
	else if (lc.getCarCour() == '<')
	{
		s = s + lc.getCarCour();
		lc.suivant();
		if (lc.getCarCour() != '=')// c'est le début d'une sous attaque
		{
			while (lc.getCarCour() != '>')
			{
				s = s + lc.getCarCour();
				lc.suivant();
			}
			s = s + '>';
			lc.suivant();
		}
		else
		{
			s = s + lc.getCarCour();
			lc.suivant();
		}
	}
	else if (lc.getCarCour() == '>')
	{
		s = s + lc.getCarCour();
		lc.suivant();
		if (lc.getCarCour() == '\0' && lc.getCarCour() != '=')// c'est le début d'une sous attaque
		{
			s = "";
		}
		else
		{
			s = s + lc.getCarCour();
			lc.suivant();
		}
	}
	else if (lc.getCarCour() == '$' || lc.getCarCour() == '@')
	{// c'est le début d'une caracteristique d'une attaque
		do
		{
			s = s + lc.getCarCour();
			lc.suivant();
		} while (isalpha(lc.getCarCour()) || lc.getCarCour() == '_');
	}
	else if (lc.getCarCour() == '#')
	{// c'est le début d'une caracteristique d'une attaque
		do
		{
			s = s + lc.getCarCour();
			lc.suivant();
		} while (isalpha(lc.getCarCour()) || lc.getCarCour() == '_');
	}
	else if (lc.getCarCour() == '"')
	{// c'est le début de chaine
		do
		{
			s = s + lc.getCarCour();
			lc.suivant();
		} while (lc.getCarCour() != '"');
		s = s + '"';
		lc.suivant();
	}
	else if (lc.getCarCour() != '\0' && lc.getCarCour() != '>')
	// c'est un caractere special = + - * / % random
	{
		if (lc.getCarCour() != 'R')
		{
			s = s + lc.getCarCour();
			lc.suivant(); //rajouter
			if (s.compare(string("=")) == 0 && lc.getCarCour() == '=')
			{
				s = s + lc.getCarCour();
				lc.suivant();
			}

		}
		else
		{
			do
			{
				s = s + lc.getCarCour();
				lc.suivant();
			} while (lc.getCarCour() != '(');
			s = s + '(';
			lc.suivant();
		}

	}
	//sinon c'est que c'est la fin


	return s;
}
