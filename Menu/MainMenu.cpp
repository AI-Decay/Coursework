#include <iostream>
#include <list>
#include <vector>
#include <locale>
#include <regex>
#pragma comment(lib,"Logic.lib")
#include "..//Cursov/RailSystem.h"

std::map<std::string, Train> RailSystem::TrainMap;

bool IsBigChar(std::string str)
{
	if (islower(str[0]) || str.empty())
	{
		std::cout << "Назва повинна починатися з великої лiтери : " << std::endl;
		return false;
	}
	else
		return true;
}

bool EmptyCheck(std::string str)
{
	if (str.empty())
	{
		std::cout << "Рядок не може бути порожнiм" << std::endl << std::endl;
		return false;
	}
	return true;
}

bool DateCheck(std::string str)
{
	//date format: 11.12.2019
	if (str.size() == 10)
	{
		int day = stoi(str.substr(0, 2));
		int month = stoi(str.substr(3, 4));
		int year = stoi(str.substr(6, 9));
		bool com = str[2] == str[5] && str[2] == '.';
		if (day > 31 || day < 1)
		{
			std::cout << "День повинен бути в межах вiд 1 до 31" << std::endl;
			return false;
		}
		else if (month > 12 || month < 1)
		{
			std::cout << "Мiсяць повинен бути в межах вiд 1 до 12" << std::endl;
			return false;
		}
		else if (year > 9999 || year < 2000)
		{
			std::cout << "Рiк повинен бути в межах вiд 2000 до 9999" << std::endl;
			return false;
		}
		else if (!com)
		{
			std::cout << "Введiть дату у форматi ХХ.ХХ.ХХХХ" << std::endl;
			return false;
		}
		else
			return true;
	}

	std::cout << "Введiть дату у форматi ХХ.ХХ.ХХХХ" << std::endl;
	return false;
}

bool DateCheckAndTime(std::string str)
{
	//date format: 11.12.2019 - 11:30
	

	if (str.size() == 18)
	{
		
		int hour = stoi(str.substr(13, 14));
		int minutes = stoi(str.substr(16, 17));
		bool space = str[10] == str[12] && str[10] == ' ';
		bool colon = str[15] == ':';
		bool dash = str[11] == '-';

		DateCheck(str.substr(0, 9));
		
		if (hour > 24 || hour < 0)
		{
			std::cout << "Години повиннi бути в межах вiд 0 до 24" << std::endl;
			return false;
		}
		else if (hour > 60 || hour < 0)
		{
			std::cout << "Хвилини повиннi бути в межах вiд 0 до 60" << std::endl;
			return false;
		}
		else if (!space || !colon || !dash)
		{
			std::cout << "Введiть дату у форматi ХХ.ХХ.ХХХХ - Hour:Minutes " << std::endl;
			return false;
		}
		else
			return true;
	}

	std::cout << "Введiть дату у форматi ХХ.ХХ.ХХХХ - Hour:Minutes " << std::endl;

	return false;
}


int main()
{
	setlocale(LC_ALL, "Ukrainian");
	std::string input{};
	char choise{};
	std::string errorInputMessage{ "Некоректний ввiд" };
	while (true)
	{
		system("cls");
		std::cout << "<<Railway ticket office>>" << std::endl << std::endl;

		std::cout << "1. Операцiї над потягами : " << std::endl;
		std::cout << "2. Операцiї над вагонами : " << std::endl;
		std::cout << "3. Операцiї над бронюванням : " << std::endl;
		std::cout << "4. Пошук : " << std::endl;
		std::cout << "5. Зберiгти даннi : " << std::endl;
		std::cout << "6. Завантажити даннi : " << std::endl;
		std::cout << "Оберiть команду : " << std::endl;
		
		std::cin >> choise;
		
		switch (choise)
		{
			case '1' :
			std::cout << "1 Додавати потяг" << std::endl;
			std::cout << "2 Видаляти потяг" << std::endl;
			std::cout << "3 Переглянути всi потяги" << std::endl;
			std::cout << "4 Переглянути данi конкретного потягу" << std::endl;
			std::cout << "5 Переглянути вагони потягу з вiдсотками заброньованих в них мiсць" << std::endl;
			std::cout << "Оберiть команду : " << std::endl;
			std::cin >> choise;
			switch (choise)
			{
				case '1':
				{
					std::string name, dest, depart, dated, datea;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin.get();
					std::getline(std::cin, name);
					while (!IsBigChar(name))
					{
						std::getline(std::cin, name);
					}
					std::cout << "Введiть пунтк вiдправлення потягу : " << std::endl;
					std::getline(std::cin, dest);
					while (!IsBigChar(dest))
					{
						std::getline(std::cin, dest);
					}
					std::cout << "Введiть пунтк призначення : " << std::endl;
					std::getline(std::cin, depart);
					while (!IsBigChar(depart))
					{
						std::getline(std::cin, depart);
					}
					std::cout << "Введiть дату вiдправлення : " << std::endl;
					std::getline(std::cin, dated);
					while (!DateCheckAndTime(dated))
					{
						std::getline(std::cin, dated);
					}
					std::cout << "Введiть дату прибуття : " << std::endl;
					std::getline(std::cin, datea);
					while (!DateCheckAndTime(datea))
					{
						std::getline(std::cin, datea);
					}
					RailSystem::AddTrain(name, depart, dest, dated, datea);
				}
					break;
				case '2':
				{
					std::string name;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin.get();
					std::getline(std::cin, name);
					while (!IsBigChar(name))
					{
						std::cin.get();
						std::getline(std::cin, name);
					}
						if (RailSystem::DelTrain(name))
							std::cout << "Елемент видалено" << std::endl;
						else
							std::cout << "Потягу з таким iм'ям не знайдено" << std::endl;
				}
					break;
				case '3':
				{
					std::list<std::string> temp = RailSystem::InfoAboutAllTrain();
					for (auto info : temp)
					{
						std::cout << info << std::endl;
					}
					system("pause");
				}
					break;
				case '4':
				{
					std::string name;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::cin.get();
						std::getline(std::cin, name);
					}
					std::cout << RailSystem::InfoAboutTrain(name) << std::endl;
					system("pause");
				}
					break;
				case '5':
				{
					std::string name;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::cin.get();
						std::getline(std::cin, name);
					}
					std::cout << RailSystem::InfoPercentRailcar(name) << std::endl;
					system("pause");
				}
					break;
				default: std::cout << errorInputMessage << std::endl;
					system("pause");
					break;
			}
			break;

			case '2' :
			std::cout << "1 Додавати вагон до потягу" << std::endl;
			std::cout << "2 Видаляти вагон з потягу (тiльки якщо в ньому немає заброньованих мiсць)" << std::endl;
			std::cout << "3 Можливiсть переглянути зайнятi/не зайнятi мiсця вагону" << std::endl;
			std::cin >> choise;
			switch (choise)
			{
				case '1':
				{
					std::string name, depart;
					int type, countplace;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::getline(std::cin, name);
					}
					std::cout << "Оберiть тип вагону : " << std::endl;
					std::cout << "1. Плацкарт" << std::endl;
					std::cout << "2. Купе" << std::endl;
					std::cout << "3. Люкс" << std::endl;
					std::cin >> type;
					std::cout << "Введiть кiлькiсть мiсць: " << std::endl;
					std::cin >> countplace;
					if(RailSystem::AddRailcarToTrain(name, static_cast<TicketType>(type), countplace))
						std::cout << "Успiшно додано" << std::endl;
					else
						std::cout << "Помилка при додаваннi" << std::endl;
					system("pause");
				}
					break;
				case '2':
				{
					std::string name;
					int number = 0;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::cin.get();
						std::getline(std::cin, name);
					}
					std::cout << "Введiть номер вагону : " << std::endl;
					std::cin >> number;
					try
					{
						if(RailSystem::DelRailcarToTrain(name, number))
							std::cout << "Успiшно видалено" << std::endl;
						else
							std::cout << "Помилка при видаленнi" << std::endl;
					}
					catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
						
					}
					system("pause");
				}
					break;
				case '3':
				{
					std::string name;
					int number = 0;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::cin.get();
						std::getline(std::cin, name);
					}
					std::cout << "Введiть номер вагону : " << std::endl;
					std::cin >> number;
					try
					{
						std::cout << RailSystem::InfoAboutPlaceRailcar(name, number) << std::endl;
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
						system("pause");
				}
					break;
				default: std::cout << errorInputMessage << std::endl;
					system("pause");
					break;
			}
			break;

			case '3' : 
			std::cout << "1 Додавати бронювання" << std::endl;
			std::cout << "2 Вiдмiнити бронювання" << std::endl;
			std::cout << "3 Змiнити бронювання" << std::endl;
			std::cout << "4 Переглянути iнформацiю про бронювання" << std::endl;
			std::cin >> choise;
			switch (choise)
			{
				case '1':
				{
					std::string name, passname;
					unsigned int number = 0;
					unsigned int index = 0;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::getline(std::cin, name);
					}
					std::cout << "Введiть номер вагону : " << std::endl;
					std::cin >> index;
					std::cout << "Введiть ваше iм'я : " << std::endl;
					std::getline(std::cin, passname);
					while (!IsBigChar(passname))
					{
						std::getline(std::cin, passname);
					}
					std::cout << "Введiть номер мiсця : " << std::endl;
					std::cin >> number;
					try
					{
						if(RailSystem::AddPlace(name, passname, index, number))
							std::cout << "Успiшно додано" << std::endl;
						else
							std::cout << "Помилка при додаваннi" << std::endl;
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
						system("pause");
					}
				}
					break;
				case '2':
				{
					std::string name;
					unsigned int number = 0;
					unsigned int index = 0;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::cin.get();
						std::getline(std::cin, name);
					}
					std::cout << "Введiть номер вагону : " << std::endl;
					std::cin >> index;
					std::cout << "Введiть номер мiсця : " << std::endl;
					std::cin >> number;
					try
					{
						if(RailSystem::DelPlace(name, index, number))
							std::cout << "Успiшно видалено" << std::endl;
						else
							std::cout << "Помилка при видаленнi" << std::endl;
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
						system("pause");
					}
				}
					break;
				case '3':
				{
					std::string name, passname;
					unsigned int oldnumber = 0;
					unsigned int newnumber = 0;
					unsigned int index = 0;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::getline(std::cin, name);
					}
					std::cout << "Введiть номер вагону : " << std::endl;
					std::cin >> index;
					std::cout << "Введiть номер мiсця : " << std::endl;
					std::cin >> oldnumber;
					std::cout << "Введiть новий номер мiсця : " << std::endl;
					std::cin >> newnumber;
					std::cout << "Введiть iм'я : " << std::endl;
					std::cin.get();
					std::getline(std::cin, passname);
					try
					{
						if(RailSystem::DelPlace(name, index, oldnumber) & RailSystem::AddPlace(name, passname, index, newnumber))
							std::cout << "Успiшно змiнено" << std::endl;
						else
							std::cout << "Помилка при змiнi" << std::endl;
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
						system("pause");
					}
				}
					break;
				case '4':
				{
					std::string name;
					unsigned int number = 0;
					unsigned int index = 0;
					std::cout << "Введiть iм'я потягу : " << std::endl;
					std::cin >> name;
					while (!IsBigChar(name))
					{
						std::getline(std::cin, name);
					}
					std::cout << "Введiть номер вагону : " << std::endl;
					std::cin >> index;
					std::cout << "Введiть номер мiсця : " << std::endl;
					std::cin >> number;
					try
					{
						std::cout << RailSystem::InfoOnePlace(name, index, number) << std::endl;
					}
					catch (std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
					system("pause");
				}
					break;
				default: std::cout << errorInputMessage << std::endl;
					system("pause");
					break;
			}
			break;

			case '4' : 
			std::cout << "1 Пошуку по ключовому слову серед потягiв" << std::endl;
			std::cout << "2 Пошуку бронi по датi бронювання" << std::endl;
			std::cin >> choise;
			switch (choise)
			{
			case '1':
			{
				std::string word;
				std::cout << "Введiть ключове слово : " << std::endl;
				std::cin.get();
				std::getline(std::cin, word);
				while (!EmptyCheck(word))
				{
					std::cin.get();
					std::getline(std::cin, word);
				}
				std::list<std::string> info = RailSystem::FindTrains(word);
				for (auto x : info)
				{
					std::cout << x << std::endl;
				}
				system("pause");
			}
				break;
			case '2':
			{
				std::string date;
				std::cout << "Введiть дату бронювання : " << std::endl;
				std::cin.get();
				std::getline(std::cin, date);
				while (!DateCheck(date))
				{
					std::getline(std::cin, date);
				}
				std::list<std::string> info = RailSystem::FindPlaceForDate(date);
				for (auto x : info)
				{
					std::cout << x << std::endl;
				}
				system("pause");
			}
				break;
			default: std::cout << errorInputMessage << std::endl;
				system("pause");
				break;
			}
			break;

			case '5' :
				RailSystem::SaveDataBase();
				std::cout << "Даннi Збереженно" << std::endl;
				system("pause");
			break;

			case '6' :
				RailSystem::LoadDataBase();
				std::cout << "Даннi Завантаженно" << std::endl;
				system("pause");
			break;
		default: std::cout << errorInputMessage << std::endl;
			system("pause");
			break;
		}
	}
	return 0;
}