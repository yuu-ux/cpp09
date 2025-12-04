#pragma once

#include <map>
#include "Date.h"

class BitcoinRateDatabase {
    private:
        static const char* DEFAULT_DATA_FILE_NAME;

        std::map<int, double> data;

    public:
        BitcoinRateDatabase();
        ~BitcoinRateDatabase();

        const std::map<int, double>& getData() const;
        std::string toString() const;

    private:
        BitcoinRateDatabase(const BitcoinRateDatabase& other);
        BitcoinRateDatabase& operator=(const BitcoinRateDatabase& rhs);
};
