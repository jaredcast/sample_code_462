#include "UI/SimpleUI.hpp"

#include <any>         // any_cast()
#include <iomanip>     // setw()
#include <iostream>    // streamsize
#include <limits>      // numeric_limits
#include <memory>      // unique_ptr, make_unique<>()
#include <string>      // string, getline()
#include <vector>

#include "Domain/Session/SessionHandler.hpp"
// #include "Domain/Ticket/TicketHandler.hpp"
// #include "Domain/Meal/MealHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"




namespace UI
{
  // Default constructor
  SimpleUI::SimpleUI()
  : //_flightHandler   ( std::make_unique<Domain::Library::Flights>()                     ),   // will replace these with factory calls in the next increment
    _loggerPtr     ( TechnicalServices::Logging::LoggerHandler::create()            ),
    _persistentData( TechnicalServices::Persistence::PersistenceHandler::instance() )
  {
    _logger << "Simple UI being used and has been successfully initialized";
  }




  // Destructor
  SimpleUI::~SimpleUI() noexcept
  {
    _logger << "Simple UI shutdown successfully";
  }




  // Operations
  void SimpleUI::launch()
  {
    // 1) Fetch Role legal value list
    std::vector<std::string> roleLegalValues = _persistentData.findRoles();


    // 2) Present login screen to user and get username, password, and valid role
    Domain::Session::UserCredentials credentials  = {"", "", {""}};           // ensures roles[0] exists
    auto &                           selectedRole = credentials.roles[0];     // convenience alias

    std::unique_ptr<Domain::Session::SessionHandler> sessionControl;

    do
    {
      std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

      std::cout << "  Email: ";
      std::getline( std::cin, credentials.userEmail );

      std::cout << "  Password: ";
      std::getline( std::cin, credentials.passPhrase );

      unsigned menuSelection;
      do
      {
        for( unsigned i = 0; i != roleLegalValues.size(); ++i )   std::cout << std::setw( 2 ) << i << " - " << roleLegalValues[i] << '\n';
        std::cout << "  role (0-" << roleLegalValues.size()-1 << "): ";
        std::cin  >> menuSelection;
      } while( menuSelection >= roleLegalValues.size() );

      selectedRole = roleLegalValues[menuSelection];


      // 3) Validate user is authorized for this role, and if so create session
      sessionControl = Domain::Session::SessionHandler::createSession( credentials );
      if( sessionControl != nullptr )
      {
        _logger << "Login Successful for \"" + credentials.userEmail + "\" as role \"" + selectedRole + "\"";
        break;
      }

      std::cout << "** Login failed\n";
      _logger << "Login failure for \"" + credentials.userEmail + "\" as role \"" + selectedRole + "\"";

    } while( true );


    // 4) Fetch functionality options for this rolee
    do
    {
      auto        commands = sessionControl->getCommands();
      std::string selectedCommand;
      unsigned    menuSelection;

      do
      {
        for( unsigned i = 0; i != commands.size(); ++i ) std::cout << std::setw( 2 ) << i << " - " << commands[i] << '\n';
        std::cout << std::setw( 2 ) << commands.size() << " - " << "Log off\n"; //This will be set to commands.size()

        std::cout << "  action (0-" << commands.size() << "): ";
        std::cin >> menuSelection;
      } while( menuSelection > commands.size() );

      //if( menuSelection == commands.size() ) break; //If menuselection is the size of commands, break out of this and end
      if( menuSelection == commands.size() ) {sessionControl->logOff();
      break;};

      selectedCommand = commands[menuSelection];
      _logger << "Command selected \"" + selectedCommand + '"';


      /******************************************************************************************************************************
      **  5) The user interface will collect relevant information to execute the chosen command.  This section requires the UI to
      **     know what information to collect, and hence what the available commands are.  Our goal is loose (minimal) coupling, not
      **     no coupling. This can be achieved in a variety of ways, but one common way is to pass strings instead of strong typed
      **     parameters.
      ******************************************************************************************************************************/
      if( selectedCommand == "Search Flight" ) //Searching the flight
      {
        std::vector<std::string> parameters( 4 );

        std::cout << " Enter origin:  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << " Enter destination:  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        std::cout << " Enter departure date (mm/dd/yyyy):  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
        std::cout << " Enter return date (mm/dd/yyyy):  ";  std::cin >> std::ws;  std::getline( std::cin, parameters[3] );

        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }

      else if( selectedCommand == "Book Flight" ) { //Booking the flight
        std::vector<std::string> parameters( 5 );
        std::cout << "Enter flight number: "; std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << "How many seats?: "; std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        std::cout << "Food Menu:\n" << "Vegetarian | Kids\n";
        //std::cout << "Food Menu:\n" + displayMeal("Vegetarian Meal") << '\n' << displayMeal("Kids Meal") << '\n';// << displayMeal("No Meal") << '\n';
        std::cout << "What kind of meal?: "; std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
        std::cout << "How many bags?: "; std::cin >> std::ws;  std::getline( std::cin, parameters[3] );
        //std::cout << "Ticket Class Types:\n" + displayClass("First Class") << '\n' << displayClass("Business Class") << '\n';// << displayClass("Economy Class") << '\n';
        std::cout << "Ticket Class Types:\n" << "First Class | Business Class\n"; //problems with this here
        std::cout << "What class type flight?: "; std::cin >> std::ws;  std::getline(std::cin, parameters[4]);

        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }

      else if (selectedCommand == "Show Ticket") { //Showing the booked tickets
        std::vector<std::string> parameters(1);
        std::cout << "Enter flight number: "; std::cin >> std::ws;  std::getline(std::cin, parameters[0]);

        auto results = sessionControl->executeCommand(selectedCommand, parameters);
        if (results.has_value()) _logger << "Received reply: \"" + std::any_cast<const std::string&>(results) + '"';
      }

      else if( selectedCommand == "Pay with Credit Card" ) { //Booking the flight
        std::vector<std::string> parameters( 6 );
        std::cout << "Enter flight number: "; std::cin >> std::ws;  std::getline( std::cin, parameters[0] );
        std::cout << "Enter card number: "; std::cin >> std::ws;  std::getline( std::cin, parameters[1] );
        std::cout << "Enter security pin: "; std::cin >> std::ws;  std::getline( std::cin, parameters[2] );
        std::cout << "Enter billing address: "; std::cin >> std::ws;  std::getline( std::cin, parameters[3] );
        std::cout << "Enter cost: "; std::cin >> std::ws;  std::getline( std::cin, parameters[4] );
        std::cout << "Enter payment card type: "; std::cin >> std::ws;  std::getline(std::cin, parameters[5]);

        auto results = sessionControl->executeCommand( selectedCommand, parameters );
        if( results.has_value() ) _logger << "Received reply: \"" + std::any_cast<const std::string &>( results ) + '"';
      }

      else sessionControl->executeCommand( selectedCommand, {} );
    } while( true );

    _logger << "Ending session and terminating";
  }
}
