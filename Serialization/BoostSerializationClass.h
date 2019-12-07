#pragma once
#include "..//Cursov/RailSystem.h"
#include "..//Cursov/Train.h"
#include "..//Cursov/Railcar.h"
#include "..//Cursov/Place.h"

class PlaceSerialization
{
public:
	PlaceSerialization() {};
	PlaceSerialization(Place obj);
	std::string NamePassenger{};
	int PlaceNumber{};

	Place Deserialization();
};

class RailcarSerialization
{
public:
	unsigned int CountPlace{};
	unsigned int Number{};
	TicketType TypeRailcar{};
	std::vector<PlaceSerialization> PlaceVector;

	RailcarSerialization() {};
	RailcarSerialization(Railcar obj);
	Railcar Deserialization();
};

class TrainSerialization
{
public:
	std::string TrainName{};
	std::string Destination{};
	std::string DeparturePoint{};
	std::vector<RailcarSerialization> CarVector{};
	std::string DateDeparture{};
	std::string DateArrival{};

	TrainSerialization() {};
	TrainSerialization(Train obj);
	Train Deserialization();
};

class RailSystemSerialization
{
public:
	std::map<std::string, TrainSerialization> TrainMap;

	RailSystemSerialization();
	std::map<std::string, Train> Deserialization();
};