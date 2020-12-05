/*#include "TechnicalServices/Payment/Payment.hpp"

// This normally goes in the .cpp file ...
namespace {
    PaymentFactory * PaymentFactory::createFactory()
    {
        // Read from configuration data what type of doors we want to create.  Let's
        // pretend a call to get the desired type of door from the configuration
        // data returned "Plastic".  In particular, note that no data is passed into
        // the creatFactory function;
        std::string factoryPreference = "Visa";

        if (factoryPreference == "Visa") return new VisaFactory();
        else if (factoryPreference == "Credit")  return new CreditFactory;
        //else if (factoryPreference == "Master Card")  return new MasterCardFactory;
        else
        {
            // error - Preference not support.
            throw std::domain_error("Unsupported factory preference encountered: " + factoryPreference);
        }
    } // createFactory()
}*/