/*
 * =====================================================================================
 *
 *       Filename:  TacheDeplacement.cpp
 *
 *    Description: Tache gérant le déplacement 
 *
 *        Version:  1.0
 *        Created:  25/06/2010 08:06:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "TacheDeplacement.h"
#include "../include/PersoManager.h"

TacheDeplacement::TacheDeplacement(int id, float newx, float newy, float newz,  float newrx, float newry, float newrz) : Tache(id), _x(newx), _y(newy), _z(newz), _rx(newrx), _ry(newry), _rz(newrz)
{

}
void TacheDeplacement::execute()
{
		PersoManager::get()->getPersoById(_id)->teleport(_x,_y,_z);
		PersoManager::get()->getPersoById(_id)->tourner(_rx, _ry, _rz);
}
