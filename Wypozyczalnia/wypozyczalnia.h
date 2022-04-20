#pragma once
#include "film.h"
#include <vector>

class Wypozyczalnia {
	std::vector <Film> filmy;
public:
	void displayMenu();
	void loadFilms();
	//void saveFilms();
	void displayFilmsMenu();
	void displayCustomersMenu();
	void displayPrintMenu();
	void displayAllFilms();
	void showRandomFilm();
};