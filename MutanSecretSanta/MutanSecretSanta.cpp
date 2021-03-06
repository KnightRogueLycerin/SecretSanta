#include "stdafx.h"

// For IO
#include "IO.h"
// Container
#include <vector>
// Shuffling
#include <algorithm>
// Randomizing
#include <time.h>

int main(void) {
	unsigned int saftey(250), count(0);
	const std::string rosterPath("_roster.txt"), outPath("_result.txt");
	std::vector<std::string> fileRoster, filePrevious, roster, result;
	std::vector<std::pair<std::string, std::string>> previous;

	// Setting up the roster
	if (!IO::File::Read(rosterPath, fileRoster)) {
		// Set upp a sample
		fileRoster = {
			"# as first symbol means the row will be ignored",
			"# Start of roster",
			"Person Perssonson",
			"Name MacNamly",
			"# This line is ignored",
			"Nick Ricards"
		};
		IO::File::Write(rosterPath, fileRoster, false);
		// "Could not find the _roster.txt!"
		// "Created a template, please edit it to suit your roster and start program again"
		IO::Console::Print(" Could not find the ", false);
		IO::Console::Print(" _roster.txt", IO::Console::RED, false);
		IO::Console::Print("!\n Created a template, please edit it to suit your roster and start program again");
		IO::Console::WaitKey("");
		return 0;
	}
	for (auto line : fileRoster) {
		if (line.front() != '#')
			roster.push_back(line);
	}
	fileRoster.clear();
	// "Loaded the _roster.txt file successfully!"
	IO::Console::Print(" Loaded the ", IO::Console::DARK_GREY, false);
	IO::Console::Print("_roster.txt", false);
	IO::Console::Print(" file ", IO::Console::DARK_GREY, false);
	IO::Console::Print("successfully", IO::Console::GREEN, false);
	IO::Console::Print("!\n\n ", false);
	
	// Reading previous results
	if (IO::File::Read(outPath, filePrevious)) {
		previous.clear();
		size_t pos = 0;
		std::string producer, consumer;
		for (auto line : filePrevious) {
			std::string temp = line;
			// Producer
			pos = temp.find('\t');
			producer = temp.substr(0, pos);
			temp.erase(0, pos + 1);
			// Omitting parsing
			pos = temp.find('\t');
			temp.erase(0, pos + 1);
			// Consumer
			consumer = temp;
			// Register
			previous.push_back(std::pair<std::string, std::string>(producer, consumer));
		}
	}
	filePrevious.clear();

	// Shuffling
	std::srand(time(0));	// Seeding randomness
	bool unique = (previous.empty()) ? true : false;
	while (!unique) {
		// Randomize
		std::random_shuffle(roster.begin(), roster.end());
		// Look for reapeats of prevoius
		unique = true;
		for (auto index = 0; index < roster.size(); index++) {
			for (auto pair : previous) {
				if (pair.first == roster[index]) {
					if ((index == 0 ? roster[roster.size() - 1] : roster[index - 1]) == pair.second)
						unique = false;
				}
			}
		}
		IO::Console::Print(".", IO::Console::DARK_GREY, false);
		
		// Sanity break
		if (++count >= saftey) {
			// "Could not creat a unique set which doesn't repeat previous results after $count$ attempts!"
			IO::Console::Print(" Could not create a ", false);
			IO::Console::Print("unique", IO::Console::RED, false);
			IO::Console::Print(" set which doesn't repeat previous results after ", false);
			IO::Console::Print(std::to_string(count) + " attempts", IO::Console::RED, false);
			IO::Console::Print("!\n");
			IO::Console::WaitKey("");
			return 0;
		}
	}
	IO::Console::Print("\n roster created\n", IO::Console::DARK_GREEN);

	// Output
	result.push_back("Doer\t->\tReceiver\n");
	std::string recipient;
	for (auto index = 0; index < roster.size(); index++) {
		recipient = (index == 0) ? roster[roster.size() - 1] : roster[index - 1];
		result.push_back(roster[index] + "\t->\t" + recipient);
	}
	IO::File::Write(outPath, result, false);
	for (auto line : result)
		IO::Console::Print(" " + line);
	
	// Wait
	IO::Console::Print("\n ", false);
	IO::Console::WaitKey("");

	// End program
	return 0;
}