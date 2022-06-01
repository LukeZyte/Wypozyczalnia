#include "film.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

void Film::showAllData() {
	std::cout << "(id: " << id << ")\t " << title << " - " << author << "\t( " << genre << " )\t" << std::setprecision(2) << std::fixed << price << " PLN";
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
	price = floor(price * 100.0) / 100.0;
	std::string fixedPrice = std::to_string(price);
	fixedPrice = fixedPrice.substr(0, fixedPrice.size() - 4);

	stream = stream + title + "\t" + author + "\t" + genre + "\t" + fixedPrice + "\n";
	return stream;
}

void Film::swapAvailable() {
	available = !available;
}