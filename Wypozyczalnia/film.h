#pragma once
#include <string>

class Film {
	std::string title;
	std::string author;
	std::string genre;
	double price;
public:
	Film()
		: Film("brak", "brak", "brak", 0) {}

	Film(std::string _title, std::string _author, std::string _genre, double _price)
		: title(_title), author(_author), genre(_genre), price(_price) {}

	void showData();
};