#include <string>
#include "model/EngineRepair.h"
#include "model/TimingChainRepair.h"

TimingChainRepair::TimingChainRepair(double basePrice, const std::__cxx11::basic_string<char> &name, int id,
                                     int engineAge) : EngineRepair(basePrice, name, id, engineAge) {}

double TimingChainRepair::getActualPrice() {
    return EngineRepair::getActualPrice();
}

std::string TimingChainRepair::getInfo() {
    return EngineRepair::getInfo();
}

TimingChainRepair::~TimingChainRepair() = default;
