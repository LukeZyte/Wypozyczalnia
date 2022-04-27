#include "WypozyczonyFilm.h"

void WypozyczonyFilm::showAllData() {
	std::cout << "(id: " << id << ") " << title << " - " << author << "\t( " << genre << " )\t" << std::setprecision(2) << std::fixed << price << " PLN ";
}

std::string WypozyczonyFilm::printToFile() {
	std::string stream = id + "\t";
	stream = "false\t";
	std::string fixedPrice = std::to_string(price);

	stream = stream + title + "\t" + author + "\t" + genre + "\t" + fixedPrice + "\t" + borrowersPesel + "\t" + borrowsDate + "\n";
	return stream;
}