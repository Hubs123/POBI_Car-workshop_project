#ifndef CARSERVICE_TYREREPAIR_H
#define CARSERVICE_TYREREPAIR_H

#include "Repair.h"

class
TyreRepair : public Repair {
private:
    int tyreSize;

public:
    TyreRepair(double basePrice, const std::string &name, int id, int tyreSize);

    ~TyreRepair() override;

    double getActualPrice() override;

    std::string getInfo() override;
};

#endif //CARSERVICE_TYREREPAIR_H
