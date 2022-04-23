#include "klient.h"
#include <iostream>

void Klient::showAllData() {
	std::string fixedGender;
	if (gender == "M") {
		fixedGender = "Mê¿czyzna";
	}
	else if (gender == "K") {
		fixedGender = "Kobieta";
	}
	std::cout << pesel << " " << name << " - " << surname << "\t" << fixedGender << "\t" << "wiek: " << age << "\t" << city;
}

std::string Klient::printToFile() {
	std::string stream = "";
	std::string fixedAge = std::to_string(age);
	stream = pesel + "\t" + name + "\t" + surname + "\t" + gender + "\t" + fixedAge + "\t" + city + "\n";
	return stream;
}