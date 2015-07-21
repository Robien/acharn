/*
 * ObjetManager.h
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#ifndef OBJETMANAGER_H_
#define OBJETMANAGER_H_

#include "Singleton.h"
#include <irrlicht.h>
#include <iostream>
#include <vector>
#include "../include/PointeurIntelligent.h"
#include "../include/ObjetPhysique.h"
#include <map>
#include "../include/ObjetPhysiqueAnimed.h"
#include "../../ackClient/include/Protocole.h"

namespace ackCore
{

class ObjetManager: public Singleton<ObjetManager>
{
public:
    ObjetManager();
    virtual ~ObjetManager();

    void setDevice(irr::IrrlichtDevice* device);
    void setProtocol(Protocole* protocole);

    irr::scene::IAnimatedMeshSceneNode* createMeshNode(std::string path);
    irr::scene::ITriangleSelector* createAnimatedTriangleSelector(irr::scene::IAnimatedMeshSceneNode* node);

    void addObjet(ObjetPhysique* objet);
    void addObjet(ObjetPhysiqueAnimed* objet, std::string name); // avec états
    void setEtat(std::string name, int etat);
    void sendEtat(std::string name, int etat);

    void addToMeta(irr::scene::IMetaTriangleSelector * meta);

    void majAll(float delta);

    irr::IrrlichtDevice* getDevice();
private:
    PointeurIntelligent<Protocole> _protocole;
    irr::IrrlichtDevice* _device;
    std::vector<PointeurIntelligent<ObjetPhysique> > _listeObjets;
    std::map<std::string, PointeurIntelligent<ObjetPhysiqueAnimed> > _dicoObjet;
};

} // namespace ackCore

#endif /* OBJETMANAGER_H_ */
