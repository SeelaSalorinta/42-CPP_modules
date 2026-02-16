#pragma once

#include <map>
#include <string>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_dataPairs;
		std::string						_inputFile;

		void	saveDataFile();
		void	processInputLines();
		bool	checkDatabase(const std::string& line,
							const std::string& date,
							double& outRate);

	public:
		BitcoinExchange() = delete;
		BitcoinExchange(const std::string& file);
		BitcoinExchange(const BitcoinExchange& other) = default;
		BitcoinExchange& operator=(const BitcoinExchange& other) = default;
		~BitcoinExchange() = default;

		void	runBtc();
};
