#include "TextManager.h"

namespace CommResMeth {

	TextManager TextManager::m_instance;

	sf::String TextManager::getText(uint32_t id){ 
		return m_instance.texts[id % MAX_TEXT_NUM]; 
	}

	TextManager::TextManager()
	{
		csvfile.open("Resources/texts/en_us.csv");
		std::wstring line;
		std::wregex rgx(L"([^,]+),([^,]+)");
		std::wsmatch match;
		int i = 0;
		while (std::getline(csvfile, line)) {
			//		const std::wstring s(line);
			//		std::regex_search(s.begin(), s.end(), match, rgx);
			//		int idx = std::stoi(match[1]);
			//		std::wstring str = std::wstring(match[2]);
			//		texts[idx] = str;
			texts[i] = sf::String::fromUtf8(line.begin(), line.end());
			i++;
		}
	}
}