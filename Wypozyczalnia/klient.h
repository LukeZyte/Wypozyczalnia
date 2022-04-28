#pragma once
#include <string>

class Klient {
	bool haveFilms;
	std::string pesel;
	std::string name;
	std::string surname;
	std::string gender;
	int age;
	std::string city;
public:
	Klient()
		: Klient(false, "brak", "brak", "brak", "brak", NULL, "brak") {}

	Klient(bool _haveFilms, std::string _pesel, std::string _name, std::string _surname, std::string _gender, int _age, std::string _city) {
		haveFilms = _haveFilms;
		pesel = _pesel;
		name = _name;
		surname = _surname;
		gender = _gender;
		age = _age;
		city = _city;
	}

	void swapHaveFilms();
	void showAllData();
	std::string printToFile();
	bool getHaveFilms() { return haveFilms; }
	std::string getPesel() { return pesel; }
	std::string getName() { return name; }
	std::string getSurname() { return surname; }
};