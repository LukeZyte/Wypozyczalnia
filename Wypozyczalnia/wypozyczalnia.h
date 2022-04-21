#pragma once
#include "film.h"
#include "klient.h"
#include <vector>

class Wypozyczalnia {
	std::vector <Film> filmy;
	std::vector <Klient> klienci;
public:
	void displayMenu();
	void loadFilms();
	void loadCustomers();
	void saveFilms();
	void displayFilmsMenu();
	void displayCustomersMenu();
	void displayPrintMenu();
	void displayAllFilms();
	void displayAddFilm();
};