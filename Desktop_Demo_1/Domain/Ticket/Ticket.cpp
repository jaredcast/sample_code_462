#include "Domain/Ticket/Ticket.hpp"
#include "Domain/Session/Session.hpp"

// This normally goes in the .cpp file ...
TicketFactory * TicketFactory::createFactory()
{ 
  // Read from configuration data what type of Tickets we want to create.  Let's
  // pretend a call to get the desired type of Ticket from the configuration
  // data returned "Plastic".  In particular, note that no data is passed into
  // the creatFactory function;
  std::string factoryPreference = "First Class Ticket";

  if      ( factoryPreference == "First Class Ticket" ) return new FirstClassFactory();
  //else if ( factoryPreference == "" )  return new Factory;
  else
  {
    // error - Preference not support.
    throw std::domain_error( "Unsupported factory preference encountered: " + factoryPreference );
  }
} // createFactory()

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