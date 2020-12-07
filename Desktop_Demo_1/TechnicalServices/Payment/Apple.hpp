#pragma once
//#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Payment/Payment.hpp"
#include <string>
#include <new>
#include <iostream>
#include <stdexcept>
#include <any>

class Apple : public Payment
    {
    public:
        Apple(std::string cardNum, int pin, std::string billAdd, int cost, std::string type = "Apple")
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