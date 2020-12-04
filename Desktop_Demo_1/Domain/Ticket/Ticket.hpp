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
        FirstClass(const std::string& name = "first class")
            : Ticket(this), _name(name)
        {}

        std::string getTicket() const override
        {
            return _name + price();
        }

        std::string price() const override
        {
            return " for $500.";
        }

        virtual ~FirstClass()
        {}

    private:
        std::string _name;
    };

    class BusinessClass : public Ticket
    {
    public:
        BusinessClass(const std::string& name = "business class")
            : Ticket(this), _name(name)
        {}

        std::string getTicket() const override
        {
            return _name + price();
        }

        std::string price() const override
        {
            return " for $250.";
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
            return "$200";
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
        //else if (ticket == "Economy Class")
        //{
        //    return ec.getTicket();
        //}
    }
    // Passing by reference (vice value) is imperative!!  Pass by reference either by reference (&) or by pointer (*)
    /*std::any displayTicket(Domain::Session::SessionHandler& session, const std::vector<std::string>& args)
    {
        FirstClass fc;
        BusinessClass bc;
        //EconomyClass ec;
        std::string results = "";
        const std::string classType = args[0];
        if (classType == "First Class") {
            results = fc.getTicket();
        }
        else if (classType == "Business Class") {
            results = bc.getTicket();
        }
        //else if (classType == "Economy Class") {
        //    results = ec.getTicket();
        //}

        return results;
    }
    */
}