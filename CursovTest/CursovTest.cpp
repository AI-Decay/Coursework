#include "pch.h"
#include "CppUnitTest.h"
#include "../Cursov/Place.h"
#include "../Cursov/Railcar.h"
#include "../Cursov/RailSystem.h"
#include "../Cursov/Train.h"
#include <vector>
std::map<std::string, Train> RailSystem::TrainMap;

const std::map<std::string, Train> RawSystem = RailSystem::GetTrainMap();

void RefreshSystem()
{
	RailSystem::GetTrainMap() = RawSystem;
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace CursovTest
{
	TEST_CLASS(PlaceTest) 
	{
	public:
		TEST_METHOD(Place_Constructor_Test)
		{
			RefreshSystem();
			// arrange
			int number = 10;
			std::string name = "John Titor";

			// act
			Place place(number, name);

			// assert
			Assert::IsTrue(place.GetNamePassenger() == name);
			Assert::IsTrue(place.GetPlaceNumber() == number);
		}

		TEST_METHOD(Place_Serialization_Test)
		{
			RefreshSystem();
			// arrange
			int number = 10;
			std::string name = "John Titor";

			// act
			Place place(number, name);

			// assert
			Place object = place.Serialization();
			Assert::IsTrue(place.GetNamePassenger() == object.GetNamePassenger());
			Assert::IsTrue(place.GetPlaceNumber() == object.GetPlaceNumber());
		}
	};

	TEST_CLASS(RailcarTest)
	{
	public:
		TEST_METHOD(Railcar_Constructor_Test)
		{
			RefreshSystem();
			// arrange
			TicketType type = Luxury;
			unsigned int countplace = 50;
			unsigned int number = 1;

			// act
			Railcar railcar(type, countplace, number);

			// assert
			Assert::IsTrue(railcar.GetTypeRailcar() == type);
			Assert::IsTrue(railcar.GetCountPlace() == countplace);
			Assert::IsTrue(railcar.GetNumber() == number);
		}

		TEST_METHOD(Railcar_CreatePlace_Test)
		{
			RefreshSystem();
			// arrange
			TicketType type = Luxury;
			unsigned int countplace = 50;
			unsigned int number = 1;
			Railcar railcar(Luxury, 50, 1);
			
			
			// act
			railcar.CreatePlase();

			// assert
			std::vector<Place> PlaceVector = railcar.GetPlaceVector();
			Assert::IsTrue(PlaceVector.size() == countplace);
		}


		TEST_METHOD(Railcar_AddPlace_Test)
		{
			RefreshSystem();
			// arrange
			Railcar railcar(Luxury, 50, 1);
			railcar.CreatePlase();
			std::string name = "John Titor";
			unsigned int number = 10;
			// act
			railcar.AddPlace(name, number);

			// assert
			std::vector<Place> PlaceVector = railcar.GetPlaceVector();
			Assert::IsTrue(PlaceVector[number-1].GetNamePassenger() == name);
			Assert::IsTrue(PlaceVector[number-1].GetPlaceNumber() == number);
		}

		TEST_METHOD(Railcar_AddPlace_Exception_Type_of_out_of_range_Test)
		{
			RefreshSystem();
			//arrange
			Railcar railcar(Luxury, 50, 1);
			railcar.CreatePlase();

			// act
			auto func = [&] { railcar.AddPlace("John Titor", 51); };
			
			// assert
			Assert::ExpectException<std::out_of_range>(func);
		}

		TEST_METHOD(Railcar_AddPlace_Exception_Type_of_exception_Test)
		{
			RefreshSystem();
			//arrange
			Railcar railcar(Luxury, 50, 1);
			railcar.CreatePlase();
			railcar.AddPlace("John Titor", 5);
			// act
			auto func = [&] { railcar.AddPlace("John Titor", 5); };

			// assert
			Assert::ExpectException<std::exception>(func);
		}

		TEST_METHOD(Railcar_DelPlace_Test)
		{
			RefreshSystem();
			// arrange
			Railcar railcar(Luxury, 50, 1);
			railcar.CreatePlase();
			railcar.AddPlace("John Titor", 10);

			// act
			railcar.DelPlace(10);

			// assert
			auto PlaceVector = railcar.GetPlaceVector();
			Assert::IsTrue(PlaceVector[9].GetNamePassenger() == " ");
			Assert::IsTrue(PlaceVector[9].GetPlaceNumber() == 10);
		}

		TEST_METHOD(Railcar__DelPlace_Exception_Type_of_out_of_range_Test)
		{
			RefreshSystem();
			// arrange
			Railcar railcar(Luxury, 50, 1);
			railcar.CreatePlase();
			railcar.AddPlace("John Titor", 10);

			// act
			auto func = [&] { railcar.DelPlace(60); };

			// assert
			Assert::ExpectException<std::out_of_range>(func);
		}
	};

	TEST_CLASS(TrainTest)
	{
	public:

		TEST_METHOD(Train_Constructor_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";

			// act
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);

			// assert
			Assert::IsTrue(train.GetTrainName() == trainName);
			Assert::IsTrue(train.GetDestination() == destination);
			Assert::IsTrue(train.GetDeparturePoint() == departurePoint);
			Assert::IsTrue(train.GetDateDeparture() == dateDeparture);
			Assert::IsTrue(train.GetDateArrival() == dateArrival);
		}

		TEST_METHOD(Railcar_AddRailcar_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Budget;
			unsigned int countplace = 10;

			// act
			train.AddRailcar(type, countplace);

			// assert
			auto CarVector = train.GetCarVector();
			Assert::IsTrue(CarVector[0].GetTypeRailcar() == type);
			Assert::IsTrue(CarVector[0].GetCountPlace() == countplace);
		}

		TEST_METHOD(Railcar_DelRailcar_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			train.AddRailcar(Budget, 10);

			// act
			train.DelRailcar(1);

			// assert
			auto CarVector = train.GetCarVector();
			Assert::IsTrue(CarVector.size() == 0);
		}

		TEST_METHOD(Railcar_DelRailcar_Exception_Type_of_out_of_range_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			train.AddRailcar(Budget, 10);

			// act
			auto func = [&] { train.DelRailcar(2); };

			// assert
			auto CarVector = train.GetCarVector();
			Assert::ExpectException<std::out_of_range>(func);
		}

		TEST_METHOD(Railcar_DelRailcar_Exception_Type_of_exception_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			train.AddRailcar(Budget, 10);
			train.AddPlaceRailcar(1, "John Titor", 5);

			// act
			auto func = [&] { train.DelRailcar(1); };

			// assert
			auto CarVector = train.GetCarVector();
			Assert::ExpectException<std::exception>(func);
		}

		TEST_METHOD(Railcar_AddPlaceRailcar_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			train.AddRailcar(Budget, 10);
			std::string name = "Hideo Kojima";
			unsigned int number = 1;
			unsigned int numberRailcar = 1;
			
			// act
			train.AddPlaceRailcar(numberRailcar, name, number);

			// assert
			auto CarVector = train.GetCarVector();
			auto PlaceVector = CarVector[0].GetPlaceVector();
			Assert::IsTrue(CarVector[0].GetNumber() == numberRailcar);
			Assert::IsTrue(PlaceVector[number-1].GetNamePassenger() == name);
			Assert::IsTrue(PlaceVector[number-1].GetPlaceNumber() == number);
		}
		
		TEST_METHOD(Railcar_AddPlaceRailcar_Exception_Type_out_of_range_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			train.AddRailcar(Budget, 10);
			std::string name = "Hideo Kojima";
			unsigned int number = 1;
			auto CarVector = train.GetCarVector();

			// act
			auto func = [&] { train.AddPlaceRailcar(CarVector.size() + 1, name, number); };

			// assert
			Assert::ExpectException<std::out_of_range>(func);
		}


		TEST_METHOD(Railcar_DelPlaceRailcar_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			train.AddRailcar(Budget, 10);
			std::string name = "Hideo Kojima";
			unsigned int number = 1;
			unsigned int numberRailcar = 1;
			train.AddPlaceRailcar(numberRailcar, name, number);

			// act
			train.DelPlaceRailcar(numberRailcar, number);

			// assert
			auto CarVector = train.GetCarVector();
			auto PlaceVector = CarVector[0].GetPlaceVector();
			Assert::IsTrue(PlaceVector[number-1].GetNamePassenger() == " ");
			Assert::IsTrue(PlaceVector[number-1].GetPlaceNumber() == number);
		}

		TEST_METHOD(Railcar_DelPlaceRailcar_Exception_Type_out_of_range_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Star";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			Train train(trainName, destination, departurePoint, dateDeparture, dateArrival);
			train.AddRailcar(Budget, 10);
			std::string name = "Hideo Kojima";
			unsigned int number = 1;
			unsigned int numberRailcar = 1;
			auto CarVector = train.GetCarVector();
			train.AddPlaceRailcar(numberRailcar, name, number);

			// act
			auto func = [&] { train.DelPlaceRailcar(CarVector.size() + 1, number); };

			// assert
			Assert::ExpectException<std::out_of_range>(func);
		}

	};


	TEST_CLASS(RailSystemTest)
	{
	public:
		TEST_METHOD(Railcar_AddTrain_True_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Foos";
			std::string destination = "Hell";
			std::string departurePoint = "EA23";
			std::string dateDeparture = "13.11.2019 - 11:30";
			std::string dateArrival = "17.11.2019 - 1:30";

			// act
			bool actual = RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			Assert::IsTrue(actual);
			Assert::IsTrue(train.GetTrainName() == trainName);
			Assert::IsTrue(train.GetDestination() == destination);
			Assert::IsTrue(train.GetDeparturePoint() == departurePoint);
			Assert::IsTrue(train.GetDateDeparture() == dateDeparture);
			Assert::IsTrue(train.GetDateArrival() == dateArrival);
		}

		TEST_METHOD(Railcar_AddTrain_False_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "SSSS";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);

			// act
			bool actual = RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);

			// assert
			auto size = RailSystem::GetTrainMap().size();
			Assert::IsTrue(actual == false);
			Assert::IsTrue(size == 1);
		}


		TEST_METHOD(Railcar_DelTrain_True_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Simple";
			std::string destination = "Moskow";
			std::string departurePoint = "Kyiv";
			std::string dateDeparture = "12.11.2999 - 12:30";
			std::string dateArrival = "13.11.2899 - 12:38";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);

			// act
			bool actual = RailSystem::DelTrain(trainName);

			// assert
			auto size = RailSystem::GetTrainMap().size();
			Assert::IsTrue(actual);
			Assert::IsTrue(size == 0);
		}
		TEST_METHOD(Railcar_DelTrain_False_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "HardWork";
			std::string destination = "Moskow";
			std::string departurePoint = "Kyiv";
			std::string dateDeparture = "12.11.2999 - 12:30";
			std::string dateArrival = "13.11.2899 - 12:38";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			std::string otherName = "Golden";

			// act
			bool actual = RailSystem::DelTrain(otherName);

			// assert
			auto size = RailSystem::GetTrainMap().size();
			Assert::IsFalse(actual);
			Assert::IsTrue(size == 1);
		}

		TEST_METHOD(Railcar_AddRailcarToTrain_True_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Fair";
			std::string destination = "German";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;

			// act
			bool actual = RailSystem::AddRailcarToTrain(trainName, type, countPlace);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto railcar = train.GetCarVector()[0];
			Assert::IsTrue(actual);
			Assert::IsTrue(railcar.GetTypeRailcar() == type);
			Assert::IsTrue(railcar.GetCountPlace() == countPlace);
		}

		TEST_METHOD(Railcar_AddRailcarToTrain_False_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "BigStar";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			std::string otherName = "Maria";

			// act
			bool actual = RailSystem::AddRailcarToTrain(otherName, type, countPlace);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto size = train.GetCarVector().size();
			Assert::IsFalse(actual);
			Assert::IsTrue(size == 0);
		}

		TEST_METHOD(Railcar_DelRailcarToTrain_True_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Spos";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			unsigned int number = 1;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);

			// act
			bool actual = RailSystem::DelRailcarToTrain(trainName, number);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto size = train.GetCarVector().size();
			Assert::IsTrue(actual);
			Assert::IsTrue(size == 0);
		}

		TEST_METHOD(Railcar_DelRailcarToTrain_False_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Mvs";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			unsigned int number = 1;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			std::string otherName = "Maria";

			// act
			bool actual = RailSystem::DelRailcarToTrain(otherName, number);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto size = train.GetCarVector().size();
			Assert::IsFalse(actual);
			Assert::IsTrue(size == 1);
		}

		
		TEST_METHOD(Railcar_AddPlace_True_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Polish";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			unsigned int number = 1;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			unsigned int numberOfRailcar = 1;
			unsigned int numberOfPlace = 5;
			std::string passname = "Oda Nobunaga";

			// act
			bool actual = RailSystem::AddPlace(trainName, passname, numberOfRailcar, numberOfPlace);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto railcar = train.GetCarVector()[0];
			auto place = railcar.GetPlaceVector()[numberOfPlace-1];
			Assert::IsTrue(actual);
			Assert::IsTrue(place.GetNamePassenger() == passname);
			Assert::IsTrue(place.GetPlaceNumber() == numberOfPlace);
		}

		TEST_METHOD(Railcar_AddPlace_False_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Poko";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			unsigned int number = 1;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			unsigned int numberOfRailcar = 1;
			unsigned int numberOfPlace = 5;
			std::string passname = "Oda Nobunaga";
			std::string otherName = "Juid";

			// act
			bool actual = RailSystem::AddPlace(otherName, passname, numberOfRailcar, numberOfPlace);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto railcar = train.GetCarVector()[0];
			auto place = railcar.GetPlaceVector()[numberOfPlace - 1];
			Assert::IsFalse(actual);
			Assert::IsTrue(place.GetNamePassenger() == " ");
			Assert::IsTrue(place.GetPlaceNumber() == numberOfPlace);
		}

		TEST_METHOD(Railcar_DelPlace_True_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Atlantic";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			unsigned int numberOfRailcar = 1;
			unsigned int numberOfPlace = 5;
			std::string passname = "Oda Nobunaga";
			RailSystem::AddPlace(trainName, passname, numberOfRailcar, numberOfPlace);

			// act
			bool actual = RailSystem::DelPlace(trainName, numberOfRailcar, numberOfPlace);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto railcar = train.GetCarVector()[0];
			auto place = railcar.GetPlaceVector()[numberOfPlace - 1];
			Assert::IsTrue(actual);
			Assert::IsTrue(place.GetNamePassenger() == " ");
			Assert::IsTrue(place.GetPlaceNumber() == numberOfPlace);
		}

		TEST_METHOD(Railcar_DelPlace_False_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			unsigned int numberOfRailcar = 1;
			unsigned int numberOfPlace = 5;
			std::string passname = "Oda Nobunaga";
			RailSystem::AddPlace(trainName, passname, numberOfRailcar, numberOfPlace);
			std::string otherName = "Juid";

			// act
			bool actual = RailSystem::DelPlace(otherName, numberOfRailcar, numberOfPlace);

			// assert
			auto train = RailSystem::GetTrainMap().find(trainName)->second;
			auto railcar = train.GetCarVector()[0];
			auto place = railcar.GetPlaceVector()[numberOfPlace - 1];
			Assert::IsFalse(actual);
			Assert::IsTrue(place.GetNamePassenger() == passname);
			Assert::IsTrue(place.GetPlaceNumber() == numberOfPlace);
		}

		TEST_METHOD(Railcar_InfoAboutPlaceRailcar_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Coupe;
			unsigned int countPlace = 10;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			unsigned int numberOfRailcar = 1;
			unsigned int numberOfPlace1 = 2;
			std::string passname1 = "Oda Nobunaga";
			unsigned int numberOfPlace2 = 4;
			std::string passname2 = "Gerasim Mumu";
			RailSystem::AddPlace(trainName, passname1, numberOfRailcar, numberOfPlace1);
			RailSystem::AddPlace(trainName, passname2, numberOfRailcar, numberOfPlace2);
			std::string expected = "Вiльнi мiсця : 1 3 5 6 7 8 9 10 \nЗайнятi мiсця : 2 4 \n";
			// act
			std::string actual = RailSystem::InfoAboutPlaceRailcar(trainName, numberOfRailcar);

			// assert
			Assert::AreEqual(actual, expected);
		}

		TEST_METHOD(Railcar_InfoAboutAllTrain_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			trainName = "Star";
			destination = "German";
			departurePoint = "Std";
			dateDeparture = "11.11.2029 - 19:30";
			dateArrival = "13.14.2029 - 14:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			std::list<std::string> expected = { "Iм'я потягу : Bosuid\nДата вiдправлення : 12.11.2019 - 12:30\nДата прибуття : 13.11.2019 - 12:30\nМiсце вiдправлення : Japan\nМiсце прибуття : Moskow\n", 
												"Iм'я потягу : Star\nДата вiдправлення : 11.11.2029 - 19:30\nДата прибуття : 13.14.2029 - 14:30\nМiсце вiдправлення : Std\nМiсце прибуття : German\n" };
			// act
			std::list<std::string> actual = RailSystem::InfoAboutAllTrain();

			// assert
			Assert::IsTrue(actual == expected);
		}


		TEST_METHOD(Railcar_FindTrains_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			trainName = "Star";
			destination = "German";
			departurePoint = "Std";
			dateDeparture = "11.11.2029 - 19:30";
			dateArrival = "13.14.2029 - 14:30";
			std::string keyword = "suid";
			std::list<std::string> expected = { "Iм'я потягу : Bosuid\nДата вiдправлення : 12.11.2019 - 12:30\nДата прибуття : 13.11.2019 - 12:30\nМiсце вiдправлення : Japan\nМiсце прибуття : Moskow\n"};
			// act
			std::list<std::string> actual = RailSystem::FindTrains(keyword);

			// assert
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(Railcar_InfoAboutTrain_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			std::string expected = "Iм'я потягу : Bosuid\nДата вiдправлення : 12.11.2019 - 12:30\nДата прибуття : 13.11.2019 - 12:30\nМiсце вiдправлення : Japan\nМiсце прибуття : Moskow\n";
			
			// act
			std::string actual = RailSystem::InfoAboutTrain(trainName);

			// assert
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(Railcar_InfoOnePlace_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Luxury;
			unsigned int countPlace = 5;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			std::string passName = "John Titor";
			unsigned int numberRailcar = 1;
			unsigned int numberPlace = 3;
			RailSystem::AddPlace(trainName, passName, numberRailcar, numberPlace);
			std::string expected = "Iм'я потягу : Bosuid\nДата вiдправлення : 12.11.2019 - 12:30\nДата прибуття : 13.11.2019 - 12:30\nМiсце вiдправлення : Japan\nМiсце прибуття : Moskow\nНомер вагону : 1\nНомер мiсця : 3\nIм'я пасажиру : John Titor\n";

			// act
			std::string actual = RailSystem::InfoOnePlace(trainName, numberRailcar, numberPlace);

			// assert
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(Railcar_FindPlaceForDate_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Luxury;
			unsigned int countPlace = 5;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			std::string passName = "John Titor";
			unsigned int numberRailcar = 1;
			unsigned int numberPlace = 3;
			RailSystem::AddPlace(trainName, passName, numberRailcar, numberPlace);
			std::string keyword = "12.11.2019";
			std::list<std::string> expected = { "Iм'я потягу : Bosuid\nДата вiдправлення : 12.11.2019 - 12:30\nДата прибуття : 13.11.2019 - 12:30\nМiсце вiдправлення : Japan\nМiсце прибуття : Moskow\nНомер вагону : 1\nНомер мiсця : 3\nIм'я пасажиру : John Titor\n"};

			// act
			std::list<std::string> actual = RailSystem::FindPlaceForDate(keyword);

			// assert
			Assert::IsTrue(actual == expected);
		}

		TEST_METHOD(Railcar_InfoPercentRailcar_Test)
		{
			RefreshSystem();
			// arrange
			std::string trainName = "Bosuid";
			std::string destination = "Moskow";
			std::string departurePoint = "Japan";
			std::string dateDeparture = "12.11.2019 - 12:30";
			std::string dateArrival = "13.11.2019 - 12:30";
			RailSystem::AddTrain(trainName, destination, departurePoint, dateDeparture, dateArrival);
			TicketType type = Luxury;
			unsigned int countPlace = 5;
			RailSystem::AddRailcarToTrain(trainName, type, countPlace);
			std::string passName = "John Titor";
			unsigned int numberRailcar = 1;
			unsigned int numberPlace = 3;
			RailSystem::AddPlace(trainName, passName, numberRailcar, numberPlace);
			passName = "Saber";
			numberPlace = 2;
			RailSystem::AddPlace(trainName, passName, numberRailcar, numberPlace);
			std::string expected = "40.000000%\n";

			// act
			std::string actual = RailSystem::InfoPercentRailcar(trainName);

			// assert
			Assert::IsTrue(actual == expected);
		}

	};

}
