#ifndef CARSERVICE_CLIENTTYPE_H
#define CARSERVICE_CLIENTTYPE_H

#include <string>

class ClientType {
public:
    virtual std::string getTypeInfo() const = 0;

    virtual double applyDiscount(double price) const = 0;

    virtual ~ClientType();
};

class Default : public ClientType {
public:
    std::string getTypeInfo() const override;

    double applyDiscount(double price) const override;
};

class Silver : public ClientType {
public:
    std::string getTypeInfo() const override;

    double applyDiscount(double price) const override;
};

class Gold : public ClientType {
public:
    std::string getTypeInfo() const override;

    double applyDiscount(double price) const override;
};

class Platinum : public ClientType {
public:
    std::string getTypeInfo() const override;

    double applyDiscount(double price) const override;
};

#endif //CARSERVICE_CLIENTTYPE_H
