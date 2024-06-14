#include <string>
#include <utility>

#include "model/Service.h"

using namespace std;

Service::~Service() = default;

int Service::getID() const {
    return ID;
}

double Service::getServiceCost() const {
    return client->applyDiscount(repair->getActualPrice());
}

const pt::ptime &Service::getStartTime() const {
    return startTime;
}

const pt::ptime &Service::getFinishTime() const {
    return finishTime;
}

string Service::getInfo() const {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);
    stream << "ID: " << ID << ", service cost: " << getServiceCost();
    return stream.str();
}

Service::Service(int id, const pt::ptime &startTime, ClientPtr client, RepairPtr repair) : ID(id), startTime(startTime),
                                                                                                         client(std::move(client)),
                                                                                                         repair(std::move(repair)) {}

void Service::setFinishTime(const pt::ptime &finishTime) {
    Service::finishTime = finishTime;
}

