/*
** EPITECH PROJECT, 2023
** giti
** File description:
** Update.hpp
*/

#ifndef GITI_UPDATE_HPP
    #define GITI_UPDATE_HPP
    #include "lib.pch"
    #include "GitiExceptions.hpp"
    class Date {
        public:
        Date(std::string);
        Date(int day, int month, int year) : day(day), month(month), year(year) {};
        Date() = default;
        ~Date() = default;
        bool operator==(const Date &rhs) const {
            return day == rhs.day &&
                   month == rhs.month &&
                   year == rhs.year;
        }
        bool operator!=(const Date &rhs) const {
            return !(rhs == *this);
        }
        bool operator<(const Date &rhs) const {
            if (day < rhs.day)
                return true;
            if (rhs.day < day)
                return false;
            if (month < rhs.month)
                return true;
            if (rhs.month < month)
                return false;
            return year < rhs.year;
        }
        bool operator>(const Date &rhs) const {
            return rhs < *this;
        }
        std::string __str__() const {
            return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
        }
        int dayDiff(const Date &rhs) const {
            int total_days = day + month * 30 + year * 365;
            int total_days_rhs = rhs.day + rhs.month * 30 + rhs.year * 365;
            return total_days - total_days_rhs;
        }
        int day;
        int month;
        int year;
    };
    class Version {
        public:
        Version(std::string);
        Version() = default;
        ~Version() = default;
        bool operator==(const Version &rhs) const { // equivalent of SameVersion
            return build == rhs.build &&
                   major == rhs.major &&
                   minor == rhs.minor &&
                   patch == rhs.patch;
        }
        bool operator!=(const Version &rhs) const { // equivalent of DifferentVersion
            return !(rhs == *this);
        }
        bool operator<(const Version &rhs) const { // equivalent of OlderVersion
            if (build < rhs.build)
                return true;
            if (rhs.build < build)
                return false;
            if (major < rhs.major)
                return true;
            if (rhs.major < major)
                return false;
            if (minor < rhs.minor)
                return true;
            if (rhs.minor < minor)
                return false;
            return patch < rhs.patch;
        }
        bool operator>(const Version &rhs) const { // equivalent of NewerVersion
            return rhs < *this;
        }
        std::string __str__() const {
            return std::to_string(build) + "." + std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch);
        }
        int build;
        int major;
        int minor;
        int patch;
    };
    /**
     * @brief Class representing a changelog - It will parse the changelog file and store the data in a JSON object
     */
    class Changelog {
    public:
        Changelog(std::string filename, bool is_file = true);
        Changelog(const Changelog &rhs) {
            std::string rhs_str = rhs._data.GetString();
            _data.Parse(rhs_str.c_str());
            _currentVersion = rhs._currentVersion;
            _lastUpdateDate = rhs._lastUpdateDate;
            _today = rhs._today;
            _LUCDate = rhs._LUCDate;
            _updatedSince = rhs._updatedSince;
        }
        ~Changelog() = default;
        void display();
        Changelog &operator=(const Changelog &rhs) {
            std::string rhs_str = rhs._data.GetString();
            if (this != &rhs) {
                _data.Parse(rhs_str.c_str());
                _currentVersion = rhs._currentVersion;
                _lastUpdateDate = rhs._lastUpdateDate;
                _today = rhs._today;
                _LUCDate = rhs._LUCDate;
                _updatedSince = rhs._updatedSince;
            }
            return *this;
        }
        Version _currentVersion;
    protected:
    rapidjson::Document _data;
    Date _lastUpdateDate;
    Date _today;
    Date _LUCDate;
    int _updatedSince;
    };

    class Update {
    public:
        Update(Changelog localChangelog, Changelog remoteChangelog): _localChangelog(localChangelog), _remoteChangelog(remoteChangelog) {};
        ~Update() = default;
        /**
         * @brief Fetch the remote changelog file to compare it with the local one
         * @warning This function will throw an exception if it can't fetch the remote changelog file
         */
        void fetchChangelog();
        /**
         * @brief Parse the remote changelog file
         * @warning This function will throw an exception if it can't parse the remote changelog file
         */
        void parseChangelog();
        /**
         * @brief Compare the local and remote changelog files to determine if an update is available
         * @warning This function will throw an exception if it can't compare the local and remote changelog files
         */
        void compareVersions();
        /**
         * @brief Update the local installation
         * @warning This function will throw an exception if it can't update the local installation
         */
        void update();
        Changelog _localChangelog;
        Changelog _remoteChangelog;
    };
#endif //GITI_UPDATE_HPP
