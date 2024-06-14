#ifndef CARSERVICE_CLIENTMANAGER_H
#define CARSERVICE_CLIENTMANAGER_H

#include "typedefs.h"
#include <string>
#include <vector>
#include <memory>


class ClientManager {
private:
    ClientRepositoryPtr clientRepository;
    ClientRepositoryPtr clientArchive;

public:
    ClientManager();

    ~ClientManager();

    ClientPtr registerClient(const std::string &firstNamee, const std::string &lastNamee, const int &personlID,  ClientTypePtr clientTypee);

    void unregisterClient(const ClientPtr &client);

    [[nodiscard]] ClientPtr getClient(const int &personalId) const;

    [[nodiscard]] std::vector<ClientPtr> findAllClients() const;

    [[nodiscard]] std::vector<ClientPtr> findAllArchivedClients() const;
};

#endif //CARSERVICE_CLIENTMANAGER_H
