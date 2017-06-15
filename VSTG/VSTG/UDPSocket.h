#pragma once

#include "SFML/Network.hpp"
#include <set>
#include <iostream>
#include <assert.h>

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
	std::vector<sf::Packet> GetPacket();
private:
	sf::UdpSocket socket;
	sf::IpAddress serverIp;
	unsigned short serverPort;
	std::set<std::pair<sf::IpAddress, unsigned short>> clinetInfo;
	Mode mode;
public:
	void ClearClientInfo() { clinetInfo.clear(); }
	void Unbind() { socket.unbind(); }
	size_t GetClinetNumb() const { return clinetInfo.size(); }
};