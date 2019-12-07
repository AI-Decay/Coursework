#pragma once
namespace Serialize
{
	void Save();
	void Load();
}

/*
#include <vector>
#include <list>
#include <map>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#pragma comment(lib,"..//Debug//Logic.lib")
#include "..//Cursov/RailSystem.h"
#include "..//Cursov/Train.h"
#include "..//Cursov/Railcar.h"
#include "..//Cursov/Place.h"
#include "Header.h"

class PlaceSerialization
{
public:
	PlaceSerialization(Place obj)
		: NamePassenger(obj.NamePassenger), PlaceNumber(obj.PlaceNumber) {};
	std::string NamePassenger{};
	int PlaceNumber{};

	Place Deserialization()
	{
		return Place(PlaceNumber, NamePassenger);
	}
};

class RailcarSerialization
{
public:
	unsigned int CountPlace;
	unsigned int Number;
	TicketType TypeRailcar;
	std::vector<PlaceSerialization> PlaceVector;
	RailcarSerialization(Railcar obj)
		: TypeRailcar(obj.TypeRailcar), CountPlace(obj.CountPlace), Number(obj.Number)
	{
		for (int i = 0; i < obj.PlaceVector.size(); i++)
		{
			PlaceVector.push_back(PlaceSerialization(obj.PlaceVector[i].Serialization()));
		}
	};

	Railcar Deserialization()
	{
		Railcar temp(TypeRailcar, CountPlace, Number);
		for (int i = 0; i < PlaceVector.size(); i++)
		{
			temp.PlaceVector.push_back(PlaceVector[i].Deserialization());
		}
		return temp;
	}

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
	TrainSerialization(Train obj)
		: TrainName(obj.TrainName), Destination(obj.Destination), DeparturePoint(obj.DeparturePoint),
		DateDeparture(obj.DateDeparture), DateArrival(obj.DateArrival)
	{
		for (int i = 0; i < obj.CarVector.size(); i++)
		{
			CarVector.push_back(RailcarSerialization(obj.CarVector[i].Serialization()));
		}
	};

	Train Deserialization()
	{
		Train temp(TrainName, Destination, DeparturePoint, DateDeparture, DateArrival);

		for (int i = 0; i < CarVector.size(); i++)
		{
			temp.CarVector.push_back(CarVector[i].Deserialization());
		}

		return temp;
	}

};

class RailSystemSerialization
{
public:
	std::map<std::string, TrainSerialization> TrainMap;
	RailSystemSerialization()
	{
		std::map<std::string, Train> temp = RailSystem::Serialization();
		for (auto x : temp)
		{
			TrainMap.insert( { x.first, TrainSerialization(x.second) });
		}
	}

	std::map<std::string, Train> Deserialization()
	{
		std::map<std::string, Train> temp;
		for (auto x : TrainMap)
		{
			temp.insert({ x.first, x.second.Deserialization() });
		}

		return temp;
	}

};

namespace boost {
	namespace serialization {

		template<class Archive>
		void serialize(Archive& archive, PlaceSerialization& obj, const unsigned int version)
		{
			archive& BOOST_SERIALIZATION_NVP(obj.NamePassenger);
			archive& BOOST_SERIALIZATION_NVP(obj.PlaceNumber);
		}

		template<class Archive>
		void serialize(Archive& archive, RailcarSerialization& obj, const unsigned int version)
		{
			archive& BOOST_SERIALIZATION_NVP(obj.CountPlace);
			archive& BOOST_SERIALIZATION_NVP(obj.Number);
			archive& BOOST_SERIALIZATION_NVP(obj.PlaceVector);
			archive& BOOST_SERIALIZATION_NVP(obj.TypeRailcar);
		}

		template<class Archive>
		void serialize(Archive& archive, TrainSerialization& obj, const unsigned int version)
		{
			archive& BOOST_SERIALIZATION_NVP(obj.CarVector);
			archive& BOOST_SERIALIZATION_NVP(obj.DateArrival);
			archive& BOOST_SERIALIZATION_NVP(obj.DateDeparture);
			archive& BOOST_SERIALIZATION_NVP(obj.DeparturePoint);
			archive& BOOST_SERIALIZATION_NVP(obj.Destination);
			archive& BOOST_SERIALIZATION_NVP(obj.TrainName);
		}

		template<class Archive>
		void serialize(Archive& archive, RailSystemSerialization& obj, const unsigned int version)
		{
			archive& BOOST_SERIALIZATION_NVP(obj.TrainMap);
		}

	} // namespace serialization
} // namespace boost


void Serial::save()
{
	std::ofstream file("archive.xml");
	boost::archive::xml_oarchive oa(file);

	/*
	PlaceSerialization a(10, "John");
	PlaceSerialization b(11, "Kojima");
	PlaceSerialization c(19, "Yulio");

	std::vector<PlaceSerialization> A;
	A.push_back(a);
	A.push_back(b);
	A.push_back(c);

	RailcarSerialization d(static_cast<TicketType>(1), 10, 2);
	d.PlaceVector = A;

	std::vector<RailcarSerialization> RailV;
	RailV.push_back(d);

	TrainSerialization train("Gof", "Moskow", "Kyiv", "11.12.2019 - 19:00", "12.12.2019 - 10:00");
	train.CarVector = RailV;*/
/*
RailSystemSerialization a;

oa& BOOST_SERIALIZATION_NVP(a);
}

void Serial::load()
{
	std::ifstream file("archive.xml");
	boost::archive::xml_iarchive ia(file);
	RailSystemSerialization a;
	ia& BOOST_SERIALIZATION_NVP(a);
	RailSystem::Deserialization(a.Deserialization());
}


*/