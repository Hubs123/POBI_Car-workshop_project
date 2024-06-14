#include <stdexcept>
#include "managers/ClientManager.h"
#include "model/Client.h"
#include "repositories/ClientRepository.h"
#include <fstream>

ClientManager::ClientManager() {
    clientRepository = std::make_shared<ClientRepository>();
    clientArchive = std::make_shared<ClientRepository>();
}

ClientManager::~ClientManager() = default;

ClientPtr ClientManager::registerClient(const std::string &firstNamee, const std::string &lastNamee, const int &personlID,  ClientTypePtr clientTypee) {
    auto client = std::make_shared<Client>(firstNamee, lastNamee, personlID, clientTypee);

    if(clientRepository->findBy([personlID](const ClientPtr &ptr)->bool{
        return ptr->getPersonalID() == personlID;
    }).empty() && clientArchive->findBy([personlID](const ClientPtr &ptr)->bool{
        return ptr->getPersonalID() == personlID;
    }).empty()) {
        clientRepository->addClient(client);

        std::string Path = "../../dysk/clients";
        std::ofstream outFile(Path, std::ios_base::app);
        if (outFile.is_open()) {
            outFile << client->getClientInfo() << std::endl;
            outFile.close();
        } else {
            throw std::ios_base::failure("Nie mozna otworzyc pliku do zapisu.");
        }
    } else {
        throw std::logic_error("Klient o podanym ID juz istnieje");
    }

    return client;
}

void ClientManager::unregisterClient(const ClientPtr &client) {
    if(clientRepository->findBy([client](const ClientPtr &ptr)->bool{
        return ptr == client;
    }).empty()) {
        throw std::logic_error("Klient nie istnieje");
    } else {
        clientRepository->removeClient(client);
        clientArchive->addClient(client);

        std::string path = "../../dysk/clients";
        std::string path1 = "../../dysk/temp_clients";
        std::string path2 = "../../dysk/clients_archive";
        std::ifstream inFile(path);
        std::ofstream tempFile(path1);

        if (!inFile.is_open() || !tempFile.is_open()) {
            throw std::ios_base::failure("Nie mozna otworzyc pliku clients do odczytu lub temp_clients do zapisu.");
        }

        std::string line;
        bool removed = false;
        while (std::getline(inFile, line)) {
            if (line.find(client->getClientInfo()) == std::string::npos) {
                tempFile << line << std::endl;
            } else {
                removed = true;
            }
        }

        inFile.close();
        tempFile.close();

        if (!removed) {
            throw std::logic_error("Nie znaleziono informacji o usuwanym kliencie w pliku clients.");
        }

        inFile.open(path, std::ofstream::out | std::ofstream::trunc);
        inFile.close();

        inFile.open(path1);
        tempFile.open(path);

        if (!inFile.is_open() || !tempFile.is_open()) {
            throw std::ios_base::failure("Nie mozna otworzyc pliku clients lub temp_clients do zapisu.");
        }

        while (std::getline(inFile, line)) {
            tempFile << line << std::endl;
        }

        inFile.close();
        tempFile.close();

        std::ofstream outFile(path2, std::ios_base::app);
        if (!outFile.is_open()) {
            throw std::ios_base::failure("Nie mozna otworzyc pliku clients_archive do zapisu.");
        }
        outFile << client->getClientInfo() << std::endl;
    }
}

ClientPtr ClientManager::getClient(const int &personalId) const {
    std::vector<ClientPtr> found = clientRepository->findBy([personalId](const ClientPtr &ptr)->bool{
        return ptr->getPersonalID() == personalId;
    });
    if(found.empty()){
        throw std::logic_error("Nie znaleziono osoby o podanym ID");
    } else {
        return found[0];
    }
}

std::vector<ClientPtr> ClientManager::findAllClients() const {
    return clientRepository->findBy([](ClientPtr)->bool{
        return true;
    });
}

std::vector<ClientPtr> ClientManager::findAllArchivedClients() const {
    return clientArchive->findBy([](ClientPtr)->bool{
        return true;
    });
}