#ifndef FCARAC_H_
#define FCARAC_H_

#include "Fenetre.h"
#include "Caracteristique.h"
#include "BarreBouton.h"



class FCarac : public Fenetre {
public:
	FCarac(InterfaceInfo * inter);
	void majCarac(Caracteristique * caraMaj);
	void gagneNiveau(int nbPoint);
	void cliquePoint(int id);
	Caracteristique * appliquer();

private:
	irr::gui::IGUIStaticText * t_force;
	irr::gui::IGUIStaticText * t_endurance;
	irr::gui::IGUIStaticText * t_inteligence;
	irr::gui::IGUIStaticText * t_volonte;
	irr::gui::IGUIStaticText * t_initiative;
	irr::gui::IGUIStaticText * t_agilite;
	irr::gui::IGUIStaticText * v_force;
	irr::gui::IGUIStaticText * v_endurance;
	irr::gui::IGUIStaticText * v_inteligence;
	irr::gui::IGUIStaticText * v_volonte;
	irr::gui::IGUIStaticText * v_initiative;
	irr::gui::IGUIStaticText * v_agilite;
	irr::gui::IGUIStaticText * t_pointDispo;
	irr::gui::IGUIStaticText * v_pointDispo;
	Caracteristique * caraSave;
	Caracteristique * caraNv;
	BarreBouton * barre;
	BarreBouton * barreF;
	int pointDispo;
};

#endif /* FCARAC_H_ */
