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
    Ticket(int flightNum, int seatNum, std::string origin, std::string destination, std::string deptDate, int bags, double price)
    : _flightNum(flightNum), _seatNum(seatNum), _origin(origin), _destination(destination), _deptDate(deptDate), _bags(bags), _price(price)
    {}

    virtual void open() = 0;

    virtual ~Ticket()     = 0; // force the class to be abstract

  protected:
      int _flightNum;
      int _seatNum;
      std::string _origin;
      std::string _destination;
      std::string _deptDate;
      int _bags;
      double _price;
};

inline Ticket::~Ticket()
{}

// LA to Paris Ticket Concrete Product
class LAtoParisTicket : public Ticket
{
  public:
    LAtoParisTicket(int flightNum = 1, int seatNum = 1, std::string origin = "Los Angeles", std::string destination = "Paris", std::string deptDate = "12/01/2019", int bags = 2, double price = 1000)
    : Ticket(flightNum, seatNum, origin, destination, deptDate, bags, price)
    {
      std::cout << "Created LA to Paris Ticket number " << (_TicketID = ++_counter) << '\n';
    }

    void open() override
    {}

    ~LAtoParisTicket() override
    {
      std::cout << "Destroyed LA to Paris Ticket number " << _TicketID << '\n';
    }

  private:
    static long unsigned _counter; // class attribute to count the number of wooden Ticket made
    long unsigned        _TicketID = 0;
};
long unsigned LAtoParisTicket::_counter = 0; // Allocate storage for class attribute

/*******************************************************************************
**          TICKET FACTORIES
*******************************************************************************/
// Ticket Abstract Factory Interface
struct TicketFactory
{
  // Must be static
  static TicketFactory * createFactory();

  // All Ticket Factories have these functions
  virtual Ticket * createTicket(int flightNum, int seatNum, std::string origin, std::string destination, std::string deptDate, int bags, double price) = 0;
};


// Carpenter Concrete Factory
struct LAtoParisFactory : TicketFactory
{
  // Note:  Responsibility to delete this object passes to the caller
  //        Smart pointers would be a great idea here
  // Note the covariant return type!
  LAtoParisTicket * createTicket(int flightNum, int seatNum, std::string origin, std::string destination, std::string deptDate, int bags, double price) override
  { return new LAtoParisTicket(flightNum, seatNum, origin, destination, deptDate, bags, price); }
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