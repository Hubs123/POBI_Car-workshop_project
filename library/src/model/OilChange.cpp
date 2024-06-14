#include <string>
#include "model/OilChange.h"

OilChange::OilChange(double basePrice, const std::__cxx11::basic_string<char> &name, int id, int engineAge, OilType oil)
        : EngineRepair(basePrice, name, id, engineAge), oil(oil) {}

double OilChange::getActualPrice() {
    return EngineRepair::getActualPrice()*(oil*0.1);
}

std::string OilChange::getInfo() {
    return EngineRepair::getInfo() + " oil type: " + std::to_string(oil);
}

OilChange::~OilChange() = default;
