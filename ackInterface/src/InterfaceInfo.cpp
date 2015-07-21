#include "InterfaceInfo.h"

using namespace std;

InterfaceInfo::InterfaceInfo(irr::video::IVideoDriver* pilote,
        					 irr::gui::IGUIEnvironment* gui,
        					 Skin * skin,
        					 Police * police){
    this->pilote = pilote;
    this->gui = gui;
    this->skin = skin;
    this->police = police;
}

InterfaceInfo* InterfaceInfo::getInferfaceInfo(){
    return (this);
}

irr::video::IVideoDriver* InterfaceInfo::getPilote(){
    return (this->pilote);
}

irr::gui::IGUIEnvironment* InterfaceInfo::getGui(){
    return (this->gui);
}

Skin* InterfaceInfo::getSkin(){
    return (this->skin);
}

Police* InterfaceInfo::getPolice(){
    return (this->police);
}
