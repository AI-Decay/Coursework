#pragma once
#include <list>
#include <vector>
#include <stdexcept>
#include "ExceptionMessage.h"
#include "Place.h"

enum TicketType
{
	Luxury = 1, Coupe, Budget
};

class Railcar
{
private:
	unsigned int CountPlace;
	unsigned int Number;
	TicketType TypeRailcar;
	std::vector<Place> PlaceVector;
public:
	Railcar(TicketType type, unsigned int countplace, unsigned int number);
	~Railcar();
	void CreatePlase();
	void AddPlace(std::string name, unsigned int number);
	void DelPlace(unsigned int number);
	Railcar Serialization();
	unsigned int GetCountPlace() const;
	unsigned int GetNumber() const;
	TicketType GetTypeRailcar() const;
	std::vector<Place>& GetPlaceVector();
};