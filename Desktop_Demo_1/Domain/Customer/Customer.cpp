#include "Domain/Customer/Customer.hpp"
#include "Domain/Customer/CustomerHandler.hpp"
#include "Domain/Ticket/TicketHandler.hpp"
#include "Domain/Meal/MealHandler.hpp"
#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Payment/PaymentHandler.hpp"
#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
    // 1)  First define all system events (commands, actions, requests, etc.)
    #define STUB(functionName)  std::any functionName( Domain::Session::Customer & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  std::vector<std::vector<std::string>> listOfFlights = { //used temporary until objects are implemented
      // Origin 0, Destination 1, Departure date 2, return date 3, Stops 4, Price 5, Trip 6, Weather 7, Status 8, flightnum 9, seats 10, meals 11, bags 12
      //COST WILL BE INDEX 5!!!
      // For the time being, this is hardcoded in
      {"Los Angeles", "Paris", "12/01/2019", "12/16/2019", "None", "$1000", "Round Trip,", "Sunny 73F", "Open", "1"},
      {"Los Angeles", "Paris", "12/01/2019", "12/16/2019", "Chicago", "$850", "Round Trip,", "Sunny 73F", "Open", "2"}
    };

  std::vector<std::vector<std::string>> bookedFlights = {};

  std::vector<std::vector<Ticket>> ticketList = {};
  //std::vector<std::string> mealList = {};
  std::vector<std::vector<Payment>> paymentList = {};
  std::string customerTicket = "";
  std::string customerMeal = "";
  int cSeat = 0;
  int cBags = 0;

  //This is a temporary function to test our changes in the code - was having problems building, will remove once it is fixed
  std::any hello(Domain::Session::SessionHandler& session, const std::vector<std::string>& args) { //Change the header here too!!!! 12/1/2020
      std::string test = "This is a test function to rest the string!";
      return test;
  }

  //Searches for a flight based off the criteria
  std::any searchFlight(Domain::Session::SessionHandler & session, const std::vector<std::string> & args) //With SessionHandler
  { 
    auto userCred = session.getCredentials();
    const std::string origin = args[0];
    const std::string destination = args[1]; 
    const std::string dept = args[2];
    const std::string ret = args[3];
    std::string results = "";
    std::vector<std::vector<std::string>> matchFlights;
    for (auto flight : listOfFlights) {
      bool oriCheck = flight[0] == origin;
      bool destinationCheck = flight[1] == destination;
      bool deptCheck = flight[2] == dept;
      bool returnCheck = flight[3] == ret;
      if (oriCheck == true && destinationCheck == true && deptCheck == true && returnCheck == true) { matchFlights.push_back(flight); }
    }
    std::cout << "\nList of flights matching your search filters: \n";
    if (matchFlights.size() == 0) { results.append( "None matched your parameters.\n");
                                    return results;}
    for (auto flight : matchFlights) {
      std::cout << "Flight #" << flight[9] << " ";
      for (int x = 0; x < flight.size(); x++) {
        std::cout << flight[x] << " ";
        results.append(flight[x] + " ");
      }
      std::cout << "\n";
    }

    results.append(" returned to "+ userCred.userEmail); //credentials is giving us a problem here. 
    return results;
  }

  //Books the flight with the provided flight number
  std::any bookFlight(Domain::Session::SessionHandler & session, const std::vector<std::string> & args) //With SessionBase
  {
    auto userCred = session.getCredentials();
    const int flightNum = std::stoi(args[0]); 
    const int seats = std::stoi(args[1]); 
    const std::string meals = (args[2]);
    const int bags = std::stoi(args[3]);
    const std::string classType = args[4];
    
    std::string results;

    std::vector<std::string> bookedFlight;
    bool foundFlight = false;

    if (displayMeal(meals) == "Error") {
      results = "Error, invalid meal requested.";
      return results;
    }

    for (auto flight : listOfFlights) {
      if (flight[9] == args[0]) { 
        foundFlight = true;
        bookedFlight = flight;
        bookedFlights.push_back(flight);
        break;}
    }

    if (foundFlight) {
       results = "Flight number " + args[0] + " will be booked with " + args[1] + " seat(s), with a " + displayMeal(meals) + ", " + args[3] + " bag(s). The ticket type is " + displayClass(classType) + ".";
       //ticketList.push_back(classType); For now we are only keeping track of one ticket and one meal.
      //mealList.push_back(meals);
      customerMeal = meals;
      customerTicket = classType;
      cSeat = seats;
      cBags = bags;

      results.append("\nPayment is required by " + userCred.userEmail); //fix credentials
      return results;
    }
    else {
      results = "Error, no flights found with flight number " + args[0];
      return results;
    }
    
  }
  
  //Shows the ticket the customer has purchased - fix later   
  std::any showTickets(Domain::Session::SessionHandler & session, const std::vector<std::string> & args)
  {
      auto userCred = session.getCredentials();
      const int flightNum = std::stoi(args[0]);
      std::string results = "Flight Not Found";
      for (auto flight : bookedFlights)
      {
          if (flight[9] == args[0])
          {
              results = "\n""Name: " + userCred.userEmail + "\n" + //fix credentials
                  "Departure Date: " + flight[2] + "      Departure From: " + flight[0] + "\n"
                  + "Destenation:  " + flight[1] + "             Stops: " + flight[4] + "\n"
                  + "Number of Seats: " + std::to_string(cSeat) + "            Meal: " + displayMeal(customerMeal) + "      Number of Bags: " + std::to_string(cBags)
                  + "      Ticket Type: " + displayClass(customerTicket);
              break;
          }
      }
      return results;
  }

  //Pay with a credit card
  std::any payCreditCard(Domain::Session::SessionHandler& session, const std::vector <std::string > & args) {
    int flightNum = stoi(args[0]);
    std::string cardNum = args[1];
    int pin = stoi(args[2]);
    std::string billAdd = args[3];
    int cost = stoi(args[4]);
    std::string cardType = args[5];

    std::vector<std::string> tempFlight = listOfFlights[flightNum];
    PaymentFactory* theFactory = PaymentFactory::createFactory(args[5]);
    Payment* myNewPayment = theFactory->createPayment(cardNum, pin, billAdd, cost, cardType); 
    myNewPayment->open(); //In domain layer, call createPayment factory function inside paymentHandler interface/ like UI layer calling createSession
    //paymentList.push_back(myNewPayment);
    std::string results = "Flight number " + args[0] + " has been paid for by card number " + args[1] + ". Total cost: " + args[4] + ". Paid for with: " + args[5];

    return results;
  }

}    // anonymous (private) working area

//Backup 
/*std::vector<std::vector<std::string>> listOfFlights = { //used temporary until objects are implemented
      // Origin 0, Destination 1, Departure date 2, return date 3, Stops 4, Price 5, Trip 6, Weather 7, Status 8
      //COST WILL BE INDEX 5!!!
      //flightnum 9, seats 10, meals 11, bags 12
      {"Los Angeles", "Paris", "12-01-2019", "12-16-2019", "None", "$1000", "Round Trip,", "Sunny 73F", "Open", "1"},
      {"Los Angeles", "Paris", "12-01-2019", "12-16-2019", "Chicago", "$850", "Round Trip,", "Sunny 73F", "Open", "2"}
    };

  std::vector<std::vector<std::string>> bookedFlights;

  std::any searchFlight(Domain::Customer::Customer & session, const std::vector<std::string> & args)
  {
    const std::string origin = args[0];
    const std::string destination = args[1];
    const std::string dept = args[2];
    const std::string ret = args[3];
    std::vector<std::vector<std::string>> matchFlights;
    for (auto flight : listOfFlights) {
      bool oriCheck = (std::find(flight.begin(), flight.end(), origin) != flight.end());
      bool destinationCheck = (std::find(flight.begin(), flight.end(), destination) != flight.end());
      bool deptCheck = (std::find(flight.begin(), flight.end(), dept) != flight.end());
      bool retCheck = (std::find(flight.begin(), flight.end(), ret) != flight.end());
      if (oriCheck && destinationCheck && deptCheck && retCheck) { matchFlights.push_back(flight); }
    }
    std::cout << "\nList of flights matching your search filters: \n";
    for (auto flight : matchFlights) {
      std::cout << "Flight #" << flight[9] << " ";
      for (int x = 0; x < flight.size(); x++) {
        std::cout << flight[x] << " ";
      }
      std::cout << "\n";
    }

    std::string results = "Flights returned to " + session._credentials.userEmail;
    return results;
  }

  std::any bookFlight(Domain::Customer::Customer & session, const std::vector<std::string> & args)
  {
    const int flightNum = std::stoi(args[0]);
    const int seats = std::stoi(args[1]);
    const int meals = std::stoi(args[2]);
    const int bags = std::stoi(args[3]);

    std::cout << "Flight number " << flightNum << " will be booked with " <<
    seats << " seats, " << meals << " meals, and " << bags << "bags.\n"; //Add later on

    std::vector<std::string> bookedFlight;

    for (auto flight : listOfFlights) {
      if (flight[9] == args[0]) {
        bookedFlight = flight;
        break;}
    }


    std::vector<std::string> flightAndCost = { bookedFlight[9], bookedFlight[5]};
    std::string results = "System responding with flight number " + bookedFlight[9] + " and total cost of " + bookedFlight[5] +
    " to " + session._credentials.userEmail;
    return results;
  }

  std::any showTickets(Domain::Customer::Customer& session, const std::vector<std::string>& args)
  {
      const int flightNum = std::stoi(args[0]);
      std::string results = "Flight Not Found";
      for (auto flight : bookedFlights)
      {
          if (flight[9] == args[0])
          {
              results = "Name: " + session._credentials.userEmail + "\n"+"Departure Date: "+ flight[2]+
                  "      Departure From: "+ flight[0]+"\n"+"Stops: "+ flight[4]+"\n";
              break;
          }
      }
      return results;
  }

  std::any payWithCreditCard( Domain::Customer::Customer & session, const std::vector<std::string> & args )
  {
    // TO-DO  Verify there is such a book and the mark the book as being checked out by user
    int flightNum = std::stoi(args[0]);
    int cost = std::stoi(args[1]);
    int cardNum = std::stoi(args[2]);
    int pin = std::stoi(args[3]);
    std::string name = args[4];
    std::string billAddress = args[5];


    std::cout<< "Receipt: Paid " << cost << " for flight with card number " + cardNum;
    std::cout << "Flight info: "; //print according to flightNum
    std::string results = "payWithCreditCard: Receipt, ticket, flight info, email sent to" + session._credentials.userEmail;

    session._logger << "payWithCreditCard: " + results;
    return results; //fix this
  }

}    // anonymous (private) working area

namespace Domain::Customer
{
  Customer::Customer( const std::string & description, const UserCredentials & credentials ) : _credentials( credentials ), _name( description )
  {
    _logger << "Session \"" + _name + "\" being used and has been successfully initialized";
  }

  Customer::~Customer() noexcept
  {
    _logger << "Session \"" + _name + "\" shutdown successfully";
  }

  std::vector<std::string> Customer::getCommands()
  {
    std::vector<std::string> availableCommands;
    availableCommands.reserve( _commandDispatch.size() );

    for( const auto & [command, function] : _commandDispatch ) availableCommands.emplace_back( command );

    return availableCommands;
  }

  //Gets the string as the command, gets arguments as second parameter.
  //Convert string to a function, find the function that goes with it. commandDispatch.find

  std::any Customer::executeCommand( const std::string & command, const std::vector<std::string> & args )
  {
    std::string parameters;
    for( const auto & arg : args )  parameters += '"' + arg + "\"  ";
    _logger << "Responding to \"" + command + "\" request with parameters: " + parameters;

    auto it = _commandDispatch.find( command );
    if( it == _commandDispatch.end() )
    {
      std::string message = __func__;
      message += " attempt to execute \"" + command + "\" failed, no such command";

      _logger << message;
      throw BadCommand( message );
    }

    auto results = it->second( *this, args);

    if( results.has_value() )
    {
      // The type of result depends on function called.  Let's assume strings for now ...
      _logger << "Responding with: \"" + std::any_cast<const std::string &>( results ) + '"';
    }

    return results;
  }*/

  // CustomerSession::CustomerSession( const UserCredentials & credentials ) : Customer( "Customer", credentials )
  // {
  //   _commandDispatch = { {"Search Flight", searchFlight},
  //                       {"Book Flight", bookFlight},
  //                       {"Show Ticket", showTickets},
  //                       {"Pay With Credit Card", payWithCreditCard} };
  //                       //Second argument, 
  // }
  // 
