#include "wypozyczalnia.h"
#include "klient.h"
#include "film.h"
#include <iostream>
#include <string>
#include <fstream>

void Wypozyczalnia::loadFilms() {
	//Film film;
	std::fstream fileFilms("database/Filmy.txt");
	std::string title, author, genre, _price; 
	double price;
	if (fileFilms) {
		std::string wiersz;
		while (!fileFilms.eof()) {
			getline(fileFilms, title, '\t');
			//std::cout << title << " ";
			getline(fileFilms, author, '\t');
			//std::cout << author << " ";
			getline(fileFilms, genre, '\t');
			//std::cout << genre << " ";
			getline(fileFilms, _price, '\n');
			price = std::stod(_price);	// string to double
			//std::cout << price << std::endl;
			Film film(title, author, genre, price);
			Wypozyczalnia::filmy.push_back(film);
		}
	}
	fileFilms.close();
}

void Wypozyczalnia::showRandomFilm() {
	filmy.at(0).showData();
}

void Wypozyczalnia::displayMenu() {
	
	Wypozyczalnia::loadFilms();

	int action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	//system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW I AUDIOBOOKÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "G³ówny panel zadañ" << std::endl;
	std::cout << "\t1. Baza filmów" << std::endl;
	std::cout << "\t2. Baza klientów" << std::endl;
	std::cout << "\t3. Drukowanie" << std::endl;
	std::cout << std::endl << "\t0. Zamknij program" << std::endl << std::endl;
	std::cout << "WprowadŸ cyfrê interesuj¹cej Ciê czynnoœci, aby przejœæ dalej." << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;
	Wypozyczalnia::showRandomFilm();

	switch (action) {
	case 0: exit(0);
		break;
	case 1: Wypozyczalnia::displayFilmsMenu();
		break;
	case 2: Wypozyczalnia::displayCustomersMenu();
		break;
	case 3: Wypozyczalnia::displayPrintMenu();
		break;
	default: Wypozyczalnia::displayMenu();
	}
}

void Wypozyczalnia::displayFilmsMenu() {
	int action = NULL;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW I AUDIOBOOKÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "\t1. Wyœwietl bazê filmów" << std::endl;
	std::cout << "\t0. Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;

	switch (action) {
	case 1: Wypozyczalnia::displayAllFilms();
		break;
	}
}

void Wypozyczalnia::displayCustomersMenu() {

}

void Wypozyczalnia::displayPrintMenu() {
	int action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW I AUDIOBOOKÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Tutaj bedzie baza drukowania...";
}

void Wypozyczalnia::displayAllFilms() {

}