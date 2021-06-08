//
//  phone_number.cpp
//  phone_number
//
//  Created by Andre on 12/9/20.
//
#include <stdexcept>
#include "phone_number.h"

std::pair<std::string, std::string> ParseCountryCode(const std::string& number) {
    std::string result;
    size_t posFirstDash;
    std::string ex = "Not valid country code";
    if (number[0] != '+') {  // Если номер не начинается с "+", это невалидный номер
        throw std::invalid_argument(ex);
    } else {
        posFirstDash = number.find_first_of('-');
        if (posFirstDash == -1) {  // Дефиса не найдено
            throw std::invalid_argument(ex);
        }
        result = number.substr(1, posFirstDash - 1);
        if (!result.size()) {  // Код страны не может быт пустым
            throw std::invalid_argument(ex);
        }
    }
    std::string restOfNumber = number.substr(posFirstDash + 1);
    return {result, restOfNumber};
}

std::pair<std::string, std::string> ParseCityCodeAndLocalNumber(const std::string& number) {
    std::string cityCode;
    size_t posDash = number.find_first_of('-');
    std::string ex_city = "Not valid city code";
    std::string ex_localNum = "Not valid local number";
    if (posDash == -1) {  // Дефиса не найдено
        throw std::invalid_argument(ex_city);
    }
    cityCode = number.substr(0, posDash);
    if (!cityCode.size()) {  // Код города не может быть пустым
        throw std::invalid_argument(ex_city);
    }
    std::string localNumber = number.substr(posDash + 1);
    if (!localNumber.size()) {  // Номер не может быть пустым
        throw std::invalid_argument(ex_localNum);
    }
    return {cityCode, localNumber};
}


PhoneNumber::PhoneNumber(const std::string& international_number) {
    try {
        std::pair<std::string, std::string> countryCode_restOfNumber = ParseCountryCode(international_number);
        country_code_ = countryCode_restOfNumber.first;
        std::pair<std::string, std::string> cityCode_localNumber = ParseCityCodeAndLocalNumber(countryCode_restOfNumber.second);
        city_code_ = cityCode_localNumber.first;
        local_number_ = cityCode_localNumber.second;
    } catch (std::exception& ex) {
        throw;
    }
}

std::string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

std::string PhoneNumber::GetCityCode() const {
    return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}


