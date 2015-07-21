#include "AbstractObjSimple.h"
#include <string>

using namespace std;

AbstractObjSimple::AbstractObjSimple() :
	AbstractObjet()
{

}
AbstractObjSimple::AbstractObjSimple(std::string nom, std::string descrip, std::string rare, float val) :
	AbstractObjet(nom, descrip, rare, val)
{
}

AbstractObjSimple::AbstractObjSimple(string infodescrip, string infoObjet)
{
	string description = "Objet (" + infodescrip + ")";
	AbstractObjet(infoObjet, description);
}

std::string AbstractObjSimple::toSave()
{

	return ":"+ AbstractObjet::toSave();
}
