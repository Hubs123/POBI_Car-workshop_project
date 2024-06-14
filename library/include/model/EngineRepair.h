#ifndef CARSERVICE_ENGINEREPAIR_H
#define CARSERVICE_ENGINEREPAIR_H

#include "Repair.h"

class EngineRepair : public Repair {
    int engineAge;

public:
    double getActualPrice() override;

    std::string getInfo() override;

    EngineRepair(double basePrice, const std::string &name, int id, int engineAge);

    ~EngineRepair() override;
};

#endif //CARSERVICE_ENGINEREPAIR_H
