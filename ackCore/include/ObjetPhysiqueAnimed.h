/*
 * ObjetPhysiqueAnimed.h
 *
 *  Created on: 19 sept. 2010
 *      Author: romain
 */

#ifndef OBJETPHYSIQUEANIMED_H_
#define OBJETPHYSIQUEANIMED_H_

#include "ObjetPhysique.h"
#include "../include/PointeurIntelligent.h"
#include "../include/SuiteAnimations.h"
#include "../include/EtatObjet.h"
#include <vector>
#include <map>

namespace ackCore
{

class ObjetPhysiqueAnimed: public ackCore::ObjetPhysique
{
public:
    ObjetPhysiqueAnimed();
    virtual ~ObjetPhysiqueAnimed();

    void setSuiteAnimation(SuiteAnimations* suiteAnim);

    void maj(float delta);

    void setListeEtat(std::map<int, PointeurIntelligent<EtatObjet> >* listeEtat);
    void addEtat(int num, EtatObjet* etat);
    void setEtat(int i, std::string name);

private:
    PointeurIntelligent<SuiteAnimations> _anim;

    unsigned int _animCourrente;

    float _tempsAvantFinAnim;
    bool _isAnimSet;

private:
    float calculTempsAvantFin();
    float valeurAbsolue(float x); // sinon (abs) ça transforme en int >_>
    std::map<int, PointeurIntelligent<EtatObjet> >* _listeEtat;
    PointeurIntelligent<EtatObjet> _etatCourent;
    bool _withEtat;
};

} // namespace ackCore

#endif /* OBJETPHYSIQUEANIMED_H_ */
