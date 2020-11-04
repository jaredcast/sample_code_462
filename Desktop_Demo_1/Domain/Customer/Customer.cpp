#include "Domain/Customer/Customer.hpp"
#include "Domain/Customer/CustomerHandler.hpp"
#include "Domain/Session/Session.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include <string>
#include <any>
#include <vector>

namespace  // anonymous (private) working area
{
    // 1)  First define all system events (commands, actions, requests, etc.)
    #define STUB(functionName)  std::any functionName( Domain::Session::Customer & /*session*/, const std::vector<std::string> & /*args*/ ) \
                              { return {}; }  // Stubbed for now

  std::vector<std::vector<std::string>> listOfFlights = { //used temporary until objects are implemented
      // Origin 0, Destination 1, Departure date 2, return date 3, Stops 4, Price 5, Trip 6, Weather 7, Status 8
      //COST WILL BE INDEX 5!!!
      //flightnum 9, seats 10, meals 11, bags 12
      {"Los Angeles", "Paris", "12/01/2019", "12/16/2019", "None", "$1000", "Round Trip,", "Sunny 73F", "Open", "1"},
      {"Los Angeles", "Paris", "12/01/2019", "12/16/2019", "Chicago", "$850", "Round Trip,", "Sunny 73F", "Open", "2"}
    };

  std::vector<std::vector<std::string>> bookedFlights = {};

  std::any hello(Domain::Session::SessionBase& session, const std::vector<std::string>& args) {
      std::string test = "This is a test function to rest the strings!!!!!";
      return test;
  }

  std::any searchFlight(Domain::Session::SessionBase & session, const std::vector<std::string> & args)
  { 
    const std::string origin = args[0];
    const std::string destination = args[1]; 
    const std::string dept = args[2];
    const std::string ret = args[3];
    std::string results = "";
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
        results.append(flight[x] + " ");
      }
      std::cout << "\n";
    }

    results.append(" returned to "+ session._credentials.userEmail);
    return results;
  }

  std::any bookFlight(Domain::Session::SessionBase & session, const std::vector<std::string> & args)
  {
    const int flightNum = std::stoi(args[0]); 
    const int seats = std::stoi(args[1]); 
    const int meals = std::stoi(args[2]); 
    const int bags = std::stoi(args[3]); 
    std::string results = "Flight number " + args[0] + " will be booked with " + args[1] + " seats, " + args[2] + " meals, and " + args[3] + " bags. ";

    //std::cout << "Flight number " << flightNum << " will be booked with " << 
    //seats << " seats, " << meals << " meals, and " << bags << "bags.\n"; //Add later on

    std::vector<std::string> bookedFlight;

    for (auto flight : listOfFlights) {
      if (flight[9] == args[0]) { 
        bookedFlight = flight;
        bookedFlights.push_back(flight);
        break;}
    }
    //std::vector<std::string> flightAndCost = { bookedFlight[9], bookedFlight[5]};
    results.append("Total cost: " + bookedFlight[5] + "\nPayment is required by " + session._credentials.userEmail);
    return results;
  }
  
   std::any showTickets(Domain::Session::SessionBase& session, const std::vector<std::string>& args)
    {
        const int flightNum = std::stoi(args[0]);
        std::string results = "Flight Not Found";
        for (auto flight : bookedFlights)
        {
            if (flight[9] == args[0])
            {
                results = "\n""Name: " + session._credentials.userEmail + "\n" +
                    "Departure Date: " + flight[2] + "      Departure From: " + flight[0] + "\n"
                    + "Destenation:  " + flight[1] + "             Stops: " + flight[4] + "\n"
                    + "Number of Seats: 1        Numbers of Meals: 1        Number of Bags: 1";
                break;
            }
        }
        return results;
    }


  std::any payCreditCard(Domain::Session::SessionBase& session, const std::vector <std::string > & args) {
    std::string results = "Flight number " + args[0] + " has been paid for by card number " + args[1] + ".";
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
