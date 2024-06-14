#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

#include <string>
#include "model/ClientType.h"
#include "typedefs.h"

using namespace std;

class Client{
private:
    string firstName;
    string lastName;
    int personalID;
    ClientTypePtr clientType;

public:
    [[nodiscard]] const int &getPersonalID() const;

    [[nodiscard]] const string &getLastName() const;

    [[nodiscard]] const string &getFirstName() const;

    void setFirstName(const string &ufirstName);

    void setLastName(const string &ulastName);

    void setClientType(const ClientTypePtr& clientType);

    [[nodiscard]] double applyDiscount(double price) const;

    virtual ~Client();

    Client(const string &firstName, const string &lastName, const int &personalId, const ClientTypePtr &clientType);

    [[nodiscard]] const ClientTypePtr &getClientType() const;

    string getClientInfo();
};

#endif //PROJECT_CLIENT_H
