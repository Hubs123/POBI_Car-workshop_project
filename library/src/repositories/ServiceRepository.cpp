#include "repositories/ServiceRepository.h"

void ServiceRepository::addService(const ServicePtr& uService) {
    if(uService != nullptr) {
        Services.push_back(uService);
    }
}

void ServiceRepository::removeService(const ServicePtr& uService) {
    if(uService != nullptr) {
        for (int i = 0; i < Services.size(); i++) {
            if (Services[i] == uService) {
                Services.erase(Services.begin() + i);
            }
        }
    }
}

unsigned int ServiceRepository::getSize() const {
    return Services.size();
}

ServiceRepository::ServiceRepository() = default;

ServiceRepository::~ServiceRepository() = default;

std::vector<ServicePtr> ServiceRepository::findBy(const ServicePredicate& predicate) const {
    std::vector<ServicePtr> found;
    for (unsigned int i = 0; i < Services.size(); i++) {
        if (Services[i] != nullptr && predicate(Services[i])) {
            found.push_back(Services[i]);
        }
    }
    return found;
}