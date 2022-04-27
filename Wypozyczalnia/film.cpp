#include "film.h"
#include <iostream>
#include <string>

void Film::showAllData() {
	std::cout << "(id: " << id << ") " << title << " - " << author << "\t( " << genre << " )\t" << std::setprecision(2) << std::fixed << price << " PLN";
}

std::string Film::printToFile() {
	std::string stream = "";
	stream = id + "\t";
	if (available) {
		stream = stream + "true\t";
	}
	else {
		stream = stream + "false\t";
	}
	std::string fixedPrice = std::to_string(price);

	stream = stream + title + "\t" + author + "\t" + genre + "\t" + fixedPrice + "\n";
	return stream;
}

void Film::swapAvailable() {
	available = !available;
}