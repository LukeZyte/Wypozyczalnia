#pragma once
#include "film.h"
#include <string>
#include <vector>

class Klient {
	int numOfFilms;
	std::string pesel;
	std::string name;
	std::string surname;
	std::string gender;
	int age;
	std::string city;
public:
	Klient()
		: Klient(0, "brak", "brak", "brak", "brak", NULL, "brak") {}

	Klient(int _numOfFilms, std::string _pesel, std::string _name, std::string _surname, std::string _gender, int _age, std::string _city) {
		numOfFilms = _numOfFilms;
		pesel = _pesel;
		name = _name;
		surname = _surname;
		gender = _gender;
		age = _age;
		city = _city;
	}

	void showAllData();
	std::string printToFile();
	int getNumOfFilms() { return numOfFilms; }
	std::string getPesel() { return pesel; }
	std::string getName() { return name; }
	std::string getSurname() { return surname; }
	std::string getGender() { return gender; }
	int getAge() { return age; }
	std::string getCity() { return city; }
	void setNumOfFilms(int _numOfFilms);
	void incNumOfFilms();
	void decNumOfFilms();
};