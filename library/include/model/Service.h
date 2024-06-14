#ifndef PROJECT_SERVICE_H
#define PROJECT_SERVICE_H

#include <string>
#include <boost/date_time.hpp>
#include "Client.h"
#include "Repair.h"

namespace pt = boost::posix_time;
using namespace std;

class Service{
private:
    int ID;
    double serviceCost = 0.0;
    pt::ptime startTime;
    pt::ptime finishTime;
    ClientPtr client;
    RepairPtr repair;

public:
    Service(int id, const pt::ptime &startTime, ClientPtr client, RepairPtr repair);

    virtual ~Service();

    [[nodiscard]] string getInfo() const;

    [[nodiscard]] int getID() const;

    [[nodiscard]] double getServiceCost() const;

    [[nodiscard]] const pt::ptime &getStartTime() const;

    [[nodiscard]] const pt::ptime &getFinishTime() const;

    void setFinishTime(const pt::ptime &finishTime);
};

#endif //PROJECT_SERVICE_H
