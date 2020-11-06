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
	"--i | --info"; 
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
		
	std::cout << "Free: " << main.free / 1000000000 << "-GB\n";
	std::cout << "Available: " <<  main.available / 1000000000 << "-GB";
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
	}
		
	std::cout << "\n";
	
	return 0;		
}
