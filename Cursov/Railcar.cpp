#include "Railcar.h"

Railcar::Railcar(TicketType type, unsigned int countplace, unsigned int number)
	: TypeRailcar(type), CountPlace(countplace), Number(number) {};

Railcar::~Railcar() {};

//ex
void Railcar::AddPlace(std::string name, unsigned int number)
{
	if (number > PlaceVector.size())
		throw std::out_of_range(Exception::PlaceNotFound);

	if (PlaceVector[number - 1].GetNamePassenger() != " ")
		throw std::exception(Exception::PlaceIsOccupy.c_str());

	PlaceVector[number - 1] = Place(number, name);
}
//ex
void Railcar::DelPlace(unsigned int number)
{
	if (number > PlaceVector.size())
		throw std::out_of_range(Exception::PlaceNotFound);
	else
		PlaceVector[number - 1].SetNamePassenger(" ");
}

void Railcar::CreatePlase()
{
	for (unsigned int i = 1; i <= CountPlace; i++)
	{
		PlaceVector.push_back(Place(i, " "));
	}
}

Railcar Railcar::Serialization()
{
	return *this;
}

unsigned int Railcar::GetCountPlace() const
{
	return CountPlace;
}

unsigned int Railcar::GetNumber() const
{
	return Number;
}

TicketType Railcar::GetTypeRailcar() const
{
	return TypeRailcar;
}

std::vector<Place>& Railcar::GetPlaceVector()
{
	return PlaceVector;
}