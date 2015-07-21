#ifndef DEF_InterfaceInfo
#define DEF_InterfaceInfo

#include "../../ackUtils/include/Referenced.h"
#include "Police.h"
#include "Skin.h"
#include "const.h"

using namespace std;

class InterfaceInfo : public Referenced {
public:
    InterfaceInfo(irr::video::IVideoDriver* m_pilote,
    			  irr::gui::IGUIEnvironment* m_gui,
    			  Skin * skin,
    			  Police * police);

    InterfaceInfo* getInferfaceInfo();
    irr::video::IVideoDriver* getPilote();
    irr::gui::IGUIEnvironment* getGui();
    Skin * getSkin();
    Police * getPolice();

private:
    irr::video::IVideoDriver* pilote;
    irr::gui::IGUIEnvironment* gui;
    Skin * skin;
    Police * police;
};


#endif
