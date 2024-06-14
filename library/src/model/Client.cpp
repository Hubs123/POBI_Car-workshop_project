#include <string>

#include "model/Client.h"

using namespace std;

const int &Client::getPersonalID() const {
    return personalID;
}

const string &Client::getLastName() const {
    return lastName;
}

const string &Client::getFirstName() const {
    return firstName;
}

void Client::setFirstName(const string &ufirstName) {
    if (!ufirstName.empty()) {
        Client::firstName = ufirstName;
    }
}

void Client::setLastName(const string &ulastName) {
    if (!ulastName.empty()){
        Client::lastName = ulastName;
    }
}


void Client::setClientType(const ClientTypePtr& clientType) {
    if (clientType != nullptr){
        Client::clientType = clientType;
    }
}

double Client::applyDiscount(double price) const {
    return clientType->applyDiscount(price);
}

Client::~Client() = default;



Client::Client(const string &firstName, const string &lastName, const int &personalId,
               const ClientTypePtr &clientType) : firstName(firstName), lastName(lastName), personalID(personalId),

                                                  clientType(clientType) {}

const ClientTypePtr &Client::getClientType() const {
    return clientType;
}

string Client::getClientInfo() {
    return "CLient info: first name - " + firstName + ", last name - " + lastName + ", ID - " + to_string(personalID) + ", client type - " + clientType->getTypeInfo();
}
