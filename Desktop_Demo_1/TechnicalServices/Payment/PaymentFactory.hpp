#pragma once
//#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Payment/Payment.hpp"
#include "TechnicalServices/Payment/AppleFactory.hpp"
#include "TechnicalServices/Payment/AmazonFactory.hpp"
#include <string>
#include <new>
#include <iostream>
#include <stdexcept>
#include <any>



// Payment Abstract Factory Interface
struct PaymentFactory
{
    // Must be static
    static PaymentFactory* createFactory(std::string factoryPreference);

    // All Payment Factories have these functions
    virtual Payment* createPayment(std::string cardNum, int pin, std::string billAdd, int cost, std::string type) = 0;
};

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
};