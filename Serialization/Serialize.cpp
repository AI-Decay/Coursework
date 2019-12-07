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
#include "BoostSerializationClass.h"
#include "Serialize.h"


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


void Serialize::Save()
{
	std::ofstream file("archive.xml");
	boost::archive::xml_oarchive oa(file);

	RailSystemSerialization a;

	oa& BOOST_SERIALIZATION_NVP(a);
}

void Serialize::Load()
{
	std::ifstream file("archive.xml");
	boost::archive::xml_iarchive ia(file);
	RailSystemSerialization a;
	ia& BOOST_SERIALIZATION_NVP(a);
	RailSystem::Deserialization(a.Deserialization());
}