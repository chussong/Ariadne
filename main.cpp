#include "main.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error: input the name of the file containing the "
			<< "raids to be routed." << std::endl;
		return EXIT_FAILURE;
	}
	std::vector<std::string> args;
	for (int i = 1; i < argc; ++i) {
		args.emplace_back(argv[i]);
	}
	Ariadne::Path filePath = Ariadne::FileSystem::current_path() / args[0];
	std::vector<Ariadne::RaidSite> sites = Ariadne::ReadFile(filePath);
	std::vector<Ariadne::RaidSite> bestRoute = Ariadne::FastestRoute(
			sites, sites[0].location );
	std::cout << "Route:\n";
	for (const auto& site : bestRoute) {
		std::cout << site << std::endl;
	}
	return EXIT_SUCCESS;
	// options = ParseOptions 
}
