#ifndef DEF_ABSTRACTARME
#define DEF_ABSTRACTARME

#include "AbstractObjetEquipable.h"
#include <string>

class AbstractArme: public AbstractObjetEquipable
{
public:
	typedef enum
	{
		EPEE, HACHE, BATON, COUTEAU, ARC, ARBALETTE, FUSIL
	} e_Type;
	AbstractArme();
	AbstractArme(std::string nom, Caracteristique carac, e_Type type, float degats, float rechg = 1, float portee = 1); //utilisé par les autre constructeur uniquement
	AbstractArme(string infoArme, string infoObjetequi, string infoObjet);
	virtual ~AbstractArme();
	void afficher();
	void setUsure(float newusure);
	void reparer();
	bool is1Hand();
	string getTypeStr();

	float getPuissance();
	float getRecharge();
	float getPortee();
	float getPoids();
	e_Type getType();

	virtual std::string toSave();

protected:

	e_Type m_type; //type de l'arme(0:main nu, 1:épée une main, 2:deux mains, 3:distance...)
	float m_puissance;
	float m_recharge; //temps entre deux attaques
	float m_portee;
	float m_poids;
};

#endif

