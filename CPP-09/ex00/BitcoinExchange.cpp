#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <cctype>

static void	errorBadInput(const std::string& line)
{
	std::cerr << "Error: bad input => " << line << std::endl;
}

static void	errorMsg(const std::string& msg)
{
	std::cerr << msg << std::endl;
}

static bool	isValidDateFormat(const std::string& date)
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (std::size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}
	return true;
}

static bool	isNotFutureDate(const std::string& date)
{
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	std::time_t t = std::time(NULL);
	std::tm* now = std::localtime(&t);

	int curY = now->tm_year + 1900;
	int curM = now->tm_mon + 1;
	int curD = now->tm_mday;

	if (year > curY) return false;
	if (year == curY && month > curM) return false;
	if (year == curY && month == curM && day > curD) return false;

	return true;
}

static bool	isValidCalendarDate(const std::string& date)
{
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2)
	{
		bool leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
		if (leap)
			monthDays[1] = 29;
	}

	if (day > monthDays[month - 1])
		return false;

	return isNotFutureDate(date);
}

static bool	validDate(const std::string& line, const std::string& date)
{
	if (!isValidDateFormat(date) || !isValidCalendarDate(date))
	{
		errorBadInput(line);
		return false;
	}
	return true;
}

static bool	validValue(const std::string& line, const std::string& value)
{
	double dvalue;
	std::size_t pos = 0;

	try
	{
		dvalue = std::stod(value, &pos);
	}
	catch (const std::invalid_argument&)
	{
		errorBadInput(line);
		return false;
	}
	catch (const std::out_of_range&)
	{
		errorMsg("Error: too large a number.");
		return false;
	}

	if (pos != value.size())
	{
		errorBadInput(line);
		return false;
	}

	if (dvalue < 0.0)
	{
		errorMsg("Error: not a positive number.");
		return false;
	}
	if (dvalue > 1000.0)
	{
		errorMsg("Error: too large a number.");
		return false;
	}
	return true;
}

static bool	parseLine(const std::string& line, std::string& date, std::string& value)
{
	std::size_t pos = line.find('|');
	if (pos == std::string::npos)
	{
		errorBadInput(line);
		return false;
	}

	if (pos == 0 || pos + 1 >= line.length()
		|| line[pos - 1] != ' '
		|| line[pos + 1] != ' ')
	{
		errorBadInput(line);
		return false;
	}

	date = line.substr(0, pos - 1);
	value = line.substr(pos + 2);

	if (date.find(' ') != std::string::npos
		|| value.find(' ') != std::string::npos
		|| value.empty())
	{
		errorBadInput(line);
		return false;
	}

	if (!validValue(line, value))
		return false;

	return true;
}

BitcoinExchange::BitcoinExchange(const std::string& file) : _inputFile(file) {}

void BitcoinExchange::runBtc()
{
	saveDataFile();
	processInputLines();
}

void BitcoinExchange::processInputLines()
{
	std::ifstream file(_inputFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open input file.");

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::string date;
		std::string value;
		double rate = 0.0;

		if (!parseLine(line, date, value))
			continue;

		if (!validDate(line, date))
			continue;

		if (!checkDatabase(line, date, rate))
			continue;

		double result = std::stod(value) * rate;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
}

bool BitcoinExchange::checkDatabase(const std::string& line, const std::string& date, double& outRate)
{
	std::map<std::string, double>::iterator it = _dataPairs.find(date);

	if (it != _dataPairs.end())
	{
		outRate = it->second;
		return true;
	}

	it = _dataPairs.lower_bound(date);
	if (it == _dataPairs.begin())
	{
		errorBadInput(line);
		return false;
	}

	--it;
	outRate = it->second;
	return true;
}

void BitcoinExchange::saveDataFile()
{
	std::ifstream file("data.csv");
	if (!file.is_open())
		throw std::runtime_error("Error: could not open data.csv file.");

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		std::stringstream ss(line);
		std::string date;
		std::string price;

		if (!std::getline(ss, date, ',') || !std::getline(ss, price))
			throw std::runtime_error("Error: bad data.csv format.");

		try {
			_dataPairs[date] = std::stod(price);
		}
		catch (...) {
			throw std::runtime_error("Error: bad data.csv value.");
		}
	}
}
