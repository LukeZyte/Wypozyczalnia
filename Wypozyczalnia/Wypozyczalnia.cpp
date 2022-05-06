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
	default: std::cout << "Proszê wprowadziæ poprawn¹ œcie¿kê!" << std::endl;
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
		std::cout << "Wprowadzono nieoczekiwan¹ wartoœæ!" << std::endl;
		system("PAUSE");
		return false;
	}
}

void Wypozyczalnia::displayMenu() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	//std::string action = "1";
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
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Tutaj bedzie baza drukowania...";
}

void Wypozyczalnia::displayAllFilms() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
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
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista klientów, którzy wypo¿yczyli jakiœ film / filmy" << std::endl;

	int index = 0;
	for (Klient customer : customers) {
		if (customer.getNumOfFilms() > 0) {
			index++;
			std::cout << "\t" << index << ". ";
			customer.showAllData();
			std::cout << std::endl;
		}
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	
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
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Dodawanie filmu" << std::endl;
	std::cout << "[ q ] Anuluj wprowadzanie i wróæ" << std::endl << std::endl;

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
			std::cout << "Osi¹gniêto limit iloœci filmów w bazie danych! - Nie mo¿na dodaæ nowych filmów" << std::endl;
			system("PAUSE");
			displayFilmsMenu();
		}
	} while (duped);

	std::cout << "\tWprowadŸ tytu³ filmu: ";
	std::getline(std::cin, title);
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

void Wypozyczalnia::displayAddCustomer() {
	system("cls");
	std::string pesel, name, surname, gender, _age, city;
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
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Lista wszystkich wypo¿yczonych filmów" << std::endl;

	for (int i = 0; i < borrowedFilms.size(); i++) {
		std::cout << "\t" << i + 1 << ". ";
		borrowedFilms[i].showAllData();
		Klient actualCustomer = searchCustomer(borrowedFilms[i].getBorrowersPesel());
		std::cout << " | Wypo¿yczy³: " << actualCustomer.getName() << " " << actualCustomer.getSurname();
		std::cout << " - dnia: ";
		std::cout << borrowedFilms[i].getBorrowsDate();
		std::cout << std::endl;
	}

	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << "PrzejdŸ do: ";
	
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
	
	if (_number != "q" and isStringANumber(_number)) {
		number = std::stoi(_number);
	}
	else {
		std::cout << "Wprowadzono nieoczekiwan¹ wartoœæ!" << std::endl;
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
							std::string currentDate = Wypozyczalnia::currentDate();
							WypozyczonyFilm newBorrowedFilm(films[i].getId(), films[i].getAvailable(), films[i].getTitle(), films[i].getAuthor(), films[i].getGenre(), films[i].getPrice(), actualCustomer.getPesel(), currentDate);
							borrowedFilms.push_back(newBorrowedFilm);

							for (int i = 0; i < customers.size(); i++) {
								if (actualCustomer.getPesel() == customers[i].getPesel()) {
									customers[i].incNumOfFilms();
								}
							}

							std::cout << "Wypo¿yczono wybrany film!" << std::endl;
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

void Wypozyczalnia::displayReturnFilm() {
	std::string action;	// Zmienna wyboru czynnosci uzytkownika
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
	int number = 0;
	if (action != "q" and isStringANumber(action)) {
		number = std::stoi(action);
	}
	else {
		std::cout << "Wprowadzono b³êdn¹ wartoœæ!" << std::endl;
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
		std::cout << "Wprowadzono wartoœæ spoza listy!" << std::endl;
		system("PAUSE");
		Wypozyczalnia::displayReturnFilm();
		}
	}
}

void Wypozyczalnia::displayRemoveFilm() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie filmu" << std::endl;
	std::cout << "Je¿eli filmu nie ma na licie, to mo¿e znaczyæ, ¿e jest on aktualnie wypo¿yczony i nale¿y go najpierw zwróciæ." << std::endl;
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
	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << std::endl << "Wybierz numer filmu, który chcesz usun¹æ: ";
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
		std::cout << "Wprowadzono b³êdn¹ wartoœæ!" << std::endl;
		system("PAUSE");
		displayRemoveFilm();
	}
}

void Wypozyczalnia::displayRemoveCustomer() {
	char action;	// Zmienna wyboru czynnosci uzytkownika
	system("cls");
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << "-    WYPO¯YCZALNIA FILMÓW   -" << std::endl;
	std::cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << std::endl;
	std::cout << std::endl;
	std::cout << "Usuwanie klienta z bazy" << std::endl;
	std::cout << "Je¿eli szukanego klienta nie ma na liœcie, mo¿e to oznaczaæ, ¿e posiada on aktualnie wypo¿yczony film i nale¿y go najpierw zwróciæ." << std::endl;

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
	std::cout << std::endl << "[ q ] Wróæ" << std::endl;
	std::cout << std::endl << "Wybierz numer klienta, którego chcesz usun¹æ z bazy: ";
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
		std::cout << "Wprowadzono b³êdn¹ wartoœæ!" << std::endl;
		system("PAUSE");
		displayRemoveCustomer();
	}
}