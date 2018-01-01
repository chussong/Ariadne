#ifndef INPUT_HPP
#define INPUT_HPP

#include <vector>
#include <string>
#include <fstream>

#include "types.hpp"

namespace Ariadne {

// raid site input from external files ----------------------------------------
std::vector<RaidSite> ReadFile(const Path& filename);
RaidSite ParseRaidSite(const std::string& line);
std::vector<std::string> GetFields(const std::string& line);
Time ParseExpirationTime(const std::string& stringForm);

} // namespace Ariadne

#endif
