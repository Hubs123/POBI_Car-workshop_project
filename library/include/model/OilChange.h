#ifndef CARSERVICE_OILCHANGE_H
#define CARSERVICE_OILCHANGE_H

#include "EngineRepair.h"

enum OilType{
    mineral = 10,
    blended = 12,
    synthetic = 14
};

class OilChange : public EngineRepair {
    OilType oil;

public:
    OilChange(double basePrice, const std::string &name, int id, int engineAge, OilType oil);

    ~OilChange() override;

    double getActualPrice() override;

    std::string getInfo() override;
};

#endif //CARSERVICE_OILCHANGE_H
