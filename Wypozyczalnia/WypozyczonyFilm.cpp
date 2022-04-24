#include "WypozyczonyFilm.h"

void WypozyczonyFilm::showAllData() {
	std::cout << title << " - " << author << "\t( " << genre << " )\t" << std::setprecision(2) << std::fixed << price << " PLN | Wypo¿yczy³: " << borrowersPesel; // nieee to tak nie moze byc xd
}
