#include "geometry.hpp"

namespace Ariadne {

// geometry -------------------------------------------------------------------

// returns small-angle-approximate distance between locA and locB in km
double DistanceBetween(const Coordinates& locA, const Coordinates& locB) {
	double latA = locA.y*M_PI/180;
	double latB = locB.y*M_PI/180;
	double lonA = locA.x*M_PI/180;
	double lonB = locB.x*M_PI/180;
	double latDiff = latB - latA;
	double lonDiff = lonB - lonA;

	double a = std::sin(latDiff)*std::sin(latDiff) +
		std::cos(latA) * std::cos(latB) * std::sin(lonDiff)*std::sin(lonDiff);
	double c = std::atan2(std::sqrt(a), std::sqrt(1-a));
	// std::cout << "Distance between " << locA << " and " << locB << ": "
		// << earthRadius * c << "km." << std::endl;
	return earthRadius * c;
}

double DistanceBetween(const RaidSite& siteA,   const RaidSite& siteB  ) {
	return DistanceBetween(siteA.location, siteB.location);
}

Duration TimeBetween(const Coordinates& locA, const Coordinates& locB) {
	return Duration(timePerKm * DistanceBetween(locA, locB));
}

Duration TimeBetween(const RaidSite& siteA, const RaidSite& siteB) {
	return TimeBetween(siteA.location, siteB.location);
}

Matrix<double> DistanceMatrix(const std::vector<RaidSite>& sites) {
	Matrix<double> output(sites.size(), sites.size());
	for (std::size_t row = 0; row < output.rows(); ++row) {
		output(row, row) = 0;
		for (std::size_t col = row + 1; col < output.cols(); ++col) {
			output(row, col) = DistanceBetween(sites[row], sites[col]);
			output(col, row) = output(row, col);
		}
	}
	return output;
}

std::vector<double> DistanceVector(const Coordinates& start, 
		const std::vector<RaidSite>& destinations) {
	std::vector<double> output(destinations.size());
	for (std::size_t i = 0; i < destinations.size(); ++i) {
		output[i] = DistanceBetween(start, destinations[i].location);
	}
	return output;
}

Matrix<Duration> TimeMatrix(const std::vector<RaidSite>& sites) {
	Matrix<Duration> output(sites.size(), sites.size());
	for (std::size_t row = 0; row < output.rows(); ++row) {
		output(row, row) = Duration(0);
		for (std::size_t col = row + 1; col < output.cols(); ++col) {
			output(row, col) = TimeBetween(sites[row], sites[col]);
			output(col, row) = output(row, col);
		}
	}
	return output;
}

std::vector<Duration> TimeVector(const Coordinates& start, 
		const std::vector<RaidSite>& destinations) {
	std::vector<Duration> output(destinations.size());
	for (std::size_t i = 0; i < destinations.size(); ++i) {
		output[i] = TimeBetween(start, destinations[i].location);
	}
	return output;
}

} // namespace Ariadne
