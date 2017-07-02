#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <SFML/System.hpp>

#include "Defines.h"

#define MAX_TEXT_NUM 2048

namespace CommResMeth {

	class __VSTG_API TextManager {
	private:
		TextManager();
	public:
		static sf::String getText(uint32_t id);
	private:
		std::wifstream csvfile;
		sf::String texts[MAX_TEXT_NUM];
		static TextManager m_instance;
	};
}
