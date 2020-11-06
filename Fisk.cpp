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

void CLIBar(long free, long available) {
	long data = free - available;
	long cli = free / data;
	
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

int main(int argc, char** argv) {
	std::filesystem::space_info main = std::filesystem::space("/");

	CLIBar(main.free / 1000000000, main.available / 1000000000);
	
	std::cout << "\n";
}
