#include "WypozyczonyFilm.h"
#include <string>
#include <cmath>
#include <iomanip>

void WypozyczonyFilm::showAllData() {
	std::cout << "(id: " << id << ") " << title << " - " << author << "\t( " << genre << " )\t" << std::setprecision(2) << std::fixed << price << " PLN ";
}

std::string WypozyczonyFilm::printToFile() {
	std::string stream = id + "\t";
	stream = stream + "false\t";
	price = floor(price * 100.0) / 100.0;
	std::string fixedPrice = std::to_string(price);
	fixedPrice.resize(fixedPrice.size() - 4);

	stream = stream + title + "\t" + author + "\t" + genre + "\t" + fixedPrice + "\t" + borrowersPesel + "\t" + borrowsDate + "\n";
	return stream;
}