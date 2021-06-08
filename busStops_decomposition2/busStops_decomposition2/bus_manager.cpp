//
//  bus_manager.cpp
//  busStops_decomposition2
//
//  Created by Andre on 12/9/20.
//

#include "bus_manager.h"
#include <string>
#include <map>
#include <vector>

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
    buses_to_stops[bus] = stops;  // Внесли для данного маршрута список его остановок
    for (const std::string& stop : stops) {
        stops_to_buses[stop].push_back(bus);  // Внесли для каждой остановки, что через неё проходит данный маршрут
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
    BusesForStopResponse listBuses;
    if (!stops_to_buses.count(stop)) {
        listBuses.exception = true;
        return listBuses;
    }
    for (const std::string& bus : stops_to_buses.at(stop)) {
        listBuses.busesForThisStop.push_back(bus);
    }
    return listBuses;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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
