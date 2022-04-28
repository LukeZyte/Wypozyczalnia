#pragma once
#include "film.h"
#include "klient.h"
#include "WypozyczonyFilm.h"
#include <vector>

class Wypozyczalnia {
	std::vector <Film> films;
	std::vector <Klient> customers;
	std::vector <WypozyczonyFilm> borrowedFilms;
public:
	Klient searchCustomer(std::string pesel);
	Film searchFilm(std::string id);
	void initializeData();
	void selectOption(std::string _action, void(*def), void(*a), void(*b), void(*c), void(*d), void(*e), void(*f), void(*g), void(*h), void(*i), void(*j));
	void displayMenu();
	void loadFilms();
	void loadCustomers();
	void loadBorrowedFilms();
	void saveFilms();
	void saveCustomers();
	void saveBorrowedFilms();
	void displayFilmsMenu();
	void displayCustomersMenu();
	void displayPrintMenu();
	void displayAllFilms();
	void displayAllCustomers();
	void displayBorrowers();
	void displayAvailableFilms();
	void displayAllBorrowedFilms();
	void displayAddFilm();
	void displayAddCustomer();
	void displayBorrowFilm();
	void removeFilm();
	void removeCustomer();
};