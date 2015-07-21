#ifndef DEF_FBARREACTION
#define DEF_FBARREACTION

#include "BarreBouton.h"
#include "Fenetre.h"
using namespace std;

class FBarreAction : public Fenetre {
public:
    FBarreAction(InterfaceInfo* inter);

private:
	BarreBouton * barre;

};

#endif
