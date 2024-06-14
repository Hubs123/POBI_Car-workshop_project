#ifndef CARSERVICE_TYPEDEFS_H
#define CARSERVICE_TYPEDEFS_H

#include <memory>
#include <functional>

class Repair;
class Service;
class Client;
class ClientType;

class ClientRepository;
class ServiceRepository;

class ClientManager;
class ServiceManager;

typedef std::shared_ptr<Client> ClientPtr;
typedef std::shared_ptr<Service> ServicePtr;
typedef std::shared_ptr<Repair> RepairPtr;
typedef std::shared_ptr<ClientType> ClientTypePtr;

typedef std::shared_ptr<ClientRepository> ClientRepositoryPtr;
typedef std::shared_ptr<ServiceRepository> ServiceRepositoryPtr;


typedef std::shared_ptr<ClientManager> ClientManagerPtr;
typedef std::shared_ptr<ServiceManager> ServiceManagerPtr;

typedef std::function<bool(const ClientPtr&)> ClientPredicate;
typedef std::function<bool(const ServicePtr&)> ServicePredicate;


#endif //CARSERVICE_TYPEDEFS_H
