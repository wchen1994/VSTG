#include "UDPSocket.h"

UDPSocket::UDPSocket()
{
	socket.setBlocking(false);
	mode = COUNT;
}

bool UDPSocket::Host(const unsigned short port)
{
	try {
		mode = Mode::HOST;
		socket.bind(port);
	}
	catch (...) {
		return false;
	}
	return true;
}

bool UDPSocket::Join(std::string targetIp, const unsigned short targetPort, const unsigned short cli_port)
{
	try {
		mode = Mode::JOIN;
		std::string msg_out;
		socket.bind(cli_port);
		serverIp = sf::IpAddress(targetIp);
		serverPort = targetPort;
	}
	catch (...) {
		return false;
	}
	return true;
}

sf::Packet UDPSocket::Synch(sf::Packet & packet_send)
{
	sf::Packet packet_in;
	sf::IpAddress ip_in;
	unsigned short port_in;
	sf::Socket::Status status = socket.receive(packet_in, ip_in, port_in);
	switch (status)
	{
	case sf::Socket::Done:
		std::cout << "From:\t" + ip_in.toString() + ":" << port_in << "\tSize: " << packet_in.getDataSize() << std::endl;
		break;
	case sf::Socket::NotReady:
		break;
	case sf::Socket::Partial:
		assert(false);
		break;
	case sf::Socket::Disconnected:
		break;
	case sf::Socket::Error:
		assert(false);
		break;
	default:
		break;
	}

	if (!packet_send)
		return packet_in;

	switch (mode) {
	case HOST:
		for (auto pair : clinetInfo) {
			socket.send(packet_send, pair.first, pair.second);
			std::cout << "To:\t" + pair.first.toString() + ":" << pair.second << "\tSize: " << packet_send.getDataSize() << std::endl;
		}
		break;
	case JOIN:
		socket.send(packet_send, serverIp, serverPort);
		std::cout << "To:\t" + serverIp.toString() + ":" << serverPort << "\tSize: " << packet_send.getDataSize() << std::endl;
		break;
	default:
		assert(false);
	}
	return packet_in;
}

bool UDPSocket::servWait()
{		
	sf::Packet packet_in;
	sf::IpAddress remoteIp_in;
	unsigned short remotePort_in;
	
	sf::Socket::Status status = socket.receive(packet_in, remoteIp_in, remotePort_in);
	switch (status)
	{
	case sf::Socket::Done: 
		clinetInfo.insert({ remoteIp_in, remotePort_in });
		std::cout << "Connected by: " + remoteIp_in.toString() + ":" << remotePort_in << std::endl;
		return true;
		break;
	case sf::Socket::NotReady:
		break;
	case sf::Socket::Partial:
		assert(false);
		break;
	case sf::Socket::Disconnected:
		break;
	case sf::Socket::Error:
		assert(false);
		break;
	default:
		break;
	}

	return false;
}

bool UDPSocket::servTrial()
{
	sf::Packet packet_out;
	packet_out << "Greeting from Server: " << sf::IpAddress::getLocalAddress().toString();
	for (auto & pair : clinetInfo) {
		assert(socket.send(packet_out, pair.first, pair.second) == sf::Socket::Done);
	}
	return false;
}

bool UDPSocket::cliTrial()
{
	sf::Packet packet_out;
	packet_out << "Greeting from Client: " << sf::IpAddress::getLocalAddress().toString();
	assert(socket.send(packet_out, serverIp, serverPort) == sf::Socket::Done);
	return false;
}

bool UDPSocket::SendPacket(sf::Packet & packet)
{
	switch (mode) {
	case HOST:
		for (auto pair : clinetInfo) {
			assert(socket.send(packet, pair.first, pair.second) == sf::Socket::Done);
			std::cout << "To:\t" + pair.first.toString() + ":" << pair.second << "\tSize: " << packet.getDataSize() << std::endl;
		}
		break;
	case JOIN:
		assert(socket.send(packet, serverIp, serverPort) == sf::Socket::Done);
		std::cout << "To:\t" + serverIp.toString() + ":" << serverPort << "\tSize: " << packet.getDataSize() << std::endl;
		break;
	default:
		assert(false);
	}
	return true;
}

std::vector<sf::Packet> UDPSocket::GetPacket()
{
	std::vector<sf::Packet> vPackets;
	sf::Packet packet_in;
	sf::IpAddress ip_in;
	unsigned short port_in;
	while (socket.receive(packet_in, ip_in, port_in) == sf::Socket::Done) {
		vPackets.push_back(packet_in); 
		std::cout << "From:\t" + ip_in.toString() + ":" << port_in << "\tSize: " << packet_in.getDataSize() << std::endl;
	}

	return vPackets;
}
