#include "klient.h"
#include "wypozyczalnia.h"
#include <iostream>

void Klient::showAllData() {
	std::string fixedGender;
	if (gender == "M") {
		fixedGender = "Mê¿czyzna";
	}
	else if (gender == "K") {
		fixedGender = "Kobieta";
	}
	std::cout << pesel << " " << name << " - " << surname << "\t" << fixedGender << "\t" << "wiek: " << age << "\t" << city << "\t";
}

std::string Klient::printToFile() {
	std::string stream = "";
	std::string fixedAge = std::to_string(age);
	std::string fixedNumOfFilms = std::to_string(numOfFilms);
	stream = fixedNumOfFilms + "\t" + pesel + "\t" + name + "\t" + surname + "\t" + gender + "\t" + fixedAge + "\t" + city + "\n";
	return stream;
}

void Klient::incNumOfFilms() {
	numOfFilms += 1;
}
void Klient::decNumOfFilms() {
	numOfFilms -= 1;
}

void Klient::setNumOfFilms(int _numOfFilms) {
	numOfFilms = _numOfFilms;
}