#pragma once
#include <iostream>
#include <string>
#include <set>

namespace
{
    /*******************************************************************************
    **  Abstract Class  (Generalization)
    *******************************************************************************/
    class Ticket
    {
    public:
        virtual std::string getDetails() const = 0;
        virtual std::string type() const = 0;
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
        FirstClass(const std::string& name = "First Class:")
            : Ticket(this), _name(name)
        {}

        std::string getDetails() const override
        {
            return _name + type() + price();
        }

        std::string type() const override
        {
            return "\n\tFirst Class, ";
        }

        std::string price() const override
        {
            return "$500";
        }

        virtual ~FirstClass()
        {}

    private:
        std::string _name;
    };

    class BusinessClass : public Ticket
    {
    public:
        BusinessClass(const std::string& name = "Business Class: ")
            : Ticket(this), _name(name)
        {}

        std::string getDetails() const override
        {
            return _name + type() + price();
        }

        std::string type() const override
        {
            return "\n\tBusiness Class, ";
        }

        std::string price() const override
        {
            return "$250";
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

        std::string getDetails() const override
        {
            return _name + type() + price();
        }

        std::string type() const override
        {
            return "\n\tEcoonomy Class, ";
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
    // Passing by reference (vice value) is imperative!!  Pass by reference either by reference (&) or by pointer (*)
    std::string displayTicket(const Ticket& ticket)
    {
        return ticket.getDetails();
    }
}

/*#include "Domain/Session/Session.hpp"
#include <string>
#include <any>
#include <new>
#include <iostream>
#include <stdexcept>
*/
/*******************************************************************************
**          TICKETS
*******************************************************************************/
// Ticket Abstract Product Interface
/*class Ticket
{
  public:
    Ticket(std::string type, double price)
    : _type(type), _price(price)
    {}

    virtual void open() = 0;

    virtual ~Ticket()     = 0; // force the class to be abstract

  protected:
      std::string _type;
      double _price;
};

inline Ticket::~Ticket()
{}

// First Class Ticket Concrete Product
class FirstClassTicket : public Ticket
{
  public:
    FirstClassTicket(std::string type = "First Class", double price = 1000)
    : Ticket(type, price)
    {
      std::cout << "Created First Class Ticket number " << (_TicketID = ++_counter) << '\n';
    }

    void open() override
    {}

    ~FirstClassTicket() override
    {
      std::cout << "Destroyed First Class Ticket number " << _TicketID << '\n';
    }

  private:
    static long unsigned _counter; // class attribute to count the number of wooden Ticket made
    long unsigned        _TicketID = 0;
};
long unsigned FirstClassTicket::_counter = 0; // Allocate storage for class attribute

// First Class Ticket Concrete Product
class BusinessClassTicket : public Ticket
{
public:
    BusinessClassTicket(std::string type = "Business Class", double price = 750)
        : Ticket(type, price)
    {
        std::cout << "Created Business Class Ticket number " << (_TicketID = ++_counter) << '\n';
    }

    void open() override
    {}

    ~BusinessClassTicket() override
    {
        std::cout << "Destroyed Business Class Ticket number " << _TicketID << '\n';
    }

private:
    static long unsigned _counter; // class attribute to count the number of wooden Ticket made
    long unsigned        _TicketID = 0;
};
long unsigned BusinessClassTicket::_counter = 0; // Allocate storage for class attribute
*/
/*******************************************************************************
**          TICKET FACTORIES
*******************************************************************************/
// Ticket Abstract Factory Interface
/*
struct TicketFactory
{
  // Must be static
  static TicketFactory * createFactory();

  // All Ticket Factories have these functions
  virtual Ticket * createTicket(std::string type, double price) = 0;
};


// Carpenter Concrete Factory
struct FirstClassFactory : TicketFactory
{
  // Note:  Responsibility to delete this object passes to the caller
  //        Smart pointers would be a great idea here
  // Note the covariant return type!
  FirstClassTicket * createTicket(std::string type, double price) override
  { return new FirstClassTicket(type, price); }
};

struct BusinessFactory : TicketFactory
{
    // Note:  Responsibility to delete this object passes to the caller
    //        Smart pointers would be a great idea here
    // Note the covariant return type!
    BusinessClassTicket* createTicket(std::string type, double price) override
    {
        return new BusinessClassTicket(type, price);
    }
};
*/
/*          How to use          */
/*******************************************************************************
**          Clients
*******************************************************************************/
/*
int main()
{
  // I'd like a new Ticket, please.  Let's ask for one and let the system's configuration data 
  // pick the material.
  // Note the assignment of a pointer-to-concrete class to a pointer-to-interface class

  TicketFactory * theFactory = TicketFactory::createFactory();
  
  // Surprise!  I got a new Ticket but never said what kind I wanted
  Ticket        * myNewTicket = theFactory->createTicket(1, 1, "Los Angeles", "Paris", "12/01/2019", 2, 1000);

  myNewTicket->open();

  // Bookkeeping to be done - could avoid if we used smart pointers!
  delete myNewTicket;
  delete theFactory;
}
*/