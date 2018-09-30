#include "stdafx.h"

#include "IO.h"

#include <fstream>
#include <conio.h>
#include <iostream>
#include <Windows.h>

/* Console, Windows only */
static HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // For use of SetConsoleTextAttribute()

														 /* Output */
void IO::Console::Print(const std::string& s, bool lineBreak) {
	if (lineBreak)
		std::cout << s << std::endl;
	else
		std::cout << s;
}
void IO::Console::Print(const std::string& s, int color, bool lineBreak) {
	// first hexs is for background and second hex is for text colors
	SetConsoleTextAttribute(console, color);
	Print(s, lineBreak);
	SetConsoleTextAttribute(console, IO::Console::WHITE);
}
void IO::Console::Print(const std::string& s, TextColor color, bool lineBreak) {
	Print(s, (int)color, lineBreak);
}

/* Input */
bool IO::Console::Get(int & response) {
	int input = 0;
	std::cin >> input;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return false;
	}
	response = input;
	return true;
}
bool IO::Console::Get(char & response) {
	char input = 0;
	std::cin >> input;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		return false;
	}
	response = input;
	return true;
}
bool IO::Console::Get(std::string & response) {
	response.clear();
	std::cin >> response;
	if (!response.empty())
		return true;
	else
		return false;
}

/* Misc */
void IO::Console::Clear() {
	// https://stackoverflow.com/questions/6486289/how-can-i-clear-console
	// code by user 'Cat Plus Plus'
	COORD topLeft = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
unsigned char IO::Console::WaitKey() {
	unsigned char in = _getch();
	if (in == 0 || in == 0xE0)
		in = _getch();
	return in;
}
unsigned char IO::Console::WaitKey(const std::string & s) {
	if (s.size() > 0)
		Print(s, IO::Console::DARK_GREY);
	else
		Print("Press any key to continue...", IO::Console::DARK_GREY);
	return WaitKey();
}
void IO::Console::ColorChart() {
	for (int i = 0; i < 256; i++) {
		Print(" [" + std::to_string(i) + "]->########123********abc||||||||ABC%%%%%%%%", i);
	}
}

/* File */
static std::ifstream reader;
static std::ofstream writer;

bool IO::File::Read(const std::string& fileName, std::vector<std::string>& input) {
	reader.open(fileName);
	if (!reader.is_open())
		return false;
	// Reading file
	std::string line;
	while (!reader.eof()) {
		std::getline(reader, line);
		input.push_back(line);
		line.clear();
	}
	reader.close();
	return true;
}
bool IO::File::Write(const std::string & path, const std::vector<std::string>& file, bool append) {
	writer.open(path);
	if (!writer.is_open()) {
		return false;
	}
	if (!append)	// Don't append -> clear file
		writer.clear();
	for (auto i = 0; i < file.size(); i++) {
		writer << file[i];
		if (i != file.size() - 1)
			writer << std::endl;
	}
	writer.close();
	return true;
}
bool IO::File::Write(const std::string& path, const std::string& message, bool append) {
	writer.open(path);
	if (!writer.is_open()) {
		return false;
	}
	if (!append)	// Don't append -> clear file
		writer.clear();
	writer << message << std::endl;
	writer.close();
	return true;
}