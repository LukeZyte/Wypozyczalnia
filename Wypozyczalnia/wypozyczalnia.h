#pragma once
#include "film.h"
#include "klient.h"
#include "WypozyczonyFilm.h"
#include <vector>

class Wypozyczalnia {
	std::vector <Film> films;
	std::vector <Klient> customers;
	std::vector <WypozyczonyFilm> borrowerdFilms;
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
	void displayAddCustomer();
	void removeFilm();
	void removeCustomer();
};