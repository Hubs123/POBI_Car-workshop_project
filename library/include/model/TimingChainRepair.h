#ifndef CARSERVICE_TIMINGCHAINREPAIR_H
#define CARSERVICE_TIMINGCHAINREPAIR_H

#include "EngineRepair.h"

class TimingChainRepair : public EngineRepair{

public:
    TimingChainRepair(double basePrice, const std::string &name, int id, int engineAge);

    ~TimingChainRepair() override;

    double getActualPrice() override;

    std::string getInfo() override;
};
#endif //CARSERVICE_TIMINGCHAINREPAIR_H
