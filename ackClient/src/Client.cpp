#include "Client.h"

using namespace std;
using boost::asio::ip::udp;

//ProtocoleV2//
void* Client::recup(Client *cli)
{
	while (cli->_threadActif)
	{
		cli->fini = false;
		udp::socket* s = cli->getsocket();
		char data[max_length];
		udp::endpoint sender_endpoint;
		std::size_t taille = s->receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
		data[taille] = '\0';
		cli->m_protocole->rcvData(data);
		cli->fini = true;

	}
	return NULL;
}

//ProtocoleV2//
Client::Client(const char* host, const char* port, AbstractProtocole* p_proto) :
	m_connect(false), m_id(0)
{
	m_protocole = p_proto;
	m_socket = new udp::socket(io_service, udp::endpoint(udp::v4(), 0)); //socket: s
	resolver = new udp::resolver(io_service);
	udp::resolver::query query(udp::v4(), host, port);
	iterator = resolver->resolve(query);
	m_nbj = 0;
	m_joueurs = NULL;
	m_tempsRestant = -1;
	messageReception = "NULL";
	idMessage = 0;

}

Client::~Client()
{
	//	deconnexion(); // si on oubli la déco, ça le fait a la déstruction ?
	delete m_socket;
	delete resolver;
	delete[] m_joueurs;
	//	UnThread->join();
	_threadActif = false;
	//	delete UnThread;
}

//ProtocoleV2//
void Client::envoyer(const char* data)
{
	//size_t data_length = std::strlen(data);
	m_socket->send_to(boost::asio::buffer(data, std::strlen(data)), *iterator);
}

int Client::debRecep() // by Romain
{
	_threadActif = true;
	fini = false;
	UnThread = new std::thread(&Client::recup, this);

	return 0;
}

int Client::finRecep()//by Romain
{
	_threadActif = false;
	fini = true;
	delete UnThread;
	return 0;
}

int Client::calculReception(float tempsEcoule) // by Romain
{
	if (m_tempsRestant <= 0)
	{
		debRecep();
		m_tempsRestant = 10;
	}
	m_tempsRestant -= tempsEcoule;
	if (m_tempsRestant <= 0 || fini)
	{
		if (fini)
		{
			std::cout << "ping : " << (1 - m_tempsRestant) << "ms " << std::endl;
		}
		m_tempsRestant = 1;
		//finRecep();
		//debRecep();
	}

	return 0;
}

udp::socket *Client::getsocket()
{
	return m_socket;

}

