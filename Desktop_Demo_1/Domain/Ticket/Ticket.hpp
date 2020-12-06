#pragma once
#include "Domain/Ticket/TicketHandler.hpp"
#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include <iostream>
#include <string>
#include <set>
#include <any>

namespace
{
    /*******************************************************************************
    **  Abstract Class  (Generalization)
    *******************************************************************************/
    class Ticket
    {
    public:
        virtual std::string getTicket() const = 0;
        virtual std::string price()      const = 0;

        static std::set<Ticket*>& entirePopulation()
        {
            return tickets;
        }

        virtual ~Ticket() = 0;

    protected:
        // Enable derived classes to register themselves into a collection of people
        Ticket(Ticket* ticket)
        {
            tickets.insert(ticket);
        }

        inline static std::set<Ticket*> tickets;
    };

    inline Ticket::~Ticket()
    {
        tickets.erase(this);
    }


    /*******************************************************************************
    **  Concrete Class  (Specialization)
    *******************************************************************************/
    class FirstClass : public Ticket
    {
    public:
        FirstClass(const std::string& name = "First Class")
            : Ticket(this), _name(name)
        {}

        std::string getTicket() const override
        {
            return _name + price();
        }

        std::string price() const override
        {
            return " [$500]";
        }

        virtual ~FirstClass()
        {}

    private:
        std::string _name;
    };

    class BusinessClass : public Ticket
    {
    public:
        BusinessClass(const std::string& name = "Business Class")
            : Ticket(this), _name(name)
        {}

        std::string getTicket() const override
        {
            return _name + price();
        }

        std::string price() const override
        {
            return " [$250]";
        }

        virtual ~BusinessClass()
        {}

    private:
        std::string _name;
    };

    /*class EconomyClass : public Ticket
    {
    public:
        BusinessClass(const std::string& name = "Economy Class: ")
            : Ticket(this), _name(name)
        {}

        std::string getTicket() const override
        {
            return _name + price();
        }

        std::string price() const override
        {
            return " for $200";
        }

        virtual ~EconomyClass()
        {}

    private:
        std::string _name;
    };*/

    /*******************************************************************************
    **  Code to the Interface
    *******************************************************************************/
    std::string displayClass(const std::string& ticket)
    {
        FirstClass fc;
        BusinessClass bc;
        //EconomyClass ec;
        if (ticket == "First Class")
        {
            return fc.getTicket();
        }
        else if (ticket == "Business Class")
        {
            return bc.getTicket();
        }
        else return ticket; //adjust this later?
        //else if (ticket == "Economy Class")
        //{
        //    return ec.getTicket();
        //}
    }
}