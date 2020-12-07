#pragma once
//#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Payment/PaymentFactory.hpp"
#include "TechnicalServices/Payment/Payment.hpp"
#include "TechnicalServices/Payment/Apple.hpp"
#include <string>
#include <new>
#include <iostream>
#include <stdexcept>
#include <any>

struct AppleFactory : PaymentFactory
    {
        Apple* createPayment(std::string cardNum, int pin, std::string billAdd, int cost, std::string type) override
        {
            return new Apple(cardNum, pin, billAdd, cost, type);
        }
    };