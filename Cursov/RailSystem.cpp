#include "RailSystem.h"

bool RailSystem::AddTrain(std::string name, std::string dest, std::string depart, std::string dated, std::string datea)
{
	return TrainMap.insert({ name, Train(name, dest, depart, dated, datea) }).second;
}

bool RailSystem::DelTrain(std::string name)
{
	return static_cast<bool>(TrainMap.erase(name));	
}

bool RailSystem::AddRailcarToTrain(std::string name, TicketType type, unsigned int countplace)
{
	if (TrainMap.find(name) != TrainMap.end())
	{
		TrainMap.find(name)->second.AddRailcar(type, countplace);
		return true;
	}
	else
		return false;
}

bool RailSystem::DelRailcarToTrain(std::string name, unsigned int number)
{
	if (TrainMap.find(name) != TrainMap.end())
	{
		TrainMap.find(name)->second.DelRailcar(number);
		return true;
	}
	return false;
}

bool RailSystem::AddPlace(std::string trainname, std::string passname, unsigned int indexRailcar, unsigned int numberPlace)
{
	if (TrainMap.find(trainname) != TrainMap.end())
	{
		 TrainMap.find(trainname)->second.AddPlaceRailcar(indexRailcar, passname, numberPlace);
		 return true;
	}
	else
		return false;
}

bool RailSystem::DelPlace(std::string trainname, unsigned int indexRailcar, unsigned int numberPlace)
{
	if (TrainMap.find(trainname) != TrainMap.end())
	{
		TrainMap.find(trainname)->second.DelPlaceRailcar(indexRailcar, numberPlace);
		return true;
	}
	else
		return false;
}

std::map<std::string, Train> RailSystem::Serialization()
{
	return TrainMap;
}

void RailSystem::Deserialization(std::map<std::string, Train> obj)
{
	TrainMap = obj;
}

void RailSystem::LoadDataBase()
{
	Serialize::Load();
}

void RailSystem::SaveDataBase()
{
	Serialize::Save();
}


std::map<std::string, Train>& RailSystem::GetTrainMap()
{
	return TrainMap;
}


std::string RailSystem::InfoAboutPlaceRailcar(std::string name, unsigned int number)
{
	auto find = TrainMap.find(name);
	if (TrainMap.find(name) != TrainMap.end())
	{
		std::string free{};
		std::string occup{};
		auto PlaceVector = find->second.GetCarVector()[number-1].GetPlaceVector();
		for (size_t i = 0; i < PlaceVector.size(); i++)
		{
			if (PlaceVector[i].GetNamePassenger() == " ")
				free += std::to_string(PlaceVector[i].GetPlaceNumber()) + ' ';
			else
				occup += std::to_string(PlaceVector[i].GetPlaceNumber()) + ' ';
		}

		return "Вiльнi мiсця : " + free + '\n' + "Зайнятi мiсця : " + occup + '\n';
	}
	else
		return std::string{ "Елемент не знайдено" };
}

const std::list<std::string> RailSystem::InfoAboutAllTrain()
{
	std::list<std::string> info{};

	for (auto x : TrainMap)
	{
		info.push_back(InfoAboutTrain(x.first));
	}

	return info;
}

const std::list<std::string> RailSystem::FindTrains(std::string word)
{
	std::list<std::string> info{};

	for (auto x : TrainMap)
	{
		if (x.first.find(word) != std::string::npos)
			info.push_back(InfoAboutTrain(x.first));
	}
	return info;
}

const std::string RailSystem::InfoAboutTrain(std::string name)
{
	auto find = TrainMap.find(name);
	if (TrainMap.find(name) != TrainMap.end())
	{
		std::string result =
			"Iм'я потягу : " + find->second.GetTrainName() + '\n' +
			"Дата вiдправлення : " + find->second.GetDateDeparture() + '\n' +
			"Дата прибуття : " + find->second.GetDateArrival() + '\n' +
			"Мiсце вiдправлення : " + find->second.GetDeparturePoint() + '\n' +
			"Мiсце прибуття : " + find->second.GetDestination() + '\n';

		return result;
	}
	else
		return std::string{ "Потяг не знайдено" };
}

std::string RailSystem::InfoOnePlace(std::string name, unsigned int numberRailcar, unsigned int numberPlace)
{
	numberRailcar--;
	numberPlace--;
	auto find = TrainMap.find(name);
	if (find != TrainMap.end())
	{
		if (numberRailcar > find->second.GetCarVector().size())
			throw std::exception("Такого вагону не iснує");

		if (numberPlace > find->second.GetCarVector()[numberRailcar].GetCountPlace())
			throw std::exception("Такого мiсця не iснує");

		auto Railcar = find->second.GetCarVector()[numberRailcar];

		std::string result =
			"Iм'я потягу : " + find->second.GetTrainName() + '\n' +
			"Дата вiдправлення : " + find->second.GetDateDeparture() + '\n' +
			"Дата прибуття : " + find->second.GetDateArrival() + '\n' +
			"Мiсце вiдправлення : " + find->second.GetDeparturePoint() + '\n' +
			"Мiсце прибуття : " + find->second.GetDestination() + '\n' +
			"Номер вагону : " + std::to_string(Railcar.GetNumber()) + '\n' +
			"Номер мiсця : " + std::to_string(Railcar.GetPlaceVector()[numberPlace].GetPlaceNumber()) + '\n' +
			"Iм'я пасажиру : " + Railcar.GetPlaceVector()[numberPlace].GetNamePassenger() + '\n';
		return result;
	}
	else
		throw std::exception("Потяг не знайдено");
}

const std::list<std::string> RailSystem::FindPlaceForDate(std::string date)
{
	std::list<std::string> info{};

	for (auto x : TrainMap)
	{
		if (x.second.GetDateDeparture().find(date) != std::string::npos)
		{
			std::string name = x.second.GetTrainName();
			for (int i = 0; i < x.second.GetCarVector().size(); i++)
			{
				auto PlaceVector = x.second.GetCarVector()[i].GetPlaceVector();
				for (int j = 0; j < PlaceVector.size(); j++)
				{
					if (PlaceVector[j].GetNamePassenger() != " ")
						info.push_back(InfoOnePlace(x.second.GetTrainName(), i+1, j+1));
				}
			}
		}
	}
	return info;
}

const std::string RailSystem::InfoPercentRailcar(std::string name)
{
	auto find = TrainMap.find(name);
	if (find != TrainMap.end())
	{
		std::string result{};
		auto CarVector = find->second.GetCarVector();
		for (size_t i = 0; i < CarVector.size(); i++)
		{
			double count = 0;
			for (size_t j = 0; j < CarVector[i].GetCountPlace(); j++)
			{
				if (CarVector[i].GetPlaceVector()[j].GetNamePassenger() != " ")
					count++;
			}
			result += std::to_string(count / CarVector[i].GetCountPlace() * 100) + '%' + '\n';
		}
		return result;
	}
	return std::string{ "Потяг не знайдено" };
}