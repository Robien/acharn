#ifndef DEF_CONST
#define DEF_CONST
/*
 * =====================================================================================
 *
 *       Filename:  const.h
 *
 *    Description:  Des types constant ....
 *
 *        Version:  1.0
 *        Created:  08/04/2010 18:31:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>

using namespace std;

enum
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	ID_IsNotPickable = 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be picked by ray selection.
	IDFlag_IsPickable = 1 << 0,

	// I use this flag in ISceneNode IDs to indicate that the
	// scene node can be highlighted.  In this example, the
	// homonids can be highlighted, but the level mesh can't.
	IDFlag_IsHighlightable = 1 << 1
};
	struct coordonnee
	{
		float x;
		float y;
		float z;
	};
	struct joueur
	{
		int id; // id
		int initilisateur;
		coordonnee coord; //coordonnée de la personne
	};	
		enum { max_length = 1024 };



	float converfl(std::string txt);
	int converint(std::string txt);
	std::string converstr(int nb);
	std::string converstr(float nb);
	vector<std::string> split(const char* data, char separateur);

#endif

