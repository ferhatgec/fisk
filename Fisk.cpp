/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#include <iostream>
#include <filesystem>

#include <Colorized.hpp>

/* TODO:
	Disk Info without progress bars.
	Disk compare support.
	Flash drive support.
*/

void HelpFunction(char* argument) {
	std::cout << argument << " [argument]\n" << 
	"[argument]\n" << 
	"--i | --info\n" << "--p | --perms"; 
}

void CLIBar(long free, long available) {
	long data = free - available;

	unsigned q = 100 - data;
	
	for(unsigned var = 0; var < q; var++) {
		BOLD_LIGHT_GREEN_COLOR();
		std::cout << "#";
	}
	
	for(unsigned var = 0; var < 100 - q; var++) {
		BOLD_LIGHT_RED_COLOR();
		std::cout << "*";
	}
	
	RESETB();
}

void Detect(std::string path) {
	std::filesystem::space_info main = std::filesystem::space(path);

	std::cout << "Main Disk:\n";
	CLIBar(main.free / 1000000000, main.available / 1000000000);
}

void Info(std::string path) {	
	std::filesystem::space_info main = std::filesystem::space(path);

	if(path == "/")
		std::cout << "Main Disk:\n";
	else
		std::cout << "Path: " << path + "\n";
		
	std::cout << "Capacity: " << main.capacity / 1000000000 << "-GB\n";		
	std::cout << "Free: " << main.free / 1000000000 << "-GB\n";
	std::cout << "Available: " <<  main.available / 1000000000 << "-GB";
}

void Perms(std::filesystem::perms p) {
    std::cout << ((p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? "r" : "-")
              << ((p & std::filesystem::perms::owner_write) != std::filesystem::perms::none ? "w" : "-")
              << ((p & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ? "x" : "-")
              << ((p & std::filesystem::perms::group_read) != std::filesystem::perms::none ? "r" : "-")
              << ((p & std::filesystem::perms::group_write) != std::filesystem::perms::none ? "w" : "-")
              << ((p & std::filesystem::perms::group_exec) != std::filesystem::perms::none ? "x" : "-")
              << ((p & std::filesystem::perms::others_read) != std::filesystem::perms::none ? "r" : "-")
              << ((p & std::filesystem::perms::others_write) != std::filesystem::perms::none ? "w" : "-")
              << ((p & std::filesystem::perms::others_exec) != std::filesystem::perms::none ? "x" : "-");
}

void Permissions(std::string path) {	
	std::filesystem::space_info main = std::filesystem::space(path);

	if(path == "/") {
		std::cout << "Main Disk: ";
		Perms(std::filesystem::status("/").permissions());
	} else {
		std::cout << "Path: ";
		Perms(std::filesystem::status(path).permissions());
	}
}

int main(int argc, char** argv) {
	if(argc == 1) {
		Detect("/");		
		std::cout << "\n";
		return 0;
	}

	std::string argument(argv[1]);

	if(argument == "--h" || argument == "--help") {
		HelpFunction(argv[0]);
	} else if(argument == "--i" || argument == "--info") {
		if(argc == 2) 
			Info("/");
		else if(argc == 3) {
			std::string argument_path(argv[2]);
			Info(argument_path);		
		}
	} else if(argument == "--p" || argument == "--perms") {
		if(argc == 2)
			Permissions("/");
		else if(argc == 3) {
			std::string argument_path(argv[2]);
			Permissions(argument_path);
		}	
	}
		
	std::cout << "\n";
	
	return 0;		
}
