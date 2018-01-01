#include "input.hpp"

namespace Ariadne {

std::vector<RaidSite> ReadFile(const Path& filename) {
	std::ifstream inStream(filename.native());
	std::string line;
	std::vector<RaidSite> output;
	while (inStream.good()) {
		std::getline(inStream, line);
		if (line.empty()) continue;
		output.push_back(ParseRaidSite(line));
	}
	return output;
}

RaidSite ParseRaidSite(const std::string& line) {
	std::vector<std::string> fields = GetFields(line);
	if (fields.size() != 4) {
		throw std::invalid_argument("Invalid input to ParseRaidSite.");
	}
	RaidSite output;
	output.name = fields[0];
	// remember: the latitude is listed first in standard coordinates
	output.location.y = std::stod(fields[1]);
	output.location.x = std::stod(fields[2]);
	output.expiration = ParseExpirationTime(fields[3]);
	return output;
}

std::vector<std::string> GetFields(const std::string& line) {
	// std::cout << "GetFields on \"" << line << "\"" << std::endl;
	std::vector<std::string> output;
	std::size_t commaLeft = -1;
	std::size_t commaRight = -1;
	for (int field = 0; field < 4; ++field) {
		commaRight = line.find(',', commaLeft + 1);
		output.push_back(line.substr(commaLeft+1, commaRight-commaLeft));
		commaLeft = commaRight;
		if (field < 3 && commaLeft == std::string::npos) {
			throw std::invalid_argument("GetFields could not identify 4 fields.");
		}
	}
	return output;
}

Time ParseExpirationTime(const std::string& stringForm) {
	Time expTime = Today();
	std::size_t colonPos = stringForm.find(':');
	expTime += Duration(3600 * std::stod(stringForm.substr(0, colonPos)));
	expTime += Duration(60 * std::stod(stringForm.substr(colonPos+1, std::string::npos)));
	// std::cout << "expTime imported: " << stringForm << " -> " << expTime 
		// << " (Today() = " << Today() << ")." << std::endl;
	if (expTime < Now()) {
		// probably need to switch AM -> PM
		expTime += twelveHours;
		if (expTime < Now()) {
			// the time must actually be for tomorrow
			expTime += twelveHours;
		}
	}
	return expTime;
}

} // namespace Ariadne
