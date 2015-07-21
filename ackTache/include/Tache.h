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

#ifndef DEF_TACHE
#define DEF_TACHE

#include "../include/Referenced.h"

class Tache: public Referenced
{
public:
	Tache(int id);
	Tache();
	virtual void execute()=0;
protected:
	int _id;
};

#endif
