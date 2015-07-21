/*
 * Equipement.h
 *
 *  Created on: 24 juin 2010
 *      Author: cephise
 */

#ifndef EQUIPEMENT_H_
#define EQUIPEMENT_H_
#define NBOBJET 9

#include "AbstractArme.h"
#include "ObjetEquipement.h"
//#include "PointeurIntelligent.h"

struct Equipement
{

public:

	Equipement()
	{
		ADeuxMains = false;
		//objets = new AbstractEquipement[NBOBJET];
		for (int i = 0; i < NBOBJET; i++)
		{
			objets[i] = NULL;
		}
		m_armes[0] = NULL;
		m_armes[1] = NULL;
		totalArmure = 0;
		totalArmureMagique = 0;
	}

	~Equipement()
	{
		/*for(int i=0;i<NBOBJET;i++)
		 {
		 delete objets[i];
		 }*/
	}

	ObjetEquipement* ajouter(ObjetEquipement* equip)
	{
		ObjetEquipement* ancienEquip = NULL;
		if (objets[equip->getTypeEquipe()] == NULL)//pas encore d'objet a cette endroit
		{
			objets[equip->getTypeEquipe()] = equip;
		}
		else
		{
			ancienEquip = objets[equip->getTypeEquipe()];
			objets[equip->getTypeEquipe()] = equip;
			totalArmure -= ancienEquip->getArmure();
			totalArmureMagique -= ancienEquip->getArmureMagique();
		}
		totalArmure += equip->getArmure();
		totalArmureMagique += equip->getArmureMagique();
		return ancienEquip;
	}

	vector<AbstractArme*> ajouterArme(AbstractArme* arme1, int position)
	{
		vector<AbstractArme*> vectarme;
		if (position != 0 && position != 1)
		{
			if (armeAt(0))
			{
				vectarme.push_back(m_armes[0]);
			}
			if (armeAt(1))
			{
				vectarme.push_back(m_armes[1]);
				m_armes[1] = NULL;
			}
			m_armes[0] = arme1;
			ADeuxMains = true;
		}
		else
		{
			if (armeAt(position))
			{
				vectarme.push_back(m_armes[position]);
				if (position == 1 && ADeuxMains)
				{
					vectarme.push_back(m_armes[0]);
				}
			}
			m_armes[position] = arme1;
			ADeuxMains = false;
		}
		return vectarme;
	}

	AbstractArme* enleverArme(int position)
	{
		AbstractArme* ancienneArme = NULL;
		if (position != 0 && position != 1)
		{
			if (armeAt(0))
			{
				ancienneArme = m_armes[0];
				objets[0] = NULL;
				ADeuxMains = false;
			}
		}
		else
		{
			if (armeAt(position))
			{
				ancienneArme = m_armes[position];
				objets[position] = NULL;
			}
		}

		return ancienneArme;
	}

	bool armeAt(int position)//attention valeur possible 0 ou 1
	{
		return m_armes[position] != NULL;
	}

	ObjetEquipement* enlever(ObjetEquipement::e_Position posi)
	{
		ObjetEquipement* ancienEquip = objets[posi];
		objets[posi] = NULL;
		totalArmure -= ancienEquip->getArmure();
		totalArmureMagique -= ancienEquip->getArmureMagique();
		return ancienEquip;
	}

	ObjetEquipement* getEquippement(ObjetEquipement::e_Position posi)
	{
		return objets[posi];
	}

	void AfficherTout()
	{
		for (int i = 0; i < NBOBJET; i++)
		{
			if (objets[i] != NULL)
			{
				std::cout << objets[i]->toString() << endl;
			}
		}
	}

	bool haveArme2M()
	{
		return ADeuxMains;
	}

	bool haveArme()
	{
		return (m_armes[0] != NULL || m_armes[1] != NULL);
	}

	float getArmure()
	{
		return 0;
	}

	float getArmureMagique()
	{
		return 0;
	}

	string enChaine()
	{
		int j = 0;
		bool premier = false;
		string retour;

		while (!premier && j < NBOBJET)
		{
			if (objets[j] != NULL)
			{
				retour = objets[j]->toSave();
				premier = true;
			}
			++j;
		}

		while (j < NBOBJET)
		{
			retour += "!" + objets[j]->toSave();
			if (objets[j] != NULL)
			{
				retour += "!" + objets[j]->toSave();
			}
			++j;
		}

		if (m_armes[0] != NULL)
		{
			if (!premier)
			{
				retour = m_armes[0]->toSave();
			}
			else
			{
				retour += "!" + m_armes[0]->toSave();
			}
		}

		if (m_armes[1] != NULL)
		{
			if (!premier)
			{
				retour = m_armes[1]->toSave();
			}
			else
			{
				retour += "!" + m_armes[1]->toSave();
			}

		}
		return retour;
	}

	//variable
private:

	float totalArmure;
	float totalArmureMagique;
	ObjetEquipement* objets[NBOBJET];
	AbstractArme *m_armes[2];
	//PointeurIntelligent<ObjetEquipement> objets[NBOBJET];
	//PointeurIntelligent<AbstractArme> m_armes[2];
	bool ADeuxMains;
};

#endif /* EQUIPEMENT_H_ */
