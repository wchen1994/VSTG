#pragma once

#include "SFML/Network.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <assert.h>

//#define _DEBUG_VERBOSE

class UDPSocket {
public:
	enum Mode{HOST, JOIN, COUNT};
public:
	UDPSocket();
	bool Host(const unsigned short port);
	bool Join(std::string targetIp, const unsigned short targetPort, const unsigned short port);
	sf::Packet Synch(sf::Packet & packet_send);
	bool servWait();
	bool servTrial();
	bool cliTrial();
	bool SendPacket(sf::Packet & packet);
	std::queue<sf::Packet> & GetPacket();
	void FlushPacketQueue();
private:
	sf::UdpSocket socket;
	sf::IpAddress serverIp;
	unsigned short serverPort;
	std::vector<std::pair<sf::IpAddress, unsigned short>> clientInfo;
	Mode mode;
	std::queue<sf::Packet> qPackets;
public:
	void ClearClientInfo() { clientInfo.clear(); }
	void Unbind() { socket.unbind(); }
	size_t GetClinetNumb() const { return clientInfo.size(); }
	const auto GetClient() const { return clientInfo; }
};