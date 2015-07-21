#ifndef DEF_ABSTRACTEQUI
#define DEF_ABSTRACTEQUI

#include "AbstractObjetEquipable.h"
#include <string>

using namespace std;
//classe represantant tout les objets equipables
class ObjetEquipement: public AbstractObjetEquipable
{
public:
	typedef enum
	{
		MAIND, MAING, TETE, TORSE, JAMBE, PIEDD, PIEDG, BRAS, EPAULE, INDEFINI
	} e_Position;
	ObjetEquipement();
	virtual ~ObjetEquipement()
	{
	}
	ObjetEquipement(std::string nom, std::string descrip, std::string rare, float val, Caracteristique bon, e_Position tpequi = INDEFINI);
	ObjetEquipement(string infoObjet);
	//getter
	e_Position getTypeEquipe();
	float getArmure();
	float getArmureMagique();

	std::string toSave();

private:
	float m_armure;
	float m_armureMagique;

	e_Position typeEquipe;

};

class ObjectEquipement
{
};

#endif
