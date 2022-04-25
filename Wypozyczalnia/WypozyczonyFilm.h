#pragma once
#include "Film.h"
#include <iostream>
#include <string>

class WypozyczonyFilm : public Film {
	std::string borrowersPesel;
	std::string borrowsDate;
public:
	WypozyczonyFilm(bool _available, std::string _title, std::string _author, std::string _genre, double _price, std::string _borrowersPesel, std::string _borrowsDate)
		: Film(_available, _title, _author, _genre, _price) {
		available = false;
		borrowersPesel = _borrowersPesel;
		borrowsDate = _borrowsDate;
	}
	std::string getBorrowersPesel() { return borrowersPesel; }
	void showAllData();
	std::string printToFile();
};