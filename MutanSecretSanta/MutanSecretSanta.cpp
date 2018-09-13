#include "stdafx.h"

// For IO
#include <iostream>
#include <fstream>
#include <string>
// Container
#include <vector>
// Shuffling
#include <algorithm>
// Randomizing
#include <time.h>

int main(void) {
	// Setting up the roster
	std::vector<std::string> roster; std::string input = "";
	std::ifstream inFile; inFile.open("MutantRoster.txt"); 
	if (!inFile.is_open()) {	// Deafult setup
		roster = { "Aldon", "Gertrud", "Kwarg", "Japp", "Squid", "Twix" };
		std::ofstream outFile; outFile.open("MutantRoster.txt"); outFile.clear();
		outFile << "# the '#' symbol means the row will be ignored\n# Start of roster";
		for (auto s : roster) {
			outFile << s + "\n";
		}
		outFile << "# end of roster";
		outFile.close();
		
		std::cout << "Roster created\n\n";
	}
	else {	// Reading in roster from file
		while (!inFile.eof()) {
			std::getline(inFile, input);
			if (input.front() != '#') {
				roster.push_back(input);
			}
			input.clear();
		}

		std::cout << "Roster loaded\n\n";
	}
	// Shuffle
	std::srand(time(0));	// Seeding randomness
	std::random_shuffle(roster.begin(), roster.end());
	// Setting up file
	std::ofstream outFile; outFile.open("SecretMutant.txt"); outFile.clear();
	if (!outFile.is_open()) {
		std::cout << "Error: Could not open file!\n";
		std::getchar();
	}
	// Output
	outFile << "Doer	-> Receiver\n-------------------\n";
	std::cout << "Doer	-> Receiver\n-------------------\n";
	for (unsigned int index = 0; index < roster.size(); index++) {
		if (index == 0) {	// First entry with special rules
			outFile << roster[index] + "	-> " + roster[roster.size() - 1] + "\n";
			std::cout << roster[index] + "	-> " + roster[roster.size() - 1] + "\n";
		}
		else {			// Other entries
			outFile << roster[index] + "	-> " + roster[index - 1] + "\n";
			std::cout << roster[index] + "	-> " + roster[index - 1] + "\n";
		}
	}
	// Closing file
	outFile.close();
	// Wait
	std::getchar();
	// End program
	return 0;
}