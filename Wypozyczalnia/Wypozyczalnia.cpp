#include "wypozyczalnia.h"
#include "klient.h"
#include "film.h"
#include <iostream>
#include <string>
#include <fstream>

void Wypozyczalnia::loadFilms() {
	std::fstream fileFilms("database/Filmy.txt");
	std::string title, author, genre, _price, available; 
	double price;
	if (fileFilms) {
		while (!fileFilms.eof()) {
			getline(fileFilms, available, '\t');
			getline(fileFilms, title, '\t');
			//std::cout << title << " ";
			getline(fileFilms, author, '\t');
			//std::cout << author << " ";
			getline(fileFilms, genre, '\t');
			//std::cout << genre << " ";
			getline(fileFilms, _price, '\n');
			price = std::stod(_price);	// string to double
			//std::cout << price << std::endl;
			Film film(true, title, author, genre, price);
			Wypozyczalnia::filmy.push_back(film);
		}
	}
	fileFilms.close();
}

void Wypozyczalnia::saveFilms() {
	std::ofstream fileFilms("database/Filmy.txt");
	for (int i = 0; i < Wypozyczalnia::filmy.size(); i++) {
		fileFilms << Wypozyczalnia::filmy[i].printToFile();
	}
	fileFilms.close();
}

void Wypozyczalnia::loadCustomers() {
	std::fstream fileCustomers("database/Klienci.txt");
	std::string pesel, name, surname, gender, _age, city;
	int age;
	if (fileCustomers) {
		while (!fileCustomers.eof()) {
			getline(fileCustomers, pesel, '\t');
			getline(fileCustomers, name, '\t');
			getline(fileCustomers, surname, '\t');
			getline(fileCustomers, gender, '\t');
			getline(fileCustomers, _age, '\t');
			age = std::stoi(_age);	// string to int
			getline(fileCustomers, city, '\n');
			Klient klient(pesel, name, surname, gender, age, city);
			Wypozyczalnia::klienci.push_back(klient);
		}
	}
	fileCustomers.close();
}

void Wypozyczalnia::displayMenu() {
	
	Wypozyczalnia::loadFilms();
	Wypozyczalnia::loadCustomers();

	int action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "G��wny panel zada�" << std::endl;
	std::cout << "\t[ 1 ] Baza film�w" << std::endl;
	std::cout << "\t[ 2 ] Baza klient�w" << std::endl;
	std::cout << "\t[ 3 ] Drukowanie" << std::endl;
	std::cout << "\t[ 0 ] Zamknij program" << std::endl << std::endl;
	std::cout << "Wprowad� cyfr� interesuj�cej Ci� czynno�ci, aby przej�� dalej." << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

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
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Baza film�w" << std::endl;
	std::cout << "\t[ 1 ] Wy�wietl wszystkie filmy" << std::endl;
	std::cout << "\t[ 2 ] Wy�wietl wypo�yczone filmy" << std::endl;
	std::cout << "\t[ 3 ] Wy�wietl dost�pne filmy" << std::endl;
	std::cout << "\t[ 4 ] Wypo�ycz film" << std::endl;
	std::cout << "\t[ 5 ] Dodaj film" << std::endl;
	std::cout << "\t[ 6 ] Usu� film" << std::endl;
	std::cout << "\t[ 0 ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

	switch (action) {
	case 0: Wypozyczalnia::displayMenu();
		break;
	case 1: Wypozyczalnia::displayAllFilms();
		break;
	case 5: Wypozyczalnia::displayAddFilm();
		break;
	}
}

void Wypozyczalnia::displayCustomersMenu() {

}

void Wypozyczalnia::displayPrintMenu() {
	int action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Tutaj bedzie baza drukowania...";
}

void Wypozyczalnia::displayAllFilms() {
	int action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich film�w" << std::endl;
	
	for (int i = 0; i < filmy.size(); i++) {
		std::cout << "\t" << i+1 << ". ";
		filmy[i].showAllData();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ 0 ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

	switch (action) {
	case 0: Wypozyczalnia::displayFilmsMenu();
		break;
	default: Wypozyczalnia::displayAllFilms();
	}
}

void Wypozyczalnia::displayAddFilm() {
	std::string title, author, genre;
	double price;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Dodawanie filmu" << std::endl;
	std::cout << "[ 0 ] Anuluj wprowadzanie i wr��" << std::endl << std::endl;
	std::cout << "\tWprowad� tytu� filmu: ";
	std::getline(std::cin, title);
	std::getline(std::cin, title);
	if (title == "0") {
		Wypozyczalnia::displayFilmsMenu();
	}
	else {
		std::cout << "\tWprowad� autora filmu: ";
		std::getline(std::cin, author);
		if (author == "0") {
			Wypozyczalnia::displayFilmsMenu();
		}
		else {
			std::cout << "\tWprowad� gatunek filmu: ";
			std::getline(std::cin, genre);
			if (genre == "0") {
				Wypozyczalnia::displayFilmsMenu();
			}
			else {
				std::cout << "\tWprowad� cen� filmu: ";
				std::cin >> price;
				if (price == 0) {
					Wypozyczalnia::displayFilmsMenu();
				}
				else {
					Film film(true, title, author, genre, price);
					Wypozyczalnia::filmy.push_back(film);
					Wypozyczalnia::saveFilms();
					Wypozyczalnia::displayFilmsMenu();
				}
			}
		}
	}
}