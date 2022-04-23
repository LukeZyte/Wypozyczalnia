#include "wypozyczalnia.h"
#include "klient.h"
#include "film.h"
#include <iostream>
#include <string>
#include <fstream>

void Wypozyczalnia::initializeData() {
	Wypozyczalnia::loadFilms();
	Wypozyczalnia::loadCustomers();
	Wypozyczalnia::displayMenu();
}

void Wypozyczalnia::loadFilms() {
	std::fstream fileFilms("database/Filmy.txt");
	std::string title, author, genre, _price, available; 
	double price;
	filmy.clear();
	if (fileFilms) {
		while (!fileFilms.eof()) {
			getline(fileFilms, available, '\t');
			getline(fileFilms, title, '\t');
			getline(fileFilms, author, '\t');
			getline(fileFilms, genre, '\t');
			getline(fileFilms, _price, '\n');
			price = std::stod(_price);	// string to double
			Film film(true, title, author, genre, price);
			Wypozyczalnia::filmy.push_back(film);
		}
	}
	filmy.pop_back();	// usuwa ostatni film z vectora, gdyz ostatni rekord sie dublowal.
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
	klienci.clear();
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
	klienci.pop_back();
	fileCustomers.close();
}

void Wypozyczalnia::saveCustomers() {
	std::ofstream fileCustomers("database/Klienci.txt");
	for (int i = 0; i < Wypozyczalnia::klienci.size(); i++) {
		fileCustomers << Wypozyczalnia::klienci[i].printToFile();
	}
	fileCustomers.close();
}

void Wypozyczalnia::displayMenu() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "G��wny panel zada�" << std::endl;
	std::cout << "\t[ 1 ] Baza film�w" << std::endl;
	std::cout << "\t[ 2 ] Baza klient�w" << std::endl;
	std::cout << "\t[ 3 ] Drukowanie" << std::endl;
	std::cout << "\t[ q ] Zamknij program" << std::endl << std::endl;
	std::cout << "Wprowad� cyfr� interesuj�cej Ci� czynno�ci, aby przej�� dalej." << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

	switch (action) {
	case 'q': exit(0);
		break;
	case '1': Wypozyczalnia::displayFilmsMenu();
		break;
	case '2': Wypozyczalnia::displayCustomersMenu();
		break;
	case '3': Wypozyczalnia::displayPrintMenu();
		break;
	default: Wypozyczalnia::displayMenu();
	}
}

void Wypozyczalnia::displayFilmsMenu() {
	char action = NULL;
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
	std::cout << "\t[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayMenu();
		break;
	case '1': Wypozyczalnia::displayAllFilms();
		break;
	case '5': Wypozyczalnia::displayAddFilm();
		break;
	case '6': Wypozyczalnia::removeFilm();
		break;
	}
}

void Wypozyczalnia::displayCustomersMenu() {
	char action = NULL;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Baza klient�w" << std::endl;
	std::cout << "\t[ 1 ] Wy�wietl wszystkich klient�w" << std::endl;
	std::cout << "\t[ 2 ] Wy�wietl klient�w, kt�rzy wypo�yczyli film/filmy" << std::endl;
	std::cout << "\t[ 3 ] Dodaj nowego klienta" << std::endl;
	std::cout << "\t[ 4 ] Usu� klienta z bazy" << std::endl;
	std::cout << "\t[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayMenu();
		break;
	case '1': Wypozyczalnia::displayAllCustomers();
		break;
	//case '2': Wypozyczalnia::displayAddFilm();
	//	break;
	case '3': Wypozyczalnia::displayAddCustomer();
		break;
	case '4': Wypozyczalnia::removeCustomer();
		break;
	}
}

void Wypozyczalnia::displayPrintMenu() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Tutaj bedzie baza drukowania...";
}

void Wypozyczalnia::displayAllFilms() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
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

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayFilmsMenu();
		break;
	default: Wypozyczalnia::displayAllFilms();
	}
}

void Wypozyczalnia::displayAllCustomers() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich klient�w" << std::endl;

	for (int i = 0; i < klienci.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		klienci[i].showAllData();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayCustomersMenu();
		break;
	default: Wypozyczalnia::displayAllCustomers();
	}
}

void Wypozyczalnia::displayAddFilm() {
	std::string title, author, genre;
	std::string _price;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Dodawanie filmu" << std::endl;
	std::cout << "[ q ] Anuluj wprowadzanie i wr��" << std::endl << std::endl;
	std::cout << "\tWprowad� tytu� filmu: ";
	std::getline(std::cin, title);
	std::getline(std::cin, title);
	if (title == "q") {
		Wypozyczalnia::displayFilmsMenu();
	}
	else {
		std::cout << "\tWprowad� autora filmu: ";
		std::getline(std::cin, author);
		if (author == "q") {
			Wypozyczalnia::displayFilmsMenu();
		}
		else {
			std::cout << "\tWprowad� gatunek filmu: ";
			std::getline(std::cin, genre);
			if (genre == "q") {
				Wypozyczalnia::displayFilmsMenu();
			}
			else {
				std::cout << "\tWprowad� cen� filmu: ";
				std::cin >> _price;
				if (_price == "q") {
					Wypozyczalnia::displayFilmsMenu();
				}
				else {
					double price = std::stod(_price);
					Film film(true, title, author, genre, price);
					Wypozyczalnia::filmy.push_back(film);
					Wypozyczalnia::saveFilms();
					Wypozyczalnia::displayFilmsMenu();
				}
			}
		}
	}
}

void Wypozyczalnia::displayAddCustomer() {
	std::string pesel, name, surname, gender, _age, city;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Dodawanie nowego klienta" << std::endl;
	std::cout << "[ q ] Anuluj wprowadzanie i wr��" << std::endl << std::endl;
	std::cout << "\tWprowad� pesel klienta: ";
	std::getline(std::cin, pesel);
	std::getline(std::cin, pesel);
	if (pesel == "q") {
		Wypozyczalnia::displayCustomersMenu();
	}
	else {
		std::cout << "\tWprowad� imie klienta: ";
		std::getline(std::cin, name);
		if (name == "q") {
			Wypozyczalnia::displayCustomersMenu();
		}
		else {
			std::cout << "\tWprowad� nazwisko klienta: ";
			std::getline(std::cin, surname);
			if (surname == "q") {
				Wypozyczalnia::displayCustomersMenu();
			}
			else {
				std::cout << "\tWprowad� p�e� klienta ( M / K ): ";
				std::getline(std::cin, gender);
				if (gender == "q") {
					Wypozyczalnia::displayCustomersMenu();
				}
				else {
					std::cout << "\tWprowad� wiek klienta: ";
					std::getline(std::cin, _age);
					int age = std::stoi(_age);
					if (_age == "q") {
						Wypozyczalnia::displayCustomersMenu();
					}
					else {
						std::cout << "\tWprowad� miasto, z kt�rego pochodzi klient: ";
						std::getline(std::cin, city);
						if (city == "q") {
							Wypozyczalnia::displayCustomersMenu();
						}
						else {
							Klient klient(pesel, name, surname, gender, age, city);
							Wypozyczalnia::klienci.push_back(klient);
							Wypozyczalnia::saveCustomers();
							Wypozyczalnia::displayCustomersMenu();
						}
					}
				}
			}
		}
	}
}

void Wypozyczalnia::removeFilm() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie filmu" << std::endl;

	for (int i = 0; i < filmy.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		filmy[i].showAllData();
		std::cout << std::endl;
	}

	std::string _number;
	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << std::endl << "Wybierz numer filmu, kt�ry chcesz usun��: ";
	std::cin >> _number;
	if (_number == "q") {
		Wypozyczalnia::displayFilmsMenu();
	}
	else {
		int number = std::stoi(_number);
		Wypozyczalnia::filmy.erase(filmy.begin() + number - 1);
		Wypozyczalnia::saveFilms();
		Wypozyczalnia::removeFilm();
	}
}

void Wypozyczalnia::removeCustomer() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie klienta z bazy" << std::endl;

	for (int i = 0; i < klienci.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		klienci[i].showAllData();
		std::cout << std::endl;
	}

	std::string _number;
	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << std::endl << "Wybierz numer klienta, kt�rego chcesz usun�� z bazy: ";
	std::cin >> _number;
	if (_number == "q") {
		Wypozyczalnia::displayCustomersMenu();
	}
	else {
		int number = std::stoi(_number);
		Wypozyczalnia::klienci.erase(klienci.begin() + number - 1);
		Wypozyczalnia::saveCustomers();
		Wypozyczalnia::removeCustomer();
	}
}