#include <ctime>
#include <sstream>
#include <string>
#include <iomanip>
#include "date.h"

Date::Date() {
    year_ = 0;
    month_ = 0;
    day_ = 0;
}

Date::Date(const std::string &input_date) {
    CheckFormat(input_date);
    CheckData();
}

int Date::GetYear() const { return year_; }

int Date::GetMonth() const { return month_; }

int Date::GetDay() const { return day_; }

Date& Date::operator=(const Date& rhs) {
    year_ = rhs.year_;
    month_ = rhs.month_;
    day_ = rhs.day_;
    return *this;
}

std::string Date::GetDate(char separator) const {
    std::stringstream so;
    so << std::setfill('0');
    if (year_ < 0) {
        so << '-';
    }
    so << std::setw(4) << abs(year_);
    so << separator;
    so << std::setw(2) << month_;
    so << separator;
    so << std::setw(2) << day_;
    return so.str();
}

time_t Date::AsTimestamp() const {
    std::tm t;
    t.tm_sec   = 0;
    t.tm_min   = 0;
    t.tm_hour  = 0;
    t.tm_mday  = day_;
    t.tm_mon   = month_ - 1;
    t.tm_year  = year_ - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
}

int Date::ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static const int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

void Date::CheckFormat(const std::string &input) {
    std::stringstream ss(input);
    int count_data = 3;
    int date_data[3] = {-1, -1, -1};
    year_ = date_data[0];
    month_ = date_data[1];
    day_ = date_data[2];

    if (!CheckNumber(ss, date_data[0])) {
        std::stringstream so;
        so << "Wrong date format: " << input;
        throw std::runtime_error(so.str());
    }

    char input_date_separator = '-';
    for (int i = 1; i < count_data; ++i) {
        if (ss.peek() != input_date_separator) {
            std::stringstream so;
            so << "Wrong date format: " << input;
            throw std::runtime_error(so.str());
        }
        else {
            ss.ignore(1);
            if (!CheckNumber(ss, date_data[i])) {
                std::stringstream so;
                so << "Wrong date format: " << input;
                throw std::runtime_error(so.str());
            }
        }
    }

    if (ss.rdbuf()->in_avail() != 0) {
        std::stringstream so;
        so << "Wrong date format: " << input;
        throw std::runtime_error(so.str());
    }
    year_ = date_data[0];
    month_ = date_data[1];
    day_ = date_data[2];
}

bool Date::CheckNumber(std::stringstream& ss, int& number) {
    char sign = '+';
    if (ss.peek() == '+' || ss.peek() == '-') {
        sign = ss.get();
    }
    if (ss.peek() >= '0' && ss.peek() <= '9') {
        ss >> number;
        if (sign == '-') {
            number = -number;
        }
    }
    else {
        return false;
    }
    return true;
}

void Date::CheckData() {
    if (month_ < 1 || month_ > 12) {
        std::stringstream ss;
        ss << "Month value is invalid: " << month_;
        throw std::runtime_error(ss.str());
    }

    if (day_ < 1 || day_ > 31) {
        std::stringstream ss;
        ss << "Day value is invalid: " << day_;
        throw std::runtime_error(ss.str());
    }
}

bool operator<(const Date& lhs, const Date& rhs) {
    int l_year = lhs.GetYear(), l_month = lhs.GetMonth(), l_day = lhs.GetDay();
    int r_year = rhs.GetYear(), r_month = rhs.GetMonth(), r_day = rhs.GetDay();
    return (std::tie(l_year, l_month, l_day) < std::tie(r_year, r_month, r_day));
}

bool operator==(const Date& lhs, const Date& rhs) {
    return (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay());
}