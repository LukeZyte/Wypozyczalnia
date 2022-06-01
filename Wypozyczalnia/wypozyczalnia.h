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
	bool areOnlySpaces(std::string stream);
	bool isStringANumber(std::string stream);
	Klient searchCustomer(std::string pesel);
	Film searchFilm(std::string id);
	void initializeData();
	void displayMenu();
	void loadFilms();
	void loadCustomers();
	void loadBorrowedFilms();
	void saveFilms();
	void saveCustomers();
	void saveBorrowedFilms();
	bool checkSelection(char);
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
	std::string currentDate();
	void displayBorrowFilm();
	void displayReturnFilm();
	void displayRemoveFilm();
	void displayRemoveCustomer();
	void printAll();
	void printCustomers();
	void printFilms();
};