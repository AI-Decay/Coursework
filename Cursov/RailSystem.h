#pragma once
#include <map>
#include <list>
#include <vector>
#include <list>
#include "Train.h"
#pragma comment(lib,"Serialization.lib")
#include "../Serialization/Serialize.h"

class RailSystem
{
private:
	static std::map<std::string, Train> TrainMap;
	RailSystem() = delete;
	~RailSystem() = delete;
public:
	static bool AddTrain(std::string name, std::string dest, std::string depart, std::string dated, std::string datea);
	static bool DelTrain(std::string name);
	static bool AddRailcarToTrain(std::string name, TicketType type, unsigned int countplace);
	static bool DelRailcarToTrain(std::string name, unsigned int number);
	static std::string InfoAboutPlaceRailcar(std::string name, unsigned int number);
	static bool AddPlace(std::string trainname, std::string passname, unsigned int indexRailcar, unsigned int numberPlace);
	static bool DelPlace(std::string trainname, unsigned int indexRailcar, unsigned int numberPlace);
	static std::string InfoOnePlace(std::string name, unsigned int numberRailcar, unsigned int numberPlace);
	static const std::string InfoAboutTrain(std::string name);
	static const std::list<std::string> InfoAboutAllTrain();
	static const std::string InfoPercentRailcar(std::string name);
	static const std::list<std::string> FindTrains(std::string word);
	static const std::list<std::string> FindPlaceForDate(std::string word);
	static std::map<std::string, Train> Serialization();
	static std::map<std::string, Train>& GetTrainMap();
	static void Deserialization(std::map<std::string, Train> obj);
	static void LoadDataBase();
	static void SaveDataBase();
};
