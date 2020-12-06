#pragma once
//#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Payment/Payment.cpp"
#include <string>
#include <new>
#include <iostream>
#include <stdexcept>
#include <any>

/*******************************************************************************
**          PAYMENTS
*******************************************************************************/
// Payment Abstract Product Interface
namespace {
    class Payment
    {
    public:
        Payment(int cardNum, int pin, std::string billAdd, int cost, std::string type)
            : _cardNum(cardNum), _pin(pin), _billAdd(billAdd), _cost(cost), _type(type)
        {}

        virtual void open() = 0;

        virtual ~Payment() = 0; // force the class to be abstract

    protected:
        int _cardNum;
        int _pin;
        std::string _billAdd;
        int _cost;
        std::string _type;
    };

    inline Payment::~Payment()
    {}

    // Visa Payment Concrete Product
    class Amazon : public Payment
    {
    public:
        Amazon(int cardNum, int pin, std::string billAdd, int cost, std::string type = "Amazon")
            : Payment(cardNum, pin, billAdd, cost, type)
        {
            std::cout << "Created Amazon Credit Card payment number " << (_paymentID = ++_counter) << '\n';
        }

        void open() override
        {}

        ~Amazon() override
        {
            std::cout << "Destroyed Amazon Credit Card payment number " << _paymentID << '\n';
        }

    private:
        static long unsigned _counter; // class attribute to count the number of wooden door made
        long unsigned        _paymentID = 0;
    };
    long unsigned Amazon::_counter = 0; // Allocate storage for class attribute

    // Credit Payment Concrete Product
    class Apple : public Payment
    {
    public:
        Apple(int cardNum, int pin, std::string billAdd, int cost, std::string type = "Apple")
            : Payment(cardNum, pin, billAdd, cost, type)
        {
            std::cout << "Created Apple Pay Credit Card payment number " << (_paymentID = ++_counter) << '\n';
        }

        void open() override
        {}

        ~Apple() override
        {
            std::cout << "Destroyed Apple Pay Credit Credit payment number " << _paymentID << '\n';
        }

    private:
        static long unsigned _counter; // class attribute to count the number of wooden door made
        long unsigned        _paymentID = 0;
    };
    long unsigned Apple::_counter = 0; // Allocate storage for class attribute

    /*
    // Credit Payment Concrete Product
    class MasterCard : public Payment
    {
    public:
        MasterCard(std::string type = "Master Card")
            : Payment(type)
        {
            std::cout << "Created Master Card Credi payment number " << (_paymentID = ++_counter) << '\n';
        }

        void open() override
        {}

        ~MasterCard() override
        {
            std::cout << "Destroyed Master Card Credit payment number " << _paymentID << '\n';
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
        static PaymentFactory* createFactory(std::string factoryPreference);

        // All Payment Factories have these functions
        virtual Payment* createPayment(int cardNum, int pin, std::string billAdd, int cost, std::string type) = 0;
    };

    // Visa Concrete Factory
    struct AmazonFactory : PaymentFactory
    {
        Amazon* createPayment(int cardNum, int pin, std::string billAdd, int cost, std::string type) override
        {
            return new Amazon(cardNum, pin, billAdd, cost, type);
        }
    };

    // Credit Concrete Factory
    struct AppleFactory : PaymentFactory
    {
        Apple* createPayment(int cardNum, int pin, std::string billAdd, int cost, std::string type) override
        {
            return new Apple(cardNum, pin, billAdd, cost, type);
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

    PaymentFactory * PaymentFactory::createFactory(std::string factoryPreference)
    {
        // Read from configuration data what type of doors we want to create.  Let's
        // pretend a call to get the desired type of door from the configuration
        // data returned "Plastic".  In particular, note that no data is passed into
        // the creatFactory function;
        //std::string factoryPreference = "Amazon";

        if (factoryPreference == "Amazon") return new AmazonFactory();
        else if (factoryPreference == "Apple")  return new AppleFactory();
        //else if (factoryPreference == "Master Card")  return new MasterCardFactory;
        else
        {
            // error - Preference not support.
            throw std::domain_error("Unsupported factory preference encountered: " + factoryPreference);
        }
    }
}
/*std::any displayPaymentType(Domain::Session::SessionHandler& session, const std::vector<std::string>& args)
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
}*/




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