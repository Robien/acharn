#ifndef ABSTRACTPROTOCOLE_H_
#define ABSTRACTPROTOCOLE_H_

#include "../include/Referenced.h"

using namespace std;

class AbstractProtocole : public Referenced
{

public:

	AbstractProtocole() {}
	virtual void rcvData(char* data) =0;

};

#endif /* ABSTRACTPROTOCOLE_H_*/
