#include "UDPSocket.h"

namespace CommResMeth {

	UDPSocket::UDPSocket()
	{
		socket.setBlocking(false);
		mode = OFFLINE;
	}

	bool UDPSocket::Host(const unsigned short port)
	{
		try {
			mode = Mode::HOST;
			socket.unbind();
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
			socket.unbind();
			socket.bind(cli_port);
			serverIp = sf::IpAddress(targetIp);
			serverPort = targetPort;
		}
		catch (...) {
			return false;
		}
		return true;
	}

	bool UDPSocket::Synch()
	{
		sf::Packet packet;
		packet << 1;
		int num;
		std::map<std::string, int> numMap;
		if (mode == HOST) {
			for (int i = 0; i < int(clientInfo.size());) {
				size_t size_in;
				sf::IpAddress address_in;
				unsigned short port_in;
				while (socket.receive(&num, sizeof(int), size_in, address_in, port_in) != sf::Socket::Done);
				numMap[address_in.toString()] = num;
				i++;
			}
			for (auto &pair : clientInfo) {
				socket.send(&numMap[pair.first.toString()], sizeof(int), pair.first, pair.second);
			}
		}
		else if (mode == JOIN) {
			int num = rand();
			size_t size_in;
			sf::IpAddress address_in;
			unsigned short port_in;
			socket.send(&num, sizeof(int), serverIp, serverPort);
			int num_in;
			while (socket.receive(&num_in, sizeof(int), size_in, address_in, port_in) != sf::Socket::Done);
			assert(num_in == num);
			if (num_in != num)
				return false;
		}
		else {
			assert(false);
			return false;
		}

		return true;
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
		{
#if defined(_DEBUG_VERBOSE) && defined(_DEBUG)
			std::cout << "Connected by: " + remoteIp_in.toString() + ":" << remotePort_in << std::endl;
#endif
			const std::pair<sf::IpAddress, unsigned short> pair = { remoteIp_in, remotePort_in };
			if (std::find(clientInfo.begin(), clientInfo.end(), pair) == clientInfo.end()) {
				clientInfo.push_back({ remoteIp_in, remotePort_in }); // Being a vector will get increase even with same item
				return true;
			}
			break;
		}
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
		for (auto & pair : clientInfo) {
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
			for (auto pair : clientInfo) {
				assert(socket.send(packet, pair.first, pair.second) == sf::Socket::Done);
#if defined(_DEBUG_VERBOSE) && defined(_DEBUG)
				std::cout << "To:\t" + pair.first.toString() + ":" << pair.second << "\tSize: " << packet.getDataSize() << std::endl;
#endif
			}
			break;
		case JOIN:
			assert(socket.send(packet, serverIp, serverPort) == sf::Socket::Done);
#if defined(_DEBUG_VERBOSE) && defined(_DEBUG)
			std::cout << "To:\t" + serverIp.toString() + ":" << serverPort << "\tSize: " << packet.getDataSize() << std::endl;
#endif
			break;
		default:
			assert(false);
		}
		return true;
	}

	std::queue<sf::Packet> & UDPSocket::GetPacket()
	{
		std::vector<sf::Packet> vPackets;
		sf::Packet packet_in;
		sf::IpAddress ip_in;
		unsigned short port_in;
		while (socket.receive(packet_in, ip_in, port_in) == sf::Socket::Done) {
			qPackets.push(packet_in);
#if defined(_DEBUG_VERBOSE) && defined(_DEBUG)
			std::cout << "From:\t" + ip_in.toString() + ":" << port_in << "\tSize: " << packet_in.getDataSize() << std::endl;
#endif
		}

		return qPackets;
	}

	void UDPSocket::FlushPacketQueue()
	{
		while (!qPackets.empty()) {
			qPackets.pop();
		}
	}
}