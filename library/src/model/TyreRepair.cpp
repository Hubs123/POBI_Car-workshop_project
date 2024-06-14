#include <string>
#include "model/TyreRepair.h"

double TyreRepair::getActualPrice() {
    if (tyreSize <=14 && tyreSize > 0)
        return Repair::getBasePrice();
    else if (tyreSize>14 && tyreSize<=18)
        return Repair::getBasePrice()*1.1;
    else
        return Repair::getBasePrice()*1.2;
}

std::string TyreRepair::getInfo() {
    return Repair::getInfo() + " tyre size: " + std::to_string(tyreSize) + " price: " + std::to_string(getActualPrice());
}

TyreRepair::TyreRepair(double basePrice, const std::string &name, int id, int tyreSize) : Repair(basePrice, name, id),
                                                                                          tyreSize(tyreSize) {}

TyreRepair::~TyreRepair() = default;
