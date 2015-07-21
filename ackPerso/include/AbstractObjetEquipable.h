/*
 * AbstractObjetEquipable.h
 *
 *  Created on: 17 sept. 2010
 *      Author: cephise
 */

#ifndef ABSTRACTOBJETEQUIPABLE_H_
#define ABSTRACTOBJETEQUIPABLE_H_

#include "AbstractObjet.h"
#include "Caracteristique.h"
#include "const.h"

class AbstractObjetEquipable: public AbstractObjet
{
public:
	AbstractObjetEquipable();
	AbstractObjetEquipable(std::string nom, std::string descrip, std::string rare, float val, Caracteristique bon);
	AbstractObjetEquipable(std::string infoObjetequi, std::string infoobj, std::string description);
	virtual ~AbstractObjetEquipable();

	//description de l'objet
	std::string toString();
	void setBonus(std::string attri, float valeur);

	Caracteristique getCaracteristique();
	float getUsure();
	float getSolidite();

	virtual std::string toSave();

private:
	float m_usure;
	float m_solidite; //usure max
	Caracteristique m_bonus;
};

#endif /* ABSTRACTOBJETEQUIPABLE_H_ */
