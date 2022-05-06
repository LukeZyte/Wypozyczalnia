#define _CRT_SECURE_NO_WARNINGS	// wylacza blad spowodowany zabezpieczeniami

#include "wypozyczalnia.h"
#include "klient.h"
#include "film.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>

bool Wypozyczalnia::isStringANumber(std::string stream) {
	for (int i = 0; i < stream.size(); i++) {
		bool isCorrect = false;
		if (stream[i] == '0' or stream[i] == '1' or stream[i] == '2' or stream[i] == '3' or stream[i] == '4' or stream[i] == '5' or stream[i] == '6' or stream[i] == '7' or stream[i] == '8' or stream[i] == '9') {
			isCorrect = true;
		}
		if (!isCorrect) {
			return false;
		}
	}
	return true;
}

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
	system("PAUSE");
	displayFilmsMenu();
}

Film Wypozyczalnia::searchFilm(std::string id) {
	for (Film film : films) {
		if (film.getId() == id) {
			return film;
		}
	}
	std::cout << "Nie znalezniono filmu !!!" << std::endl;
	system("PAUSE");
	displayFilmsMenu();
}

/*
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
	default: std::cout << "Prosz� wprowadzi� poprawn� �cie�k�!" << std::endl;
		break;
	}
}
*/

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
	std::string _numOfFilms, pesel, name, surname, gender, _age, city;
	int age;
	int numOfFilms;
	customers.clear();
	if (fileCustomers) {
		while (!fileCustomers.eof()) {
			getline(fileCustomers, _numOfFilms, '\t');
			if (_numOfFilms != "") {
				numOfFilms = std::stoi(_numOfFilms);
				getline(fileCustomers, pesel, '\t');
				getline(fileCustomers, name, '\t');
				getline(fileCustomers, surname, '\t');
				getline(fileCustomers, gender, '\t');
				getline(fileCustomers, _age, '\t');
				age = std::stoi(_age);	// string to int
				getline(fileCustomers, city, '\n');
				Klient klient(numOfFilms, pesel, name, surname, gender, age, city);
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

bool Wypozyczalnia::checkSelection(char stream) {
	if (1) {
		return true;
	}
	else {
		std::cout << "Wprowadzono nieoczekiwan� warto��!" << std::endl;
		system("PAUSE");
		return false;
	}
}

void Wypozyczalnia::displayMenu() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	//std::string action = "1";
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

	//std::cin.clear();
	std::cin.get(action);
	if (checkSelection(action)) {
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
	else {
		displayMenu();
	}
}

void Wypozyczalnia::displayFilmsMenu() {
	char action;
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
	std::cout << "\t[ 5 ] Zwr�� film" << std::endl;
	std::cout << "\t[ 6 ] Dodaj film" << std::endl;
	std::cout << "\t[ 7 ] Usu� film" << std::endl;
	std::cout << "\t[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	
	std::cin.get(action);
	if (checkSelection(action)) {
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
		case '5': Wypozyczalnia::displayReturnFilm();
			break;
		case '6': Wypozyczalnia::displayAddFilm();
			break;
		case '7': Wypozyczalnia::displayRemoveFilm();
			break;
		default: Wypozyczalnia::displayFilmsMenu();
		}
	}
}

void Wypozyczalnia::displayCustomersMenu() {
	char action;
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

	std::cin.get(action);
	if (checkSelection(action)) {
		switch (action) {
		case 'q': Wypozyczalnia::displayMenu();
			break;
		case '1': Wypozyczalnia::displayAllCustomers();
			break;
		case '2': Wypozyczalnia::displayBorrowers();
			break;
		case '3': Wypozyczalnia::displayAddCustomer();
			break;
		case '4': Wypozyczalnia::displayRemoveCustomer();
			break;
		default: displayCustomersMenu();
		}
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
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich film�w" << std::endl;
	
	for (int i = 0; i < films.size(); i++) {
		std::cout << "\t" << i+1 << ". ";
		films[i].showAllData();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	
	std::cin.get(action);
	if (checkSelection(action)) {
		switch (action) {
		case 'q': Wypozyczalnia::displayFilmsMenu();
			break;
		default: Wypozyczalnia::displayAllFilms();
		}
	}
}

void Wypozyczalnia::displayAllCustomers() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich klient�w" << std::endl;

	for (int i = 0; i < customers.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		customers[i].showAllData();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	
	std::cin.get(action);
	if (checkSelection(action)) {
		switch (action) {
		case 'q': Wypozyczalnia::displayCustomersMenu();
			break;
		default: Wypozyczalnia::displayAllCustomers();
		}
	}
}

void Wypozyczalnia::displayBorrowers() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista klient�w, kt�rzy wypo�yczyli jaki� film / filmy" << std::endl;

	int index = 0;
	for (Klient customer : customers) {
		if (customer.getNumOfFilms() > 0) {
			index++;
			std::cout << "\t" << index << ". ";
			customer.showAllData();
			std::cout << std::endl;
		}
	}

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	
	std::cin.get(action);
	if (checkSelection(action)) {
		switch (action) {
		case 'q': Wypozyczalnia::displayCustomersMenu();
			break;
		default: Wypozyczalnia::displayBorrowers();
		}
	}
}

void Wypozyczalnia::displayAvailableFilms() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich dost�pnych w magazynie film�w" << std::endl;
	int index = 0;
	for (int i = 0; i < films.size(); i++) {
		if (films[i].getAvailable()) {
			index++;
			std::cout << "\t" << index << ". ";
			films[i].showAllData();
			std::cout << std::endl;
		}
	}

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	
	std::cin.get(action);
	if (checkSelection(action)) {
		switch (action) {
		case 'q': Wypozyczalnia::displayFilmsMenu();
			break;
		default: Wypozyczalnia::displayAvailableFilms();
		}
	}
}

void Wypozyczalnia::displayAddFilm() {
	system("cls");
	std::string id, title, author, genre;
	std::string _price;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Dodawanie filmu" << std::endl;
	std::cout << "[ q ] Anuluj wprowadzanie i wr��" << std::endl << std::endl;

	std::random_device r;
	std::default_random_engine randomNumber(r());
	std::uniform_int_distribution<int> uniform_dist(1, 10000);	// losowa liczba z zakresu
	int _id = uniform_dist(randomNumber);
	id = std::to_string(_id);

	bool duped = true;	// czy id to duplikat
	int maxIter = 0;	// zatrzymuje sprawdzanie 
	do {
		maxIter++;
		duped = false;
		for (Film film : films) {
			if (film.getId() == id) {
				std::random_device r;
				std::default_random_engine randomNumber(r());
				_id = uniform_dist(randomNumber);
				id = std::to_string(_id);
				duped = true;
			}
		}
		if (maxIter == 9999) {
			duped = false;
			std::cout << "Osi�gni�to limit ilo�ci film�w w bazie danych! - Nie mo�na doda� nowych film�w" << std::endl;
			system("PAUSE");
			displayFilmsMenu();
		}
	} while (duped);

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
					Film film(id, true, title, author, genre, price);
					Wypozyczalnia::films.push_back(film);
					Wypozyczalnia::saveFilms();
					Wypozyczalnia::displayFilmsMenu();
				}
			}
		}
	}
}

void Wypozyczalnia::displayAddCustomer() {
	system("cls");
	std::string pesel, name, surname, gender, _age, city;
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
							Klient klient(0, pesel, name, surname, gender, age, city);
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
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich wypo�yczonych film�w" << std::endl;

	for (int i = 0; i < borrowedFilms.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		borrowedFilms[i].showAllData();
		Klient actualCustomer = searchCustomer(borrowedFilms[i].getBorrowersPesel());
		std::cout << " | Wypo�yczy�: " << actualCustomer.getName() << " " << actualCustomer.getSurname();
		std::cout << " - dnia: ";
		std::cout << borrowedFilms[i].getBorrowsDate();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Przejd� do: ";
	
	std::cin.get(action);
	if (checkSelection(action)) {
		switch (action) {
		case 'q': Wypozyczalnia::displayFilmsMenu();
			break;
		default: Wypozyczalnia::displayAllBorrowedFilms();
		}
	}
}

std::string Wypozyczalnia::currentDate() {
	time_t t = time(NULL);
	tm* tPtr = localtime(&t);
	std::string today;
	if (tPtr->tm_mday < 10) {									// dzien miesiaca
		today = "0" + std::to_string(tPtr->tm_mday) + "-";
	}
	else {
		today = std::to_string(tPtr->tm_mday) + "-";
	}
	if (tPtr->tm_mon < 9) {										// miesiac
		today += "0" + std::to_string(tPtr->tm_mon + 1) + "-";
	}
	else {
		today += std::to_string(tPtr->tm_mon + 1) + "-";
	}
	today += std::to_string(tPtr->tm_year + 1900);				// rok
	return today;
}

void Wypozyczalnia::displayBorrowFilm() {
	system("cls");
	std::string _number, pesel, selectedTitle, selectedAuthor;
	int number;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Wypo�ycz film" << std::endl;
	int index = 0;
	for (int i = 0; i < films.size(); i++) {
		if (films[i].getAvailable()) {
			index++;
			std::cout << "\t" << index << ". ";
			films[i].showAllData();
			std::cout << std::endl;
		}
	}

	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << "Wybierz numer filmu, kt�ry chcesz wypo�yczy�: ";
	std::cin >> _number;
	
	if (_number != "q" and isStringANumber(_number)) {
		number = std::stoi(_number);
	}
	else {
		std::cout << "Wprowadzono nieoczekiwan� warto��!" << std::endl;
		system("PAUSE");
		displayBorrowFilm();
	}
	if (_number == "q") {
		Wypozyczalnia::displayFilmsMenu();
	}
	else if (number > 0 and number <= index) {
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
			std::cout << "\t";
			customer.showAllData();
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "Wprowad� pesel osoby po�yczaj�cej: ";
		std::cin >> pesel;
		Klient actualCustomer = searchCustomer(pesel);
		
		if (actualCustomer.getPesel() == pesel) {
			std::cout << "Czy aby na pewno chcesz wypo�yczy� film: \"" << selectedTitle << "\" - " << selectedAuthor << " tej osobie: (" << actualCustomer.getPesel() << ") " << actualCustomer.getName() << " " << actualCustomer.getSurname() << "?" << std::endl;
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
							std::string currentDate = Wypozyczalnia::currentDate();
							WypozyczonyFilm newBorrowedFilm(films[i].getId(), films[i].getAvailable(), films[i].getTitle(), films[i].getAuthor(), films[i].getGenre(), films[i].getPrice(), actualCustomer.getPesel(), currentDate);
							borrowedFilms.push_back(newBorrowedFilm);

							for (int i = 0; i < customers.size(); i++) {
								if (actualCustomer.getPesel() == customers[i].getPesel()) {
									customers[i].incNumOfFilms();
								}
							}

							std::cout << "Wypo�yczono wybrany film!" << std::endl;
							break;
						}
					}
				}
			}
			else {
				displayBorrowFilm();
			}
		}
		else {
			std::cout << "Wprowad� pesel pasujacy do kt�rego� z klient�w w bazie!" << std::endl;
			displayBorrowFilm();
		}
		system("PAUSE");
		saveCustomers();
		saveFilms();
		saveBorrowedFilms();
		displayFilmsMenu();
	}
	else {
		std::cout << "Podano nieprawid�owy numer filmu!" << std::endl;
		system("PAUSE");
		displayBorrowFilm();
	}
}

void Wypozyczalnia::displayReturnFilm() {
	std::string action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Zwr�� film" << std::endl;
	for (int i = 0; i < borrowedFilms.size(); i++) {
		if (!borrowedFilms[i].getAvailable()) {
			std::cout << i + 1 << ". ";
			borrowedFilms[i].showAllData();
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "Wybierz numer filmu, kt�ry chcesz zwr�ci�: ";

	std::cin >> action;
	int number = 0;
	if (action != "q" and isStringANumber(action)) {
		number = std::stoi(action);
	}
	else {
		std::cout << "Wprowadzono b��dn� warto��!" << std::endl;
		system("PAUSE");
	}
	if (number > 0 and number <= borrowedFilms.size()) {
		// zmiana dostepnosci filmu
		for (int i = 0; i < films.size(); i++) {
			if (films[i].getId() == borrowedFilms[number - 1].getId()) {
				films[i].swapAvailable();
			}
		}
		// dekrementacja numOfFilms klienta
		for (int i = 0; i < customers.size(); i++) {
			if (customers[i].getPesel() == borrowedFilms[number - 1].getBorrowersPesel()) {
				customers[i].decNumOfFilms();
			}
		}
		// usuniecie filmu z vektora wypozyczonych filmow
		if (number > 0 and number <= borrowedFilms.size()) {
			borrowedFilms.erase(borrowedFilms.begin() + number - 1);
		}

		saveBorrowedFilms();
		saveFilms();
		saveCustomers();
	}
	
	switch (action[0]) {
	case 'q': Wypozyczalnia::displayFilmsMenu();
		break;
	default: {
		std::cout << "Wprowadzono warto�� spoza listy!" << std::endl;
		system("PAUSE");
		Wypozyczalnia::displayReturnFilm();
		}
	}
}

void Wypozyczalnia::displayRemoveFilm() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie filmu" << std::endl;
	std::cout << "Je�eli filmu nie ma na licie, to mo�e znaczy�, �e jest on aktualnie wypo�yczony i nale�y go najpierw zwr�ci�." << std::endl;
	int index = 0;
	for (int i = 0; i < films.size(); i++) {
		if (films[i].getAvailable()) {
			index++;
			std::cout << "\t" << index << ". ";
			films[i].showAllData();
			std::cout << std::endl;
		}
	}

	std::string _number;
	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << std::endl << "Wybierz numer filmu, kt�ry chcesz usun��: ";
	std::cin >> _number;
	if (_number == "q") {
		Wypozyczalnia::displayFilmsMenu();
	}
	else if (isStringANumber(_number)) {
		int number = std::stoi(_number);
		int indexAll = 0;
		int indexAvailable = 0;
		for (int i = 0; i < films.size(); i++) {
			indexAll++;
			if (films[i].getAvailable()) {
				indexAvailable++;
				if (indexAvailable == number) {
					Wypozyczalnia::films.erase(films.begin() + indexAll - 1);
				}
			}
		}
		Wypozyczalnia::saveFilms();
		Wypozyczalnia::displayRemoveFilm();
	}
	else {
		std::cout << "Wprowadzono b��dn� warto��!" << std::endl;
		system("PAUSE");
		displayRemoveFilm();
	}
}

void Wypozyczalnia::displayRemoveCustomer() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO�YCZALNIA FILM�W   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie klienta z bazy" << std::endl;
	std::cout << "Je�eli szukanego klienta nie ma na li�cie, mo�e to oznacza�, �e posiada on aktualnie wypo�yczony film i nale�y go najpierw zwr�ci�." << std::endl;

	int index = 0;
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i].getNumOfFilms() == 0) {
			index++;
			std::cout << "\t" << index << ". ";
			customers[i].showAllData();
			std::cout << std::endl;
		}
	}

	std::string _number;
	std::cout << std::endl << "[ q ] Wr��" << std::endl;
	std::cout << std::endl << "Wybierz numer klienta, kt�rego chcesz usun�� z bazy: ";
	std::cin >> _number;
	if (_number == "q") {
		Wypozyczalnia::displayCustomersMenu();
	}
	else if (isStringANumber(_number)) {
		int number = std::stoi(_number);
		int indexAll = 0;
		int indexAvailable = 0;
		for (int i = 0; i < customers.size(); i++) {
			indexAll++;
			if (customers[i].getNumOfFilms() == 0) {
				indexAvailable++;
				if (indexAvailable == number) {
					Wypozyczalnia::customers.erase(customers.begin() + indexAll - 1);
				}
			}
		}
		Wypozyczalnia::saveCustomers();
		Wypozyczalnia::displayRemoveCustomer();
	}
	else {
		std::cout << "Wprowadzono b��dn� warto��!" << std::endl;
		system("PAUSE");
		displayRemoveCustomer();
	}
}