#include "FCarac.h"

FCarac::FCarac(InterfaceInfo * inter) :
    Fenetre(inter, irr::core::position2d<irr::s32>(10, 100), L"Caractéristiques", 164, 116)
{
    caraSave = NULL;
    pointDispo = 0;

    //texte des caractéristiques
    t_force = inter->getGui()->addStaticText(L"Force : ", irr::core::rect<irr::s32>(2, 2, 100, 14), false, true, fenetre, -1, true);
    t_endurance = inter->getGui()->addStaticText(L"Endurance : ", irr::core::rect<irr::s32>(2, 16, 100, 28), false, true, fenetre, -1, true);
    t_inteligence = inter->getGui()->addStaticText(L"Inteligence : ", irr::core::rect<irr::s32>(2, 30, 100, 42), false, true, fenetre, -1, true);
    t_volonte = inter->getGui()->addStaticText(L"Volonté : ", irr::core::rect<irr::s32>(2, 44, 100, 56), false, true, fenetre, -1, true);
    t_initiative = inter->getGui()->addStaticText(L"Initiative : ", irr::core::rect<irr::s32>(2, 58, 100, 70), false, true, fenetre, -1, true);
    t_agilite = inter->getGui()->addStaticText(L"Agilité : ", irr::core::rect<irr::s32>(2, 72, 100, 84), false, true, fenetre, -1, true);

    //valeur des caractéristiques
    v_force = inter->getGui()->addStaticText(L"0", irr::core::rect<irr::s32>(102, 2, 134, 14), true, true, fenetre, -1, true);
    v_endurance = inter->getGui()->addStaticText(L"0", irr::core::rect<irr::s32>(102, 16, 134, 28), true, true, fenetre, -1, true);
    v_inteligence = inter->getGui()->addStaticText(L"0", irr::core::rect<irr::s32>(102, 30, 134, 42), true, true, fenetre, -1, true);
    v_volonte = inter->getGui()->addStaticText(L"0", irr::core::rect<irr::s32>(102, 44, 134, 56), true, true, fenetre, -1, true);
    v_initiative = inter->getGui()->addStaticText(L"0", irr::core::rect<irr::s32>(102, 58, 134, 70), true, true, fenetre, -1, true);
    v_agilite = inter->getGui()->addStaticText(L"0", irr::core::rect<irr::s32>(102, 72, 134, 84), true, true, fenetre, -1, true);

    //cadre pour le gain de niveau
    t_pointDispo = inter->getGui()->addStaticText(L"Points disponibles : ", irr::core::rect<irr::s32>(2, 86, 134, 98), false, true, fenetre, -1, true);
    v_pointDispo = inter->getGui()->addStaticText(L"0", irr::core::rect<irr::s32>(136, 86, 162, 98), true, true, fenetre, -1, true);

    //bouton + et -
    barre = new BarreBouton(inter, irr::core::position2d<irr::s32>(134, 0), 14, 14, 2, 6, fenetre);
    for (int i = 1; i <= barre->getNbBouton(); i++)
    {
        if ((i % 2) == 1)
        {
            barre->getBouton(i)->setBoutonImage("plus.png");
        }
        else
        {
            barre->getBouton(i)->setBoutonImage("moins.png");
        }
        barre->getBouton(i)->getBouton()->setID(7200 + i);
    }

    //bouton de fenetre
    barreF = new BarreBouton(inter, irr::core::position2d<irr::s32>(0, 100), 80, 14, 2, 1, fenetre);
    barreF->getBouton(1)->setBoutonTexte("Appliquer");
    barreF->getBouton(1)->getBouton()->setID(7301);
    barreF->getBouton(2)->setBoutonTexte("Fermer");
    barreF->getBouton(2)->getBouton()->setID(7302);

}

void FCarac::majCarac(Caracteristique * caraMaj)
{
    caraNv = caraMaj;
    v_force->setText(irr::core::stringw((converstr((int) caraNv->m_force)).c_str()).c_str());
    v_endurance->setText(irr::core::stringw((converstr((int) caraNv->m_endurance)).c_str()).c_str());
    v_inteligence->setText(irr::core::stringw((converstr((int) caraNv->m_inteligence)).c_str()).c_str());
    v_volonte->setText(irr::core::stringw((converstr((int) caraNv->m_volonte)).c_str()).c_str());
    v_initiative->setText(irr::core::stringw((converstr((int) caraNv->m_initiative)).c_str()).c_str());
    v_agilite->setText(irr::core::stringw((converstr((int) caraNv->m_agilite)).c_str()).c_str());
}

void FCarac::gagneNiveau(int nbPoint)
{
    pointDispo += nbPoint;

    v_pointDispo->setText(irr::core::stringw((converstr(pointDispo)).c_str()).c_str());

    //sauvegarder l'actuel cara
    if (caraSave != NULL)
    {
//        delete caraSave;
    }
    caraSave = new Caracteristique();
    (*caraSave) = (*caraNv);
}

void FCarac::cliquePoint(int id)
{
    //l'utilisateur clique sur un bouton
    switch (id)
    {
    case 7201:
        //bouton +
        if (pointDispo > 0)
        {
            //s'il reste des points à distribuer
            caraNv->setAttribut("force", caraNv->m_force + 1);
            pointDispo -= 1;
        }
        break;
    case 7202:
        //bouton -
        if (caraNv->m_force - 1 >= caraSave->m_force)
        {
            //si on ne passe pas en dessous de l'ancienne valeur
            caraNv->setAttribut("force", caraNv->m_force - 1);
            pointDispo += 1;
        }
        break;
    case 7203:
        //bouton +
        if (pointDispo > 0)
        {
            //s'il reste des points à distribuer
            caraNv->setAttribut("endurance", caraNv->m_endurance + 1);
            pointDispo -= 1;
        }
        break;
    case 7204:
        //bouton -
        std::cout << caraNv->m_endurance << " - " <<  caraSave->m_endurance << std::endl;
        if (caraNv->m_endurance - 1 >= caraSave->m_endurance)
        {
            //si on ne passe pas en dessous de l'ancienne valeur
            caraNv->setAttribut("endurance", caraNv->m_endurance - 1);
            pointDispo += 1;
        }
        break;
    case 7205:
        //bouton +
        if (pointDispo > 0)
        {
            //s'il reste des points à distribuer
            caraNv->setAttribut("inteligence", caraNv->m_inteligence + 1);
            pointDispo -= 1;
        }
        break;
    case 7206:
        //bouton -
        if (caraNv->m_inteligence - 1 >= caraSave->m_inteligence)
        {
            //si on ne passe pas en dessous de l'ancienne valeur
            caraNv->setAttribut("inteligence", caraNv->m_inteligence - 1);
            pointDispo += 1;
        }
        break;
    case 7207:
        //bouton +
        if (pointDispo > 0)
        {
            //s'il reste des points à distribuer
            caraNv->setAttribut("volonte", caraNv->m_volonte + 1);
            pointDispo -= 1;
        }
        break;
    case 7208:
        //bouton -
        if (caraNv->m_volonte - 1 >= caraSave->m_volonte)
        {
            //si on ne passe pas en dessous de l'ancienne valeur
            caraNv->setAttribut("volonte", caraNv->m_volonte - 1);
            pointDispo += 1;
        }
        break;
    case 7209:
        //bouton +
        if (pointDispo > 0)
        {
            //s'il reste des points à distribuer
            caraNv->setAttribut("initiative", caraNv->m_initiative + 1);
            pointDispo -= 1;
        }
        break;
    case 7210:
        //bouton -
        if (caraNv->m_initiative - 1 >= caraSave->m_initiative)
        {
            //si on ne passe pas en dessous de l'ancienne valeur
            caraNv->setAttribut("initiative", caraNv->m_initiative - 1);
            pointDispo += 1;
        }
        break;
    case 7211:
        //bouton +
        if (pointDispo > 0)
        {
            //s'il reste des points à distribuer
            caraNv->setAttribut("agilite", caraNv->m_agilite + 1);
            pointDispo -= 1;
        }
        break;
    case 7212:
        //bouton -
        if (caraNv->m_agilite - 1 >= caraSave->m_agilite)
        {
            //si on ne passe pas en dessous de l'ancienne valeur
            caraNv->setAttribut("initiative", caraNv->m_agilite - 1);
            pointDispo += 1;
        }
        break;
    }
    v_pointDispo->setText(irr::core::stringw((converstr(pointDispo)).c_str()).c_str());
    majCarac(caraNv);
}

Caracteristique * FCarac::appliquer()
{
    //l'utilisateur clique sur appliquer

	if (pointDispo==0) {
		//sauvegarde de cara
		caraSave = caraNv;
	}

    //retourner cara pour maj du perso
    return caraSave;
}
