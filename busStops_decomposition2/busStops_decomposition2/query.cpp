//
//  query.cpp
//  busStops_decomposition2
//
//  Created by Andre on 12/9/20.
//

#include "query.h"

std::istream& operator >> (std::istream& is, Query& q) {
    // Реализуйте эту функцию
        std::string nb;
        is >> nb;
        if (nb == "NEW_BUS") {
            q.type = QueryType::NewBus;
            int stop_count;
            is >> q.bus;
            is >> stop_count;
            std::vector<std::string> stops;
            for (size_t i = 0; i < stop_count; ++i) {
                is >> q.stop;
                stops.push_back(q.stop);
            }
            q.stops = stops;
        } else if (nb == "BUSES_FOR_STOP") {
            q.type = QueryType::BusesForStop;
            is >> q.stop;
        } else if (nb == "STOPS_FOR_BUS") {
            q.type = QueryType::StopsForBus;
            is >> q.bus;
        } else {
            q.type = QueryType::AllBuses;
        }
    return is;
}
