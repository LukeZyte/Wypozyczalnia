#include "wypozyczalnia.h"
#include "klient.h"
#include "film.h"
#include <iostream>
#include <string>
#include <fstream>

void Wypozyczalnia::initializeData() {
	Wypozyczalnia::loadFilms();
	Wypozyczalnia::loadCustomers();
	Wypozyczalnia::loadBorrowedFilms();
	Wypozyczalnia::displayMenu();
}

Klient Wypozyczalnia::searchCustomer(std::string pesel) {
	for (Klient customer : customers) {
		if (customer.getPesel() == pesel) {
			return customer;
		}
	}
	std::cout << "Nie znaleziono klienta !!!" << std::endl;
}

Film Wypozyczalnia::searchFilm(std::string id) {
	for (Film film : films) {
		if (film.getId() == id) {
			return film;
		}
	}
	std::cout << "Nie znalezniono filmu !!!" << std::endl;
}

void selectOption(std::string _action, void(*def), void(*a), void(*b), void(*c), void(*d), void(*e), void(*f), void(*g), void(*h), void(*i), void(*j)) {
	char action = _action[0];
	switch (action) {
	case 'q': if (&a) {
		&a;
	}
			else {
		&def;
	}
		break;
	case '1': &b;
		break;
	case '2': &c;
		break;
	case '3': &d;
		break;
	case '4': &e;
		break;
	case '5': &f;
		break;
	case '6': &g;
		break;
	case '7': &h;
		break;
	case '8': &i;
		break;
	case '9': &j;
		break;
	default: std::cout << "Proszê wprowadziæ poprawn¹ œcie¿kê!" << std::endl;
		break;
	}
}

void Wypozyczalnia::loadFilms() {
	std::fstream fileFilms("database/Filmy.txt");
	std::string id, title, author, genre, _price, _available;
	bool available;
	double price;
	films.clear();
	if (fileFilms) {
		while (!fileFilms.eof()) {
			getline(fileFilms, id, '\t');
			if (id != "") {
				getline(fileFilms, _available, '\t');
				if (_available == "true") {
					available = true;
				}
				else {
					available = false;
				}
				getline(fileFilms, title, '\t');
				getline(fileFilms, author, '\t');
				getline(fileFilms, genre, '\t');
				getline(fileFilms, _price, '\n');
				price = std::stod(_price);	// string to double
				Film film(id, available, title, author, genre, price);
				Wypozyczalnia::films.push_back(film);
			}
		}
	}
	fileFilms.close();
}

void Wypozyczalnia::saveFilms() {
	std::ofstream fileFilms("database/Filmy.txt");
	for (int i = 0; i < Wypozyczalnia::films.size(); i++) {
		fileFilms << Wypozyczalnia::films[i].printToFile();
	}
	fileFilms.close();
}

void Wypozyczalnia::loadCustomers() {
	std::fstream fileCustomers("database/Klienci.txt");
	std::string _haveFilms, pesel, name, surname, gender, _age, city;
	int age;
	bool haveFilms;
	customers.clear();
	if (fileCustomers) {
		while (!fileCustomers.eof()) {
			getline(fileCustomers, _haveFilms, '\t');
			if (_haveFilms != "") {
				if (_haveFilms == "true") {
					haveFilms = true;
				}
				else {
					haveFilms = false;
				}
				getline(fileCustomers, pesel, '\t');
				getline(fileCustomers, name, '\t');
				getline(fileCustomers, surname, '\t');
				getline(fileCustomers, gender, '\t');
				getline(fileCustomers, _age, '\t');
				age = std::stoi(_age);	// string to int
				getline(fileCustomers, city, '\n');
				Klient klient(haveFilms, pesel, name, surname, gender, age, city);
				Wypozyczalnia::customers.push_back(klient);
			}
		}
	}
	fileCustomers.close();
}

void Wypozyczalnia::saveCustomers() {
	std::ofstream fileCustomers("database/Klienci.txt");
	for (int i = 0; i < Wypozyczalnia::customers.size(); i++) {
		fileCustomers << Wypozyczalnia::customers[i].printToFile();
	}
	fileCustomers.close();
}

void Wypozyczalnia::loadBorrowedFilms() {
	std::fstream fileBorrowedFilms("database/WypozyczoneFilmy.txt");
	std::string id, title, author, genre, _price, available, pesel, borrowsDate;
	double price;
	borrowedFilms.clear();
	if (fileBorrowedFilms) {
		while (!fileBorrowedFilms.eof()) {
			getline(fileBorrowedFilms, id, '\t');
			if (id != "") {
				//getline(fileBorrowedFilms, id, '\t');
				getline(fileBorrowedFilms, available, '\t');
				getline(fileBorrowedFilms, title, '\t');
				getline(fileBorrowedFilms, author, '\t');
				getline(fileBorrowedFilms, genre, '\t');
				getline(fileBorrowedFilms, _price, '\t');
				price = std::stod(_price);	// string to double
				getline(fileBorrowedFilms, pesel, '\t');
				getline(fileBorrowedFilms, borrowsDate, '\n');
				WypozyczonyFilm wypozyczonyFilm(id, false, title, author, genre, price, pesel, borrowsDate);
				Wypozyczalnia::borrowedFilms.push_back(wypozyczonyFilm);
			}
		}
	}
	fileBorrowedFilms.close();
}

void Wypozyczalnia::saveBorrowedFilms() {
	std::ofstream fileBorrowedFilms("database/WypozyczoneFilmy.txt");
	for (int i = 0; i < Wypozyczalnia::borrowedFilms.size(); i++) {
		fileBorrowedFilms << Wypozyczalnia::borrowedFilms[i].printToFile();
	}
	fileBorrowedFilms.close();
}

void Wypozyczalnia::displayMenu() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "G³ówny panel zadañ" << std::endl;
	std::cout << "\t[ 1 ] Baza filmów" << std::endl;
	std::cout << "\t[ 2 ] Baza klientów" << std::endl;
	std::cout << "\t[ 3 ] Drukowanie" << std::endl;
	std::cout << "\t[ q ] Zamknij program" << std::endl << std::endl;
	std::cout << "WprowadŸ cyfrê interesuj¹cej Ciê czynnoœci, aby przejœæ dalej." << std::endl;
	std::cout << "PrzejdŸ do: ";
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
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Baza filmów" << std::endl;
	std::cout << "\t[ 1 ] Wyœwietl wszystkie filmy" << std::endl;
	std::cout << "\t[ 2 ] Wyœwietl wypo¿yczone filmy" << std::endl;
	std::cout << "\t[ 3 ] Wyœwietl dostêpne filmy" << std::endl;
	std::cout << "\t[ 4 ] Wypo¿ycz film" << std::endl;
	std::cout << "\t[ 5 ] Zwróæ film" << std::endl;
	std::cout << "\t[ 6 ] Dodaj film" << std::endl;
	std::cout << "\t[ 7 ] Usuñ film" << std::endl;
	std::cout << "\t[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayMenu();
		break;
	case '1': Wypozyczalnia::displayAllFilms();
		break;
	case '2': Wypozyczalnia::displayAllBorrowedFilms();
		break;
	case '3': Wypozyczalnia::displayAvailableFilms();
		break;
	case '4': Wypozyczalnia::displayBorrowFilm();
		break;
	case '5': Wypozyczalnia::returnFilm();
		break;
	case '6': Wypozyczalnia::displayAddFilm();
		break;
	case '7': Wypozyczalnia::removeFilm();
		break;
	}
}

void Wypozyczalnia::displayCustomersMenu() {
	char action = NULL;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Baza klientów" << std::endl;
	std::cout << "\t[ 1 ] Wyœwietl wszystkich klientów" << std::endl;
	std::cout << "\t[ 2 ] Wyœwietl klientów, którzy wypo¿yczyli film/filmy" << std::endl;
	std::cout << "\t[ 3 ] Dodaj nowego klienta" << std::endl;
	std::cout << "\t[ 4 ] Usuñ klienta z bazy" << std::endl;
	std::cout << "\t[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayMenu();
		break;
	case '1': Wypozyczalnia::displayAllCustomers();
		break;
	case '2': Wypozyczalnia::displayBorrowers();
		break;
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
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Tutaj bedzie baza drukowania...";
}

void Wypozyczalnia::displayAllFilms() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich filmów" << std::endl;
	
	for (int i = 0; i < films.size(); i++) {
		std::cout << "\t" << i+1 << ". ";
		films[i].showAllData();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
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
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich klientów" << std::endl;

	for (int i = 0; i < customers.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		customers[i].showAllData();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayCustomersMenu();
		break;
	default: Wypozyczalnia::displayAllCustomers();
	}
}

void Wypozyczalnia::displayBorrowers() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista klientów, którzy wypo¿yczyli jakiœ film / filmy" << std::endl;

	for (Klient customer : customers) {
		if (customer.getHaveFilms()) {
			customer.showAllData();
			std::cout << std::endl;
		}
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayCustomersMenu();
		break;
	default: Wypozyczalnia::displayBorrowers();
	}
}

void Wypozyczalnia::displayAvailableFilms() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich dostêpnych w magazynie filmów" << std::endl;
	int index = 0;
	for (int i = 0; i < films.size(); i++) {
		if (films[i].getAvailable()) {
			index++;
			std::cout << "\t" << index << ". ";
			films[i].showAllData();
			std::cout << std::endl;
		}
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayFilmsMenu();
		break;
	default: Wypozyczalnia::displayAvailableFilms();
	}
}

void Wypozyczalnia::displayAddFilm() {
	std::string id, title, author, genre;
	std::string _price;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Dodawanie filmu" << std::endl;
	std::cout << "[ q ] Anuluj wprowadzanie i wróæ" << std::endl << std::endl;
	std::cout << "\tWprowadŸ id filmu: ";
	std::getline(std::cin, id);
	std::getline(std::cin, id);
	if (title == "q") {
		displayFilmsMenu();
	}
	else {
		std::cout << "\tWprowadŸ tytu³ filmu: ";
		std::getline(std::cin, title);
		if (title == "q") {
			Wypozyczalnia::displayFilmsMenu();
		}
		else {
			std::cout << "\tWprowadŸ autora filmu: ";
			std::getline(std::cin, author);
			if (author == "q") {
				Wypozyczalnia::displayFilmsMenu();
			}
			else {
				std::cout << "\tWprowadŸ gatunek filmu: ";
				std::getline(std::cin, genre);
				if (genre == "q") {
					Wypozyczalnia::displayFilmsMenu();
				}
				else {
					std::cout << "\tWprowadŸ cenê filmu: ";
					std::cin >> _price;
					if (_price == "q") {
						Wypozyczalnia::displayFilmsMenu();
					}
					else {
						double price = std::stod(_price);
						Film film(id, true, title, author, genre, price);
						Wypozyczalnia::films.push_back(film);
						Wypozyczalnia::saveFilms();
						Wypozyczalnia::displayFilmsMenu();
					}
				}
			}
		}
	}
}

void Wypozyczalnia::displayAddCustomer() {
	std::string pesel, name, surname, gender, _age, city;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Dodawanie nowego klienta" << std::endl;
	std::cout << "[ q ] Anuluj wprowadzanie i wróæ" << std::endl << std::endl;
	std::cout << "\tWprowadŸ pesel klienta: ";
	std::getline(std::cin, pesel);
	std::getline(std::cin, pesel);
	if (pesel == "q") {
		Wypozyczalnia::displayCustomersMenu();
	}
	else {
		std::cout << "\tWprowadŸ imie klienta: ";
		std::getline(std::cin, name);
		if (name == "q") {
			Wypozyczalnia::displayCustomersMenu();
		}
		else {
			std::cout << "\tWprowadŸ nazwisko klienta: ";
			std::getline(std::cin, surname);
			if (surname == "q") {
				Wypozyczalnia::displayCustomersMenu();
			}
			else {
				std::cout << "\tWprowadŸ p³eæ klienta ( M / K ): ";
				std::getline(std::cin, gender);
				if (gender == "q") {
					Wypozyczalnia::displayCustomersMenu();
				}
				else {
					std::cout << "\tWprowadŸ wiek klienta: ";
					std::getline(std::cin, _age);
					int age = std::stoi(_age);
					if (_age == "q") {
						Wypozyczalnia::displayCustomersMenu();
					}
					else {
						std::cout << "\tWprowadŸ miasto, z którego pochodzi klient: ";
						std::getline(std::cin, city);
						if (city == "q") {
							Wypozyczalnia::displayCustomersMenu();
						}
						else {
							Klient klient(false, pesel, name, surname, gender, age, city);
							Wypozyczalnia::customers.push_back(klient);
							Wypozyczalnia::saveCustomers();
							Wypozyczalnia::displayCustomersMenu();
						}
					}
				}
			}
		}
	}
}

void Wypozyczalnia::displayAllBorrowedFilms() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich wypo¿yczonych filmów" << std::endl;

	for (int i = 0; i < borrowedFilms.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		borrowedFilms[i].showAllData();
		Klient actualCustomer = searchCustomer(borrowedFilms[i].getBorrowersPesel());
		std::cout << " | Wypo¿yczy³: " << actualCustomer.getName() << " " << actualCustomer.getSurname();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	std::cin >> action;

	switch (action) {
	case 'q': Wypozyczalnia::displayFilmsMenu();
		break;
	default: Wypozyczalnia::displayAllBorrowedFilms();
	}
}

void Wypozyczalnia::displayBorrowFilm() {
	std::string _number, pesel, selectedTitle, selectedAuthor;
	int number;
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Wypo¿ycz film" << std::endl;
	int index = 0;
	for (int i = 0; i < films.size(); i++) {
		if (films[i].getAvailable()) {
			index++;
			std::cout << "\t" << index << ". ";
			films[i].showAllData();
			std::cout << std::endl;
		}
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "Wybierz numer filmu, który chcesz wypo¿yczyæ: ";
	std::cin >> _number;
	number = std::stoi(_number);

	if (_number == "q") {
		Wypozyczalnia::displayFilmsMenu();
	}
	else if (number > 0 and number <= index) {
		//Film actualFilm;
		index = 0;
		for (int i = 0; i < films.size(); i++) {
			if (films[i].getAvailable()) {
				index++;
				if (index == number) {
					Film actualFilm = searchFilm(films[i].getId());
					selectedTitle = actualFilm.getTitle();
					selectedAuthor = actualFilm.getAuthor();
					break;
				}
			}
		}
		std::cout << std::endl;

		for (Klient customer : customers) {
			customer.showAllData();
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "WprowadŸ pesel osoby po¿yczaj¹cej: ";
		std::cin >> pesel;
		Klient actualCustomer = searchCustomer(pesel);
		
		if (actualCustomer.getPesel() == pesel) {
			std::cout << "Czy aby na pewno chcesz wypo¿yczyæ film: \"" << selectedTitle << "\" - " << selectedAuthor << " tej osobie: (" << actualCustomer.getPesel() << ") " << actualCustomer.getName() << " " << actualCustomer.getSurname() << "?" << std::endl;
			std::cout << "tak / nie ? ";
			std::string approve;
			std::cin >> approve;
			if (approve == "tak") {
				index = 0;
				for (int i = 0; i < films.size(); i++) {
					if (films[i].getAvailable()) {
						index++;
						if (index == number) {
							films[i].swapAvailable();
							WypozyczonyFilm newBorrowedFilm(films[i].getId(), films[i].getAvailable(), films[i].getTitle(), films[i].getAuthor(), films[i].getGenre(), films[i].getPrice(), actualCustomer.getPesel(), "10.10.1010");
							borrowedFilms.push_back(newBorrowedFilm);
							std::cout << "Wypo¿yczono wybrany film!" << std::endl;
							break;
						}
					}
				}
				for (int i = 0; i < customers.size(); i++) {
					if (customers[i].getPesel() == pesel && !customers[i].getHaveFilms()) {
						customers[i].swapHaveFilms();
					}
				}
			}
			else {
				displayBorrowFilm();
			}
		}
		else {
			std::cout << "WprowadŸ pesel pasujacy do któregoœ z klientów w bazie!" << std::endl;
			displayBorrowFilm();
		}
		system("PAUSE");
		saveCustomers();
		saveFilms();
		saveBorrowedFilms();
		displayFilmsMenu();
	}
	else {
		std::cout << "Podano nieprawid³owy numer filmu!" << std::endl;
		system("PAUSE");
		displayBorrowFilm();
	}
}

void Wypozyczalnia::returnFilm() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Zwróæ film" << std::endl;
	for (int i = 0; i < borrowedFilms.size(); i++) {
		if (!borrowedFilms[i].getAvailable()) {
			std::cout << i + 1 << ". ";
			borrowedFilms[i].showAllData();
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "Wybierz numer filmu, który chcesz zwróciæ: ";
	std::cin >> action;
	int number = action;
	// zmiana dostepnosci filmu
	for (int i = 0; i < films.size(); i++) {
		if (films[i].getId() == borrowedFilms[number - 1].getId()) {
			films[i].swapAvailable();
		}
	}
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i].getPesel() == borrowedFilms[number - 1].getBorrowersPesel()) {
			//
		}
	}
	// usuniecie filmu z vektora wypozyczonych filmow
	if (number > 0 and number <= borrowedFilms.size()) {
		borrowedFilms.erase(borrowedFilms.begin() + number - 1);
	}
	
	switch (action) {
	case 'q': Wypozyczalnia::displayFilmsMenu();
		break;
	default: Wypozyczalnia::returnFilm();
		break;
	}
}

void Wypozyczalnia::removeFilm() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie filmu" << std::endl;

	for (int i = 0; i < films.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		films[i].showAllData();
		std::cout << std::endl;
	}

	std::string _number;
	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << std::endl << "Wybierz numer filmu, który chcesz usun¹æ: ";
	std::cin >> _number;
	if (_number == "q") {
		Wypozyczalnia::displayFilmsMenu();
	}
	else {
		int number = std::stoi(_number);
		Wypozyczalnia::films.erase(films.begin() + number - 1);
		Wypozyczalnia::saveFilms();
		Wypozyczalnia::removeFilm();
	}
}

void Wypozyczalnia::removeCustomer() {
	char action = NULL;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie klienta z bazy" << std::endl;

	for (int i = 0; i < customers.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		customers[i].showAllData();
		std::cout << std::endl;
	}

	std::string _number;
	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << std::endl << "Wybierz numer klienta, którego chcesz usun¹æ z bazy: ";
	std::cin >> _number;
	if (_number == "q") {
		Wypozyczalnia::displayCustomersMenu();
	}
	else {
		int number = std::stoi(_number);
		Wypozyczalnia::customers.erase(customers.begin() + number - 1);
		Wypozyczalnia::saveCustomers();
		Wypozyczalnia::removeCustomer();
	}
}