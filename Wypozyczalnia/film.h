#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Film {
protected:
	std::string title;
	std::string author;
	std::string genre;
	double price;
	bool available;
public:
	Film()
		: Film(false, "brak", "brak", "brak", 0.00) {}

	Film(bool _available = false, std::string _title = "brak", std::string _author = "brak", std::string _genre = "brak", double _price = 0.00) {
		available = _available;
		title = _title;
		author = _author;
		genre = _genre;
		price = _price;
		available = _available;
	}

	void showAllData();
	std::string printToFile();
};