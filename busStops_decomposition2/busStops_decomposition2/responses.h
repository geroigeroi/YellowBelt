//
//  responses.hpp
//  busStops_decomposition2
//
//  Created by Andre on 12/9/20.
//

#pragma once
#include <map>
#include <vector>
#include "query.h"

struct BusesForStopResponse {
    std::vector<std::string> busesForThisStop;
    bool exception = false;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    std::vector<std::string> stops;
    std::vector<std::vector<std::string>> busesForTheStops;
    bool exception = false;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> allBusesWithStops;
    bool exception = false;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
