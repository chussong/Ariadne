#include "types.hpp"

namespace Ariadne {

std::ostream& operator<<(std::ostream& os, const Ariadne::Duration& dur) {
	return os << dur.count();
}

std::ostream& operator<<(std::ostream& os, const Ariadne::Time& time) {
	long count = time.time_since_epoch().count();
	typedef std::chrono::time_point<
		std::chrono::system_clock, std::chrono::duration<long>> IntegralTime;
	IntegralTime intTime = IntegralTime(std::chrono::duration<long>(count));
	time_t converted = std::chrono::system_clock::to_time_t(intTime);
	return os << std::put_time(std::localtime(&converted), "%R");
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coords) {
	return os << "{" << coords.y << ", " << coords.x << "}";
}

std::ostream& operator<<(std::ostream& os, const RaidSite& site) {
	return os << site.name << " " << site.location << " -- " << site.expiration;
}

} // namespace Ariadne
