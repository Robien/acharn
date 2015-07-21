#ifndef DEF_ABSTRACTOBJSIMPLE
#define DEF_ABSTRACTOBJSIMPLE

#include "AbstractObjet.h"
#include <string>

using namespace std;

//classe represantant tout les objets non equipable
class AbstractObjSimple: public AbstractObjet
{
public:
	AbstractObjSimple();
	AbstractObjSimple(std::string nom, std::string descrip, std::string rare, float val);
	AbstractObjSimple(string infoobjsim, string infoObjet);
	virtual std::string toSave();
};

#endif
