/*
 * Symbole.cpp
 *
 *  Created on: 12 juin 2010
 *      Author: C. Louison
 */

/*! \file Symbole.cc
 \brief L'implementation de la classe Symbole
 \author C. Louison
 \date 19.05.2010
 */
#include <ctype.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "Symbole.h"

////////////////////////////////////////////////////////////////////////////////
Symbole::Symbole(string s)
{
	this->chaine = s;

	if (s == "" || s == "\0")
	{
		this->categorie = FINDATTAQUE;
	}
	else if (s[0] == '"' && s[s.size() - 1] == '"')
	{
		this->categorie = CHAINE;
	}
	else if (s[0] == '<' && s[s.size() - 1] == '>')
	{
		this->categorie = SOUSATTAQUE;
	}
	else if (isdigit(s[0]))
	{
		this->categorie = VALEUR;
	}
	else if (isMotCle(s))
	{
		this->categorie = MOTCLE;
	}
	else if (s[0] == '$' || s[0] == '@')
	{
		this->categorie = CARACTERISTIQUE;
	}
	else if (s[0] == '#')
	{
		this->categorie = ATTRIBUT;
	}
	else
	{
		this->categorie = INDEFINI;
		cout << "indefini";

	}
}

////////////////////////////////////////////////////////////////////////////////
bool Symbole::operator ==(string ch)
{
	return this->chaine == ch || (this->categorie == CARACTERISTIQUE && ch == "<CARACTERISTIQUE>") || (this->categorie == ATTRIBUT && ch == "<ATTRIBUT>") || (this->categorie == INDEFINI && ch
			== "<INDEFINI>") || (this->categorie == CHAINE && ch == "<CHAINE>") || (this->categorie == SOUSATTAQUE && ch == "<SOUSATTAQUE>") || (this->categorie == MOTCLE && ch == "<MOTCLE>")
			|| (this->categorie == FINDATTAQUE && ch == "<FINDATTAQUE>") || (this->categorie == VALEUR && ch == "<VALEUR>");
}

////////////////////////////////////////////////////////////////////////////////
bool Symbole::isMotCle(string s)
{
	static vector<string> motsCles; // vecteur pour stocker les mots clés du langage
	// si on n'a pas encore chargé les mots clés dans le vecteur, on le fait !
	if (motsCles.empty())
	{
		motsCles.push_back("=");
		motsCles.push_back("+");
		motsCles.push_back("-");
		motsCles.push_back("*");
		motsCles.push_back("/");
		motsCles.push_back("%");
		motsCles.push_back(")");
		motsCles.push_back("(");
		motsCles.push_back("Random(");
		motsCles.push_back("==");
		motsCles.push_back(">=");
		motsCles.push_back("<=");
	}

	// on recherche s dans le vecteur des mots clés triés
	unsigned int i;
	for (i = 0; i < motsCles.size() && !(motsCles[i] == s); i++)
		;
	return (i < motsCles.size() && motsCles[i] == s);
}
