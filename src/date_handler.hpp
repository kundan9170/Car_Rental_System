#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <windows.h>
#include <chrono>
#include<ctime>
#include<thread>
#include <bits/stdc++.h>

using namespace std;

namespace dates {

    void waitForSeconds(int seconds) {
    auto start = std::chrono::steady_clock::now();
    auto end = start + std::chrono::seconds(seconds);

    while (std::chrono::steady_clock::now() < end) {
        // Do nothing, just wait
    }
}

   bool isValidDate(const std::string& inputDate) {
    std::istringstream dateStream(inputDate);
    char dash1, dash2;
    int year, month, day;

    // Attempt to extract year, month, and day
    dateStream >> year >> dash1 >> month >> dash2 >> day;

    // Check for extraction success and that the entire string was consumed
    if (dateStream.fail() || !dateStream.eof()) {
        return false;
    }

    // Check if dashes are in the correct positions
    if (dash1 != '-' || dash2 != '-') {
        return false;
    }

    // Validate year, month, and day ranges
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Additional date-specific validations can be added if needed

    return true;
}

    bool isLaterDate(const std::string& givenDate, const std::string& laterDate) {
            // Parse the date strings
            std::tm tmGiven = {};
            std::tm tmLater = {};

            std::istringstream ssGiven(givenDate);
            std::istringstream ssLater(laterDate);

            ssGiven >> std::get_time(&tmGiven, "%Y-%m-%d");
            ssLater >> std::get_time(&tmLater, "%Y-%m-%d");

            if (ssGiven.fail() || ssLater.fail()) {
                // Parsing failed
                return false;
            }

            // Convert to time_point
            auto timeGiven = std::chrono::system_clock::from_time_t(std::mktime(&tmGiven));
            auto timeLater = std::chrono::system_clock::from_time_t(std::mktime(&tmLater));

            // Compare the time_point values
            return timeLater > timeGiven;
}




    string addWeeksToDate(const string& inputDate, int numberOfWeeks) {
    // Parse the input date string
    tm dateInfo = {};
    istringstream iss(inputDate);
    iss >> get_time(&dateInfo, "%Y-%m-%d");

    // Convert tm structure to time_point
    chrono::system_clock::time_point currentDate = chrono::system_clock::from_time_t(mktime(&dateInfo));

    // Add the specified number of weeks
    currentDate += chrono::hours(24 * 7 * numberOfWeeks);

    // Convert the new time_point to tm structure
    time_t newDate_t = chrono::system_clock::to_time_t(currentDate);
    tm* newDate_tm = localtime(&newDate_t);

    // Format the new date
    ostringstream oss;
    oss << setfill('0') << setw(4) << newDate_tm->tm_year + 1900 << '-'
        << setw(2) << newDate_tm->tm_mon + 1 << '-'
        << setw(2) << newDate_tm->tm_mday;

    return oss.str();
}



    string getCurrentDateAsString() {
    // Get the current time point
    auto currentTime = chrono::system_clock::now();

    // Convert the time point to a time_t
    time_t currentTime_t = chrono::system_clock::to_time_t(currentTime);

    // Convert time_t to a local time structure
    tm* currentTime_tm = localtime(&currentTime_t);

    // Format the date
    ostringstream oss;
    oss << setfill('0') << setw(4) << currentTime_tm->tm_year + 1900 << '-'
        << setw(2) << currentTime_tm->tm_mon + 1 << '-'
        << setw(2) << currentTime_tm->tm_mday;

    return oss.str();
}
}