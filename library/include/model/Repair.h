#ifndef PROJECT_REPAIR_H
#define PROJECT_REPAIR_H

#include <string>

class Repair{
private:
    double basePrice;
    std::string name;
    int id;

public:
    virtual std::string getInfo();

    virtual double getActualPrice() = 0;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] int getID() const;

    virtual ~Repair();

    Repair(double basePrice, std::string name, int id);

    [[nodiscard]] double getBasePrice() const;
};

#endif //PROJECT_REPAIR_H
