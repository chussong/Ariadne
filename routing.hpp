#ifndef ROUTING_HPP
#define ROUTING_HPP

#include <vector>
#include <algorithm> // std::next_permutation

#include "matrix.hpp"
#include "types.hpp"
#include "geometry.hpp"

namespace Ariadne {

// these should be configurable; all Durations are in seconds
constexpr Duration timeAtRaid = Duration(480);

// route analysis -------------------------------------------------------------
std::vector<RaidSite> ShortestRoute(std::vector<RaidSite> sites,
		const Coordinates& currentLocation);
std::vector<RaidSite> FastestRoute(std::vector<RaidSite> sites,
		const Coordinates& currentLocation);
double RouteDistance(const std::vector<std::size_t>& route,
		const Matrix<double>& distanceMatrix, 
		const std::vector<double>& firstDistanceVector);
Duration RouteTime(const std::vector<std::size_t>& route,
		const Matrix<Duration>& timeMatrix, 
		const std::vector<Duration>& firstTimeVector,
		const std::vector<Time>& expirationTimes);

} // namespace Ariadne

#endif
