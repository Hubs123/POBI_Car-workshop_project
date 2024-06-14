#ifndef CARSERVICE_SERVICEREPOSITORY_H
#define CARSERVICE_SERVICEREPOSITORY_H

#include "typedefs.h"
#include "model/Service.h"
#include <vector>

class ServiceRepository {
private:
    std::vector<ServicePtr> Services;

public:
    void addService(const ServicePtr& uService);

    void removeService(const ServicePtr& uService);

    [[nodiscard]] unsigned int getSize() const;

    [[nodiscard]] std::vector<ServicePtr> findBy(const ServicePredicate& predicate) const;

    ServiceRepository();

    virtual ~ServiceRepository();
};

#endif //CARSERVICE_SERVICEREPOSITORY_H
