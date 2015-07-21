#include "Sac.h"

Sac::Sac(unsigned taille)
{
	tailleMax = taille;
}

void Sac::ajouter(AbstractObjet* item)
{
	if (l_Sac.size() < tailleMax)
	{
		l_Sac.push_back(item);
	}
	else
	{
		std::cout << "erreur: sac plein" << std::endl;
	}
}

unsigned int Sac::GetTaille()
{
	return l_Sac.size();
}

AbstractObjet* Sac::enlever(unsigned int numitem)
{
	AbstractObjet* ancienObj = l_Sac[numitem];
	l_Sac.erase(l_Sac.begin() + numitem);
	return ancienObj;
}

string Sac::enChaine()
{
	string retour;
	if (l_Sac.size() > 0)
	{
		retour = l_Sac[0]->toSave();
		for (unsigned int i = 1; i < l_Sac.size(); i++)
		{
			retour += "!" + l_Sac[i]->toSave();
		}
	}
	return retour;
}
