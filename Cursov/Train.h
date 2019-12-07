#pragma once
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include "Railcar.h"

class Train
{
private:
	std::string TrainName{};
	std::string Destination{};
	std::string DeparturePoint{};
	std::string DateDeparture{};
	std::string DateArrival{};
	std::vector<Railcar> CarVector{};
public:
	Train(std::string name, std::string dest, std::string depart, std::string dated, std::string datea);
	~Train();
	void AddRailcar(TicketType type, unsigned int countplace);
	void DelRailcar(unsigned int position);
	void AddPlaceRailcar(unsigned int index, std::string name, unsigned int number);
	void DelPlaceRailcar(unsigned int index, unsigned int number);
	std::string GetTrainName();
	std::string GetDestination();
	std::string GetDeparturePoint();
	std::string GetDateDeparture();
	std::string GetDateArrival();
	std::vector<Railcar>& GetCarVector();

	Train Serialization();

};