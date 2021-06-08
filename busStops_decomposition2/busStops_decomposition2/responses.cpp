//
//  responses.cpp
//  busStops_decomposition2
//
//  Created by Andre on 12/9/20.
//

#include "responses.h"
#include <iostream>

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
    if (r.exception) {
        os << "No stop";
    } else {
        for (const auto& bus : r.busesForThisStop) {
            os << bus << " ";
        }
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
    bool first = true;
    if (r.exception) {
        os << "No bus";
        return os;
    }
    for (int stop = 0; stop < r.stops.size(); ++stop) {
        if (!first) {
            os << std::endl;
            os << "Stop " << r.stops[stop] << ":";
            if (r.busesForTheStops[stop].size() == 0) {
                os << " no interchange";
            } else {
                for (int bus = 0; bus < r.busesForTheStops[stop].size(); ++bus) {
                    os << " " << r.busesForTheStops[stop][bus];
                }
            }
        } else {
            os << "Stop " << r.stops[stop] << ":";
            if (r.busesForTheStops[stop].size() == 0) {
                os << " no interchange";
            } else {
                for (int bus = 0; bus < r.busesForTheStops[stop].size(); ++bus) {
                    os << " " << r.busesForTheStops[stop][bus];
                }
            }
            first = false;
        }
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
    if (r.exception) {
        os << "No buses";
    } else {
        auto it = r.allBusesWithStops.begin();
        auto it_end = r.allBusesWithStops.end();
        it_end--;
        for (it; it != r.allBusesWithStops.end(); ++it) {
            os << "Bus " << it->first << ":";
            for (const auto& stop : it->second) {
                os << " " << stop;
            }
            if (it != it_end) {
                os << std::endl;
            }
        }
    }
    return os;
}
