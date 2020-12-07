#pragma once
//#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Payment/Payment.hpp"
#include <string>
#include <new>
#include <iostream>
#include <stdexcept>
#include <any>

class Amazon : public Payment
    {
    public:
        Amazon(std::string cardNum, int pin, std::string billAdd, int cost, std::string type = "Amazon")
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