#pragma once

#include <SFML/Network.hpp>
#include <queue>
#include <vector>
#include <iostream>
#include <assert.h>

#include "Defines.h"
//#define _DEBUG_VERBOSE

namespace CommResMeth {

	class __VSTG_API UDPSocket {
	public:
		enum Mode { HOST, JOIN, OFFLINE };
		enum class PacketType : int { ADD, REMOVE, SIGNAL, SIGNAL_SIZE, CHANGE, ADD_T, CHANGE_T, CHANGE_POS, CHANGE_HP, COUNT };
		static constexpr unsigned short DEFAULT_HOST_PORT = 55009;
		static constexpr unsigned short DEFAULT_CLIENT_PORT = 55010;
	public:
		bool Host(const unsigned short port);
		bool Join(std::string targetIp, const unsigned short targetPort, const unsigned short port);
		bool Synch();
		bool servWait();
		bool servTrial();
		bool cliTrial();
		bool SendPacket(sf::Packet & packet);
		std::queue<sf::Packet> & GetPacket();
		void FlushPacketQueue();
		bool isClient() { return mode == Mode::JOIN; }
		bool isHost() { return mode == Mode::HOST; }
	private:
		sf::UdpSocket socket;
		sf::IpAddress serverIp;
		unsigned short serverPort;
		std::vector<std::pair<sf::IpAddress, unsigned short>> clientInfo;
		Mode mode;
		std::queue<sf::Packet> qPackets;
	public:
		UDPSocket();
		void ClearClientInfo() { clientInfo.clear(); }
		void Unbind() { socket.unbind(); }
		size_t GetClinetNumb() const { return clientInfo.size(); }
		const auto GetClient() const { return clientInfo; }
		const Mode getMode() const { return mode; }
		void setMode(const Mode m) { mode = m; }
	};
}