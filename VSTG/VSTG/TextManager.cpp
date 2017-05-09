#include "TextManager.h"

TextManager::TextManager(const std::string & filepath)
{
	csvfile.open(filepath);
	std::string line;
	std::regex rgx("([^,]+),([^,]+)");
	std::smatch match;
	while (std::getline(csvfile, line)) {
		const std::string s(line);
		std::regex_search(s.begin(), s.end(), match, rgx);
		int idx = std::stoi(match[1]);
		std::string str = std::string(match[2]);
		texts[idx] = str;
	}
}
