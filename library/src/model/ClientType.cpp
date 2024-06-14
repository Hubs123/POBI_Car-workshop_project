#include "model/ClientType.h"

ClientType::~ClientType() = default;

double Default::applyDiscount(double price) const {
    return price;
}

std::string Default::getTypeInfo() const {
    return "Default";
}

double Silver::applyDiscount(double price) const {
    return price*0.95;
}

std::string Silver::getTypeInfo() const {
    return "Silver";
}

double Gold::applyDiscount(double price) const {
    return price * 0.9;
}

std::string Gold::getTypeInfo() const {
    return "Gold";
}

double Platinum::applyDiscount(double price) const {
    return price * 0.8;
}

std::string Platinum::getTypeInfo() const {
    return "Platinum";
}
