#include "Domain/Session/Session.hpp"
#include <string>
#include <any>
#include <new>
#include <iostream>
#include <stdexcept>

/*******************************************************************************
**          TICKETSS
*******************************************************************************/
// Ticket Abstract Product Interface
class Ticket
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

/*******************************************************************************
**          TICKET FACTORIES
*******************************************************************************/
// Ticket Abstract Factory Interface
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