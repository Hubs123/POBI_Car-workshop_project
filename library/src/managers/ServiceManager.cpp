#include <stdexcept>
#include "managers/ServiceManager.h"
#include "model/Service.h"
#include "repositories/ServiceRepository.h"
#include <fstream>

ServiceManager::ServiceManager() {
    serviceRepository = std::make_shared<ServiceRepository>();
    serviceArchive = std::make_shared<ServiceRepository>();
}

ServiceManager::~ServiceManager() = default;

ServicePtr ServiceManager::registerService(int id, const pt::ptime &startTime, ClientPtr client, RepairPtr repair) {
    auto service = std::make_shared<Service>(id, startTime, client, repair);

    if(serviceRepository->findBy([id](const ServicePtr &ptr)->bool{
        return ptr->getID() == id;
    }).empty() && serviceArchive->findBy([id](const ServicePtr &ptr)->bool{
        return ptr->getID() == id;
    }).empty()) {
        serviceRepository->addService(service);

        std::string Path = "../../dysk/services";
        std::ofstream outFile(Path, std::ios_base::app);
        if (outFile.is_open()) {
            outFile << service->getInfo() << std::endl;
            outFile.close();
        } else {
            throw std::ios_base::failure("Nie mozna otworzyc pliku do zapisu.");
        }
    } else {
        throw std::logic_error("Service o podanym ID juz istnieje.");
    }

    return service;
}

void ServiceManager::unregisterService(const ServicePtr &Service) {
    if(serviceRepository->findBy([Service](const ServicePtr &ptr)->bool{
        return ptr == Service;
    }).empty()) {
        throw std::logic_error("Service nie istnieje");
    } else {
        serviceRepository->removeService(Service);
        serviceArchive->addService(Service);

        std::string path = "../../dysk/services";
        std::string path1 = "../../dysk/temp_services";
        std::string path2 = "../../dysk/services_archive";
        std::ifstream inFile(path);
        std::ofstream tempFile(path1);

        if (!inFile.is_open() || !tempFile.is_open()) {
            throw std::ios_base::failure("Nie mozna otworzyc pliku services do odczytu lub temp_services do zapisu.");
        }

        std::string line;
        bool removed = false;
        while (std::getline(inFile, line)) {
            if (line.find(Service->getInfo()) == std::string::npos) {
                tempFile << line << std::endl;
            } else {
                removed = true;
            }
        }

        inFile.close();
        tempFile.close();

        if (!removed) {
            throw std::logic_error("Nie znaleziono informacji o usuwanym kliencie w pliku services.");
        }

        inFile.open(path, std::ofstream::out | std::ofstream::trunc);
        inFile.close();

        inFile.open(path1);
        tempFile.open(path);

        if (!inFile.is_open() || !tempFile.is_open()) {
            throw std::ios_base::failure("Nie mozna otworzyc pliku services lub temp_services do zapisu.");
        }

        while (std::getline(inFile, line)) {
            tempFile << line << std::endl;
        }

        inFile.close();
        tempFile.close();

        std::ofstream outFile(path2, std::ios_base::app);
        if (!outFile.is_open()) {
            throw std::ios_base::failure("Nie mozna otworzyc pliku services_archive do zapisu.");
        }
        outFile << Service->getInfo() << std::endl;
    }
}

ServicePtr ServiceManager::getService(const int &personalId) const {
    std::vector<ServicePtr> found = serviceRepository->findBy([personalId](const ServicePtr &ptr)->bool{
        return ptr->getID() == personalId;
    });
    if(found.empty()){
        throw std::logic_error("Nie znaleziono osoby o podanym ID");
    } else {
        return found[0];
    }
}

std::vector<ServicePtr> ServiceManager::findAllServices() const {
    return serviceRepository->findBy([](ServicePtr)->bool{
        return true;
    });
}

std::vector<ServicePtr> ServiceManager::findAllArchivedServices() const {
    return serviceArchive->findBy([](ServicePtr)->bool{
        return true;
    });
}
