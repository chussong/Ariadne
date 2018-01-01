#ifndef TYPES_HPP
#define TYPES_HPP

#include <chrono>
#include <ctime>
//#include <filesystem>
#include <iostream>
#include <iomanip>

#include <boost/filesystem.hpp>

namespace Ariadne {

// this is necessary until filesystem is no longer "experimental"
//namespace FileSystem = std::filesystem;
namespace FileSystem = boost::filesystem;

typedef std::chrono::duration<double> Duration; // this is in seconds
typedef std::chrono::time_point<std::chrono::system_clock, Duration> Time;
typedef FileSystem::path Path;

const Duration twelveHours(43200);

// these are coordinates in decimal degrees; x is longitude, y is latitude
struct Coordinates {
	double x;
	double y;
};

struct RaidSite {
	std::string name;
	Coordinates location;
	Time expiration;
};

std::ostream& operator<<(std::ostream& os, const Ariadne::Duration& dur);
std::ostream& operator<<(std::ostream& os, const Ariadne::Time& time);
std::ostream& operator<<(std::ostream& os, const Coordinates& coords);
std::ostream& operator<<(std::ostream& os, const RaidSite& site);

inline Time Now() {
	return std::chrono::system_clock::now();
}

// should give the start of the current day in *local time*
inline Time Today() {
	typedef std::chrono::time_point<
		std::chrono::system_clock, std::chrono::duration<long>> IntegralTime;

	Time output = Now();
	long count = output.time_since_epoch().count();
	IntegralTime intTime = IntegralTime(std::chrono::duration<long>(count));
	time_t converted = std::chrono::system_clock::to_time_t(intTime);
	std::tm* localTime = std::localtime(&converted);
	output -= Duration(3600*localTime->tm_hour);
	output -= Duration(60*localTime->tm_min);
	output -= Duration(localTime->tm_sec);
	return output;
}

} // namespace Ariadne

#endif
