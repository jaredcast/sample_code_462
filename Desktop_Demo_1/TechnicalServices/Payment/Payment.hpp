#pragma once
//#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include <string>
#include <new>
#include <iostream>
#include <stdexcept>
#include <any>

/*******************************************************************************
**          PAYMENTS
*******************************************************************************/
// Payment Abstract Product Interface
class Payment
{
public:
    Payment(std::string type)
        : _type(type)
    {}

    virtual void open() = 0;

    virtual ~Payment() = 0; // force the class to be abstract

protected:
    std::string _type;
};

inline Payment::~Payment()
{}

// Visa Payment Concrete Product
class Visa : public Payment
{
public:
    Visa(std::string type = "Visa")
        : Payment(type)
    {
        std::cout << "Created visa payment number " << (_paymentID = ++_counter) << '\n';
    }

    void open() override
    {}

    ~Visa() override
    {
        std::cout << "Destroyed visa payment number " << _paymentID << '\n';
    }

private:
    static long unsigned _counter; // class attribute to count the number of wooden door made
    long unsigned        _paymentID = 0;
};
long unsigned Visa::_counter = 0; // Allocate storage for class attribute

// Credit Payment Concrete Product
class Credit : public Payment
{
public:
    Credit(std::string type = "Credit")
        : Payment(type)
    {
        std::cout << "Created credit payment number " << (_paymentID = ++_counter) << '\n';
    }

    void open() override
    {}

    ~Credit() override
    {
        std::cout << "Destroyed credit payment number " << _paymentID << '\n';
    }

private:
    static long unsigned _counter; // class attribute to count the number of wooden door made
    long unsigned        _paymentID = 0;
};
long unsigned Credit::_counter = 0; // Allocate storage for class attribute

/*
// Credit Payment Concrete Product
class MasterCard : public Payment
{
public:
    MasterCard(std::string type = "Master Card")
        : Payment(type)
    {
        std::cout << "Created Master Card payment number " << (_paymentID = ++_counter) << '\n';
    }

    void open() override
    {}

    ~MasterCard() override
    {
        std::cout << "Destroyed Master Card payment number " << _paymentID << '\n';
    }

private:
    static long unsigned _counter; // class attribute to count the number of wooden door made
    long unsigned        _paymentID = 0;
};
long unsigned MasterCard::_counter = 0; // Allocate storage for class attribute
*/

/*******************************************************************************
**          PAYMENT FACTORIES
*******************************************************************************/
// Payment Abstract Factory Interface
struct PaymentFactory
{
    // Must be static
    static PaymentFactory* createFactory();

    // All Door Factories have these functions
    virtual Payment* createPayment(std::string type) = 0;
};

// Visa Concrete Factory
struct VisaFactory : PaymentFactory
{
    Visa* createPayment(std::string type) override
    {
        return new Visa(type);
    }
};

// Credit Concrete Factory
struct CreditFactory : PaymentFactory
{
    Credit* createPayment(std::string type) override
    {
        return new Credit(type);
    }
};

/*
// Master Card Concrete Factory
struct MasterCardFactory : PaymentFactory
{
    MasterCard* createPayment(std::string type) override
    {
        return new MasterCard(type);
    }
};
*/

std::any displayPaymentType(Domain::Session::SessionHandler& session, const std::vector<std::string>& args)
{
    Visa visa;
    Credit credit;
    //MasterCard mastercard;
    std::string results = "";
    const std::string paymentType = args[0];
    if (paymentType == "Visa") {
        visa.open();
    }
    else if (paymentType == "Credit") {
        credit.open();
    }
    //else if (paymentType == "Master Card") {
    //    mastercard.open();
    //}
    results = "\nEntered " + args[0] + " payment type.";
    return results;
}




/*******************************************************************************
**          Clients
*******************************************************************************/
/*
int main()
{
    // I'd like a new door, please.  Let's ask for one and let the system's configuration data 
    // pick the material.
    // Note the assignment of a pointer-to-concrete class to a pointer-to-interface class

    DoorFactory* theFactory = DoorFactory::createFactory();

    // Surprise!  I got a new door but never said what kind I wanted
    Door* myNewDoor = theFactory->createDoor(12, 1.5, 3.0);

    myNewDoor->open();

    // Bookkeeping to be done - could avoid if we used smart pointers!
    delete myNewDoor;
    delete theFactory;
}
*/