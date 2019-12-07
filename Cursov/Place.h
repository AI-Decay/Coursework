#pragma once
#include <string>
class Place
{
private:
	std::string NamePassenger{};
	int PlaceNumber{};
public:
	Place(int number, std::string name);
	~Place();
	std::string GetNamePassenger();
	int GetPlaceNumber();
	Place Serialization();
	void SetNamePassenger(std::string name);
};