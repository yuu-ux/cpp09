#include "BitcoinRateDatabase.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

const char* BitcoinRateDatabase::DEFAULT_DATA_FILE_NAME = "data.csv";

BitcoinRateDatabase::BitcoinRateDatabase() {
    std::ifstream data(BitcoinRateDatabase::DEFAULT_DATA_FILE_NAME);
    if (!data) {
        throw std::runtime_error("Error: could not open file.");
    }

    std::string line;
    bool first_row = true;
    while (std::getline(data, line)) {
        // 1 行目はカラムのためスキップ
        if (first_row) {
            first_row = false;
            continue;
        }
        // date
        std::string::size_type date_pos = line.find(',');
        Date date(line.substr(0, date_pos));

        // value
        std::string value_str = line.substr(date_pos + 1);
        double value;
        std::stringstream ss(value_str);
        ss >> value;
        this->data[date.toInt()] = value;
    }
}

std::string BitcoinRateDatabase::toString() const {
    std::string response;
    response.assign("date exchange_rate\n");
    for (std::map<int, double>::const_iterator row = this->data.begin();
            row != this->data.end(); ++row) {
            response.append(util::to_string(row->first))
            .append(" ")
            .append(util::to_string(row->second))
            .append("\n");
    }
    return response;
}

BitcoinRateDatabase::~BitcoinRateDatabase() {}

const std::map<int, double>& BitcoinRateDatabase::getData() const { return this->data; }
