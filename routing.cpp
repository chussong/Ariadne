#include "routing.hpp"

namespace Ariadne {

// gives route through graph whose edges are space intervals between sites
std::vector<RaidSite> ShortestRoute(std::vector<RaidSite> sites,
		const Coordinates& currentLocation) {
	Matrix<double> distMat = DistanceMatrix(sites);
	std::vector<double> firstDistVec = DistanceVector(currentLocation, sites);
	std::vector<std::size_t> bestRoute(sites.size());
	for (std::size_t i = 0; i < bestRoute.size(); ++i) bestRoute[i] = i;
	double bestDistance = RouteDistance(bestRoute, distMat, firstDistVec);

	std::vector<std::size_t> route = bestRoute;
	while (std::next_permutation(route.begin(), route.end())) {
		double distance = RouteDistance(route, distMat, firstDistVec);
		if (distance < bestDistance) {
			bestDistance = distance;
			bestRoute = route;
		}
	}

	std::vector<RaidSite> output(bestRoute.size());
	for (std::size_t i = 0; i < bestRoute.size(); ++i) {
		output[i] = sites[bestRoute[i]];
	}
	return output;
}

// gives route through graph whose edges are time intervals between sites
std::vector<RaidSite> FastestRoute(std::vector<RaidSite> sites,
		const Coordinates& currentLocation) {
	Matrix<Duration> timeMat = TimeMatrix(sites);
	// std::cout << "timeMat: \n" << timeMat << std::endl;
	std::vector<Duration> firstTimeVec = TimeVector(currentLocation, sites);
	std::vector<Time> expTimes(sites.size());
	for (std::size_t i = 0; i < sites.size(); ++i) {
		expTimes[i] = sites[i].expiration;
	}

	std::vector<std::size_t> bestRoute(sites.size());
	for (std::size_t i = 0; i < bestRoute.size(); ++i) bestRoute[i] = i;
	Duration bestTime = RouteTime(bestRoute, timeMat, firstTimeVec, expTimes);

	std::vector<std::size_t> route = bestRoute;
	while (std::next_permutation(route.begin(), route.end())) {
		Duration routeTime = RouteTime(route, timeMat, firstTimeVec, expTimes);
		if (routeTime < bestTime) {
			bestTime = routeTime;
			bestRoute = route;
		}
	}

	if (bestTime == Duration::max()) {
		throw std::runtime_error("No valid routes for the given raids.");
	}

	std::vector<RaidSite> output(bestRoute.size());
	for (std::size_t i = 0; i < bestRoute.size(); ++i) {
		output[i] = sites[bestRoute[i]];
	}
	return output;
}

double RouteDistance(const std::vector<std::size_t>& route,
		const Matrix<double>& distanceMatrix, 
		const std::vector<double>& firstDistanceVector) {
	if (route.size() == 0 || distanceMatrix.rows() == 0 
			|| distanceMatrix.cols() == 0 || firstDistanceVector.size() == 0) {
		throw std::out_of_range("RouteDistance was fed empty container(s).");
	}
	double distance = firstDistanceVector[route[0]];
	for (std::size_t i = 0; i < route.size()-1; ++i) {
		distance += distanceMatrix(route[i], route[i+1]);
	}
	return distance;
}

Duration RouteTime(const std::vector<std::size_t>& route,
		const Matrix<Duration>& timeMatrix, 
		const std::vector<Duration>& firstTimeVector,
		const std::vector<Time>& expirationTimes) {
	if (route.size() == 0 || timeMatrix.rows() == 0 
			|| timeMatrix.cols() == 0 || firstTimeVector.size() == 0) {
		throw std::out_of_range("RouteDistance was fed empty container(s).");
	}
	Time startTime = Now();
	// std::cout << "Start time: " << startTime << std::endl;
	Duration totalTime = firstTimeVector[route[0]];
	// std::cout << "Raid at: " << startTime + totalTime << std::endl;
	for (std::size_t i = 0; i < route.size()-1; ++i) {
		totalTime += timeMatrix(route[i], route[i+1]);
		// std::cout << "Raid at: " << startTime + totalTime << std::endl;
		if (startTime + totalTime > expirationTimes[route[i+1]]) {
			return Duration::max();
		}
		totalTime += timeAtRaid;
	}
	return totalTime;
}

} // namespace Ariadne
