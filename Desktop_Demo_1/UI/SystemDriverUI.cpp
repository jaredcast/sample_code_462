#include "UI/SystemDriverUI.hpp"

#include "Domain/Session/SessionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"




namespace UI
{
  // Default constructor
  SystemDriverUI::SystemDriverUI()
  : _loggerPtr( TechnicalServices::Logging::LoggerHandler::create() )
  {
    _logger << "Contracted UI being used and has been successfully initialized";
  }




  // Destructor
  SystemDriverUI::~SystemDriverUI() noexcept
  {
    _logger << "Contracted UI shutdown successfully";
  }




  // Operations
  void SystemDriverUI::launch()
  {
    {
      _logger << "Starting scenario 1: Book flight";

      auto session  = Domain::Session::SessionHandler::createSession( {"jared@csuf.com", "password", {"Customer"}} );
      auto commands = session->getCommands();
      auto results  = session->executeCommand( "Search Flight", {"Los Angeles", "Paris", "12-01-2019", "12-16-2019"} );
      //session->singOff();

      _logger << "Completed scenario 1";
      system( "PAUSE" ); //pauses the automatic scenario
    }
  }
}    // namespace UI

