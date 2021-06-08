//
//  bus_manager.hpp
//  busStops_decomposition2
//
//  Created by Andre on 12/9/20.
//

#pragma once
#include "responses.h"

class BusManager {
public:
    void AddBus(const std::string& bus, const std::vector<std::string>& stops);
    BusesForStopResponse GetBusesForStop(const std::string& stop) const;
    StopsForBusResponse GetStopsForBus(const std::string& bus) const;
    AllBusesResponse GetAllBuses() const;
private:
    std::map<std::string, std::vector<std::string>> buses_to_stops;  // Ключ: автобус, значение: вектор остановок, через которые проходит данный автобус
    std::map<std::string, std::vector<std::string>> stops_to_buses;  // Ключ: остановка, значение: вектор автобусов, проходящих через данную остановку
};
