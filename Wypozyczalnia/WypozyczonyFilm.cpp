#include "WypozyczonyFilm.h"

void WypozyczonyFilm::showAllData() {
	std::cout << title << " - " << author << "\t( " << genre << " )\t" << std::setprecision(2) << std::fixed << price << " PLN | Wypożyczył: " << borrowersPesel; // nieee to tak nie moze byc xd
}
