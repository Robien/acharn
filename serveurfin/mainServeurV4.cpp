/*
 * mainServeurV4.cpp
 *
 *  Created on: 22 sept. 2010
 *      Author: cephise
 */
#include "ServeurV4.h"
using asio::ip::udp;
using namespace std;
int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: ./serveur <port>\n";//on le traite de port
			return 1;
		}
		asio::io_service io_service;//creer le service udp
		char buffertime[256];
		time_t timestamp = time(NULL);
		strftime(buffertime, sizeof(buffertime), "%d/%m/%Y - %X", localtime(&timestamp));
		std::cout << "\tDémarrage du serveur 'DenverTheLastDinosaur', port: " << argv[1] << " (" << buffertime << ")" << std::endl;
		Serveur DenverTheLastDinosaur(io_service, std::atoi(argv[1]));
		//server(io_service, std::atoi(argv[1]));//on ouvre le serveur sur le port <port>
		DenverTheLastDinosaur.ecoute();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";//si y'a des exeptions, on les affichent (vive les try)
	}

	return 0;
}
