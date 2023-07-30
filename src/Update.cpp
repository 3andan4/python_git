/*
** EPITECH PROJECT, 2023
** giti
** File description:
** FetchUpdate.cpp
*/

#include "Update.hpp"

int daysSince(const std::string& dateStr) {
    std::time_t t = std::time(0);
    std::tm* today = std::localtime(&t);

    std::tm inputDate = {};
    std::istringstream dateStream(dateStr);
    dateStream >> std::get_time(&inputDate, "%d/%m/%Y");

    if (dateStream.fail()) {
        throw std::runtime_error("Failed to parse date string");
        return -1;
    }

    std::time_t t1 = std::mktime(today);
    std::time_t t2 = std::mktime(&inputDate);

    double difference = std::difftime(t2, t1);

    int daysDiff = static_cast<int>(difference / (60 * 60 * 24));

    return daysDiff;
}

Version::Version(std::string vers) {
    std::vector<std::string> splitted;
    std::stringstream ss(vers);
    std::string token;
    while (std::getline(ss, token, '.'))
        splitted.push_back(token);
    if (splitted.size() != 4)
        throw GitiException(2);
    this->build = std::stoi(splitted[0]);
    this->major = std::stoi(splitted[1]);
    this->minor = std::stoi(splitted[2]);
    this->patch = std::stoi(splitted[3]);
}

Date::Date(std::string date) {
    std::vector<std::string> splitted;
    std::stringstream ss(date);
    std::string token;
    while (std::getline(ss, token, '/'))
        splitted.push_back(token);
    if (splitted.size() != 3)
        throw GitiException(2);
    this->day = std::stoi(splitted[0]);
    this->month = std::stoi(splitted[1]);
    this->year = std::stoi(splitted[2]);
}

Changelog::Changelog(std::string d_cont, bool is_file)
{
    std::string content;
    if (!is_file)
        content = d_cont;
    else {
        std::ifstream ifs(d_cont);
        if (!ifs.is_open())
            throw GitiException(3);
        content = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        ifs.close();
    }
    _data.Parse(content.c_str());
    if (_data.HasParseError())
        throw GitiException(4);
    _currentVersion = Version(_data["version"].GetString());
    _lastUpdateDate = Date(_data["date"].GetString());
    _LUCDate = Date(_data["LUC"].GetString());
    std::time_t t = std::time(0);
    std::tm* today = std::localtime(&t);
    _today = Date(today->tm_mday, today->tm_mon + 1, today->tm_year + 1900);
    _updatedSince = _today.dayDiff(_LUCDate);
}

void Changelog::display() {
    std::cout << "Current version: " << _currentVersion.__str__() << std::endl;
    std::cout << "Last update: " << _lastUpdateDate.__str__() << std::endl;
    std::cout << "Last update check: " << _LUCDate.__str__() << std::endl;
    std::cout << "Updated since last check: " << _updatedSince << " days" << std::endl;
}
