#include <string>
#include <utility>
#include "model/Repair.h"

std::string Repair::getInfo() {
    return "Id: " + std::to_string(id) + " name: " + name;
}

Repair::~Repair() = default;

double Repair::getBasePrice() const {
    return basePrice;
}

Repair::Repair(double basePrice, std::string name, int id) : basePrice(basePrice), name(std::move(name)), id(id) {}

const std::string &Repair::getName() const {
    return name;
}

int Repair::getID() const {
    return id;
}
