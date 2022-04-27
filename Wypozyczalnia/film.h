#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Film {
protected:
	std::string id;
	std::string title;
	std::string author;
	std::string genre;
	double price;
	bool available;
public:
	Film()
		: Film("0", false, "brak", "brak", "brak", 0.00) {}

	Film(std::string _id, bool _available = false, std::string _title = "brak", std::string _author = "brak", std::string _genre = "brak", double _price = 0.00) {
		id = _id;
		available = _available;
		title = _title;
		author = _author;
		genre = _genre;
		price = _price;
		available = _available;
	}
	std::string getId() { return id; }
	std::string getTitle() { return title; }
	std::string getAuthor() { return author; }
	std::string getGenre() { return genre; }
	double getPrice() { return price; }
	bool getAvailable() { return available; }
	void showAllData();
	void swapAvailable();
	std::string printToFile();
};