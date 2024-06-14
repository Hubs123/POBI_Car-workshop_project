#include <string>
#include "model/Repair.h"
#include "model/EngineRepair.h"

EngineRepair::EngineRepair(double basePrice, const std::__cxx11::basic_string<char> &name, int id, int engineAge)
        : Repair(basePrice, name, id), engineAge(engineAge) {}

std::string EngineRepair::getInfo() {
    return Repair::getInfo() +" engine age: " + std::to_string(engineAge);
}

double EngineRepair::getActualPrice() {
    if (engineAge < 2000)
        return Repair::getBasePrice();
    else if (engineAge>=2000 && engineAge < 2010)
        return Repair::getBasePrice()*1.05;
    else if (engineAge>=2010 && engineAge < 2020)
        return Repair::getBasePrice()*1.1;
    else
        return Repair::getBasePrice()*1.2;
}

EngineRepair::~EngineRepair() = default;
