/*
 * TacheTalkPnj.h
 *
 *  Created on: 2 nov. 2010
 *      Author: cephise
 */

#ifndef TACHETALKPNJ_H_
#define TACHETALKPNJ_H_

#include "Tache.h"
#include "string"
#include "PersoNonJoueur.h"

using namespace std;

class TacheTalkPnj: public Tache
{
public:

	TacheTalkPnj(float newx, float newy, float newz, int type, std::string infoJoueur);
	virtual ~TacheTalkPnj();
	void execute();

private:

	int _type;
	std::string _infoJoueur;
	PersoNonJoueur* pnj;
};

#endif /* TACHETALKPNJ_H_ */
