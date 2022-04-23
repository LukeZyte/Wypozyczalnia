#include "film.h"
#include <iostream>
#include <string>

void Film::showAllData() {
	std::cout << title << " - " << author << "\t( " << genre << " )\t" << std::setprecision(2) << std::fixed << price << " PLN";
}

std::string Film::printToFile() {
	std::string stream = "";
	if (available) {
		stream = "true\t";
	}
	else {
		stream = "false\t";
	}
	std::string fixedPrice = std::to_string(price);

	stream = stream + title + "\t" + author + "\t" + genre + "\t" + fixedPrice + "\n";
	return stream;
}