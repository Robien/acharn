/*
 * =====================================================================================
 *
 *       Filename:  Tache.h
 *
 *    Description:  type de chose a faire sur la 3D
 *
 *        Version:  1.0
 *        Created:  25/06/2010 06:47:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef DEF_TACHEDEPLACEMENT
#define DEF_TACHEDEPLACEMENT


#include "Tache.h"
#include "Perso.h"

class TacheDeplacement : public Tache
{
public:
	TacheDeplacement(int id, float newx, float newy, float newz, float newrx, float newry, float newrz);
	virtual void execute();
private:
	float _x, _y, _z;
	float _rx, _ry, _rz;
};

#endif
