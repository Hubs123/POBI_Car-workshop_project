#ifndef CARSERVICE_CLIENTREPOSITORY_H
#define CARSERVICE_CLIENTREPOSITORY_H

#include "typedefs.h"
#include "model/Client.h"
#include <vector>

class ClientRepository {
private:
    std::vector<ClientPtr> clients;

public:
    [[nodiscard]] const ClientPtr findByPersonalID(int id) const;

    void addClient(ClientPtr Client);

    void removeClient(ClientPtr Client);

    [[nodiscard]] unsigned int getSize() const;

    [[nodiscard]] std::vector<ClientPtr> findBy(ClientPredicate predicate) const;

    ClientRepository();

    virtual ~ClientRepository();
};

#endif //CARSERVICE_CLIENTREPOSITORY_H
