#ifndef DEF_ABSTRACTOBJ
#define DEF_ABSTRACTOBJ

#include <string>
#include "const.h"
#include "Referenced.h"

using namespace std;

//classe de base de tout les objets
class AbstractObjet: public Referenced
{
public:
	AbstractObjet();
	AbstractObjet(std::string nom, std::string descrip, std::string rare, float val);
	AbstractObjet(string info, string description);
	virtual ~AbstractObjet()
	{
	}
	//description de l'objet
	std::string toString();

	//getter
	std::string getNom();
	std::string getDescription();
	std::string getRarete();
	float getValeur();
	virtual std::string toSave();

private:
	std::string m_nom;
	std::string m_description;
	std::string m_rarete;
	float m_valeur;
	float taille; //dans sac
};

#endif

