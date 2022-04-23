#pragma once
#include "film.h"
#include "klient.h"
#include <vector>

class Wypozyczalnia {
	std::vector <Film> filmy;
	std::vector <Klient> klienci;
public:
	void initializeData();
	void displayMenu();
	void loadFilms();
	void loadCustomers();
	void saveFilms();
	void saveCustomers();
	void displayFilmsMenu();
	void displayCustomersMenu();
	void displayPrintMenu();
	void displayAllFilms();
	void displayAllCustomers();
	void displayAddFilm();
	void removeFilm();
};