#include "Place.h"

Place::Place(int number, std::string name)
	: NamePassenger(name), PlaceNumber(number) {};

Place::~Place() {};

std::string Place::GetNamePassenger()
{
	return NamePassenger;
}

int Place::GetPlaceNumber()
{
	return PlaceNumber;
}

Place Place::Serialization()
{
	return *this;
}

void Place::SetNamePassenger(std::string name)
{
	this->NamePassenger = name;
}
