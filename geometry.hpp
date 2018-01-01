#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <vector>
#include <cmath>

#include "matrix.hpp"
#include "types.hpp"

namespace Ariadne {

constexpr double earthRadius = 6371; // in km
constexpr double timePerKm = 180; // in seconds; 180 is 20 km/hr

// geometry -------------------------------------------------------------------
double DistanceBetween(const Coordinates& locA, const Coordinates& locB);
double DistanceBetween(const RaidSite& siteA,   const RaidSite& siteB  );
Duration TimeBetween(const Coordinates& locA, const Coordinates& locB);
Duration TimeBetween(const RaidSite& siteA,   const RaidSite& siteB  );
Matrix<double> DistanceMatrix(const std::vector<RaidSite>& sites);
std::vector<double> DistanceVector(const Coordinates& start, 
		const std::vector<RaidSite>& destinations);
Matrix<Duration> TimeMatrix(const std::vector<RaidSite>& sites);
std::vector<Duration> TimeVector(const Coordinates& start, 
		const std::vector<RaidSite>& destinations);

} // namespace Ariadne

#endif
