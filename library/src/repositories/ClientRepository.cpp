#include "repositories/ClientRepository.h"

const ClientPtr ClientRepository::findByPersonalID (int id) const {
    auto it = std::find_if(clients.begin(), clients.end(), [id](const ClientPtr& client) {
        return client->getPersonalID() == id;
    });
    if (it != clients.end()) {
        return *it;

    }
    return nullptr;
}

void ClientRepository::addClient(ClientPtr client) {
    if(client != nullptr) {
        clients.push_back(client);
    }
}

void ClientRepository::removeClient(ClientPtr client) {
    if(client != nullptr) {
        for (int i = 0; i < clients.size(); i++) {
            if (clients[i] == client) {
                clients.erase(clients.begin() + i);
            }
        }
    }
}

unsigned int ClientRepository::getSize() const {
    return clients.size();
}

ClientRepository::ClientRepository() {

}

ClientRepository::~ClientRepository() {
}

std::vector<ClientPtr> ClientRepository::findBy(ClientPredicate predicate) const {
    std::vector<ClientPtr> found;
    for (unsigned int i = 0; i < clients.size(); i++) {
        if (clients[i] != nullptr && predicate(clients[i])) {
            found.push_back(clients[i]);
        }
    }
    return found;
}

