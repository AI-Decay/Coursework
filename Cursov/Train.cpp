#include "Train.h"

Train::Train(std::string name, std::string dest, std::string depart, std::string dated, std::string datea)
	: TrainName(name), Destination(dest), DeparturePoint(depart), DateDeparture(dated), DateArrival(datea) {};

Train::~Train() {};

std::string Train::GetDateDeparture() 
{
	return DateDeparture;
}

std::string Train::GetTrainName() 
{
	return TrainName;
}

std::string Train::GetDestination() 
{
	return Destination;
}

std::string Train::GetDeparturePoint() 
{
	return DeparturePoint;
}

std::string Train::GetDateArrival() 
{
	return DateArrival;
}

std::vector<Railcar>& Train::GetCarVector()
{
	return CarVector;
}

void Train::AddRailcar(TicketType type, unsigned int countplace)
{
	CarVector.push_back(Railcar(type, countplace, CarVector.size() + 1));
	CarVector.back().CreatePlase();
}

//ex
void Train::DelRailcar(unsigned int position)
{
	position--;
	if (position >= CarVector.size())
		throw std::out_of_range(Exception::RailcarNotFound);
	for (int i = 0; i < CarVector[position].GetPlaceVector().size(); i++)
	{
		if(CarVector[position].GetPlaceVector()[i].GetNamePassenger() != " ")
			throw std::exception(Exception::RailcarIsOccupy.c_str());
	}
		CarVector.erase(CarVector.begin() + position);
}

//ex
void Train::AddPlaceRailcar(unsigned int index, std::string name, unsigned int number)
{
	if (index > CarVector.size())
		throw std::out_of_range(Exception::RailcarNotFound);
	else
		 CarVector[index-1].AddPlace(name, number);
}

//ex
void Train::DelPlaceRailcar(unsigned int indexRailcar, unsigned int numberPlace)
{
	if (indexRailcar > CarVector.size())
		throw std::out_of_range(Exception::RailcarNotFound);
	else
		 CarVector[indexRailcar-1].DelPlace(numberPlace);
}

Train Train::Serialization()
{
	return *this;
}
