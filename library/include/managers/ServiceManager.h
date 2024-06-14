#ifndef CARSERVICE_SERVICEMANAGER_H
#define CARSERVICE_SERVICEMANAGER_H
#include "typedefs.h"
#include <string>
#include <vector>
#include <memory>
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;

class ServiceManager {
private:
    ServiceRepositoryPtr serviceRepository;
    ServiceRepositoryPtr serviceArchive;

public:
    ServiceManager();

    ~ServiceManager();

    ServicePtr registerService(int id, const pt::ptime &startTime, ClientPtr client, RepairPtr repair);

    void unregisterService(const ServicePtr &Service);

    [[nodiscard]] ServicePtr getService(const int &personalId) const;
    
    [[nodiscard]] std::vector<ServicePtr> findAllServices() const;

    [[nodiscard]] std::vector<ServicePtr> findAllArchivedServices() const;
};

#endif //CARSERVICE_SERVICEMANAGER_H
