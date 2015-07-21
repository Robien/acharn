#ifndef FETAT_H_
#define FETAT_H_

#include "Fenetre.h"
#include "BarreActive.h"
#include "BarreBouton.h"

class FEtat : public Fenetre {
public:
	FEtat(InterfaceInfo* inter);
	void setPseudo(string psd);
	void setNiveau(string nv);
	void setVieMax(int vieMax);
	void setVieVal(int vieVal);
	void setPouvoirMax(int pvrMax);
	void setPouvoirVal(int pvrVal);
	void setExperienceMax(int xpMax);
	void setExperienceVal(int xpVal);

private:
	irr::gui::IGUIImage * avatar;
	irr::gui::IGUIStaticText * pseudo;
	irr::gui::IGUIStaticText * niveau;
	BarreActive * vie;
	BarreActive * pouvoir;
	BarreActive * experience;
};

#endif /* FETAT_H_ */
