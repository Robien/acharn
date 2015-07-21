/*
 * TacheSetAnime.h
 *
 *  Created on: 5 août 2010
 *      Author: romain
 */

#ifndef TACHESETANIME_H_
#define TACHESETANIME_H_

#include "Tache.h"
#include "Perso.h"

class TacheSetAnime: public Tache
{

public:

	TacheSetAnime(int id, Perso::typeAnim typeAnim, bool lock=true);
	virtual ~TacheSetAnime();
	void execute();

private:

	Perso::typeAnim _typeAnim;
	bool _lock;

};

#endif /* TACHESETANIME_H_ */
