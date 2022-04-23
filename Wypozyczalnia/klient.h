#pragma once
#include <string>

class Klient {
	std::string pesel;
	std::string name;
	std::string surname;
	std::string gender;
	int age;
	std::string city;
public:
	Klient()
		: Klient("brak", "brak", "brak", "brak", NULL, "brak") {}

	Klient(std::string _pesel, std::string _name, std::string _surname, std::string _gender, int _age, std::string _city)
		: pesel(_pesel), name(_name), surname(_surname), gender(_gender), age(_age), city(_city) {}

	void showAllData();
	std::string printToFile();
};