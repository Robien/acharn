#ifndef DEF_FENETRE
#define DEF_FENETRE

#include "InterfaceInfo.h"

using namespace std;

class Fenetre : public Referenced {
public:
    Fenetre(InterfaceInfo* m_interface,
            irr::core::position2d<irr::s32> m_coord,
            const wchar_t* m_titre,
            int m_lfenetre,
            int m_hfenetre);

    void afficher();
    void cacher();

protected:
	irr::gui::IGUIWindow* fenetre;
	irr::gui::IGUIEnvironment* gui;
    irr::video::IVideoDriver* pilote;
	irr::core::rect<irr::s32> cadre;
};	
#endif

