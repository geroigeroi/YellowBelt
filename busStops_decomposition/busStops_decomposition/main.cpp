//
//  main.cpp
//  busStops_decomposition
//
//  Created by  Mister on 01.12.2020.
//

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    // Реализуйте эту функцию
        std::string nb;
        is >> nb;
        if (nb == "NEW_BUS") {
            q.type = QueryType::NewBus;
            int stop_count;
            is >> q.bus;
            is >> stop_count;
            std::vector<string> stops;
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

struct BusesForStopResponse {
    std::vector<std::string> busesForThisStop;
    bool exception = false;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.exception) {
        os << "No stop";
    } else {
        for (const auto& bus : r.busesForThisStop) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    std::vector<std::string> stops;
    std::vector<std::vector<std::string>> busesForTheStops;
    bool exception = false;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
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

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> allBusesWithStops;
    bool exception = false;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
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


class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;  // Внесли для данного маршрута список его остановок
        for (const std::string& stop : stops) {
            stops_to_buses[stop].push_back(bus);  // Внесли для каждой остановки, что через неё проходит данный маршрут
        }
    }
    
    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse listBuses;
        if (!stops_to_buses.count(stop)) {
            listBuses.exception = true;
            return listBuses;
        }
        for (const string& bus : stops_to_buses.at(stop)) {
            listBuses.busesForThisStop.push_back(bus);
        }
        return listBuses;
    }
    
    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse listStopsForThisBus;
        if (buses_to_stops.count(bus) == 0) {
            listStopsForThisBus.exception = true;
            return listStopsForThisBus;
        }
        for (const std::string& stop : buses_to_stops.at(bus)) {
            listStopsForThisBus.stops.push_back(stop);
            std::vector<std::string> stopsForOneBus;
            for (const std::string& other_bus : stops_to_buses.at(stop)) {
                if (bus != other_bus) {
                    stopsForOneBus.push_back(other_bus);
                }
            }
            listStopsForThisBus.busesForTheStops.push_back(stopsForOneBus);
        }
        return listStopsForThisBus;
    }
    
    AllBusesResponse GetAllBuses() const {
        AllBusesResponse listAllBuses;
        if (buses_to_stops.empty()) {
            listAllBuses.exception = true;
            return listAllBuses;
        }
        for (const auto& bus_item : buses_to_stops) {
            std::vector<std::string> allStopsForTheBus;
            for (const std::string& stop : bus_item.second) {
                allStopsForTheBus.push_back(stop);
            }
            listAllBuses.allBusesWithStops[bus_item.first] = allStopsForTheBus;
        }
        return listAllBuses;
    }
private:
    std::map<std::string, std::vector<std::string>> buses_to_stops;  // Ключ: автобус, значение: вектор остановок, через которые проходит данный автобус
    std::map<std::string, std::vector<std::string>> stops_to_buses;  // Ключ: остановка, значение: вектор автобусов, проходящих через данную остановку
};

int main() {
    int query_count;
    Query q;
    cin >> query_count;
    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
      cin >> q;
      switch (q.type) {
      case QueryType::NewBus:
        bm.AddBus(q.bus, q.stops);
        break;
      case QueryType::BusesForStop:
        cout << bm.GetBusesForStop(q.stop) << endl;
        break;
      case QueryType::StopsForBus:
        cout << bm.GetStopsForBus(q.bus) << endl;
        break;
      case QueryType::AllBuses:
        cout << bm.GetAllBuses() << endl;
        break;
      }
    }
    return 0;
}
