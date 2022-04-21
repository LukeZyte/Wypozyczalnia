#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Film {
	std::string title;
	std::string author;
	std::string genre;
	double price;
	bool available;
public:
	Film()
		: Film(false, "brak", "brak", "brak", 0.00) {}

	Film(bool _available, std::string _title, std::string _author, std::string _genre, double _price)
		: available(_available), title(_title), author(_author), genre(_genre), price(_price) {}

	void showAllData();
	std::string printToFile();
};