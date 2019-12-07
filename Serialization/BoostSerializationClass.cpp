#include "BoostSerializationClass.h"

PlaceSerialization::PlaceSerialization(Place obj)
	: NamePassenger(obj.GetNamePassenger()), PlaceNumber(obj.GetPlaceNumber()) {};

Place PlaceSerialization::Deserialization()
{
	return Place(PlaceNumber, NamePassenger);
}



RailcarSerialization::RailcarSerialization(Railcar obj)
	: TypeRailcar(obj.GetTypeRailcar()), CountPlace(obj.GetCountPlace()), Number(obj.GetNumber())
{
	for (int i = 0; i < CountPlace; i++)
	{
		PlaceVector.push_back(PlaceSerialization(obj.GetPlaceVector()[i].Serialization()));
	}
};

Railcar RailcarSerialization::Deserialization()
{
	Railcar temp(TypeRailcar, CountPlace, Number);
	for (int i = 0; i < CountPlace; i++)
	{
		temp.GetPlaceVector().push_back(PlaceVector[i].Deserialization());
	}
	return temp;
}


TrainSerialization::TrainSerialization(Train obj)
	: TrainName(obj.GetTrainName()), Destination(obj.GetDestination()), DeparturePoint(obj.GetDeparturePoint()),
	DateDeparture(obj.GetDateDeparture()), DateArrival(obj.GetDateArrival())
{
	for (int i = 0; i < obj.GetCarVector().size(); i++)
	{
		CarVector.push_back(RailcarSerialization(obj.GetCarVector()[i].Serialization()));
	}
};

Train TrainSerialization::Deserialization()
{
	Train temp(TrainName, Destination, DeparturePoint, DateDeparture, DateArrival);

	for (int i = 0; i < CarVector.size(); i++)
	{
		temp.GetCarVector().push_back(CarVector[i].Deserialization());
	}

	return temp;
}


RailSystemSerialization::RailSystemSerialization()
{
	std::map<std::string, Train> temp = RailSystem::Serialization();
	for (auto x : temp)
	{
		TrainMap.insert({ x.first, TrainSerialization(x.second) });
	}
}

std::map<std::string, Train> RailSystemSerialization::Deserialization()
{
	std::map<std::string, Train> temp;
	for (auto x : TrainMap)
	{
		temp.insert({ x.first, x.second.Deserialization() });
	}
	return temp;
}