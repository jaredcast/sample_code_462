#pragma once
//possibly dont need
#include "Domain/Customer/CustomerHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include <string>
#include <vector>

//class
namespace Domain::Customer 
{
  class Customer : public CustomerHandler //customer implements customershandler interface
  //Functions need to be real. Remove the =0
  {
    public:
        // Constructors
        //using CustomerHandler::CustomerHandler;  // inherit constructors
        Customer( const std::string & description,  const UserCredentials & credentials );

        std::vector<std::string> getCommands   ()                                                                     override;    // retrieves the list of actions (commands)
        std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) override;    // executes one of the actions retrieved
    
        // Operations
        //add to interface of CustomerHandler. still need here to implement interface
        //override - implement functions from base class

        std::any searchFlight(Domain::Session::SessionHandler & session, const std::vector<std::string> & args) override;
        std::any bookFlight(Domain::Session::SessionHandler & session, const std::vector<std::string> & args) override; //respond with flight number, and cost
        std::any payCreditCard(Domain::Session::SessionHandler & session, const std::vector<std::string> & args) override; //flight info, receipt, ticket, email etc
        std::any showTickets(Domain::Session::SessionHandler& session, const std::vector <std::string > & args) override;
        //std::any hello(Domain::Session::SessionHandler & session, const std::vector<std::string> & args) override;


        // Dispatched functions need access to these attributes, so for now make these public instead of protected
        // Types
        using DispatchTable = std::map<std::string, std::any (*)( Domain::Customer::Customer &, const std::vector<std::string> & )>;
        friend class Policy;

        // Instance Attributes
        std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
        TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;

        UserCredentials const                                      _credentials;
        std::string     const                                      _name      = "Undefined";
        DispatchTable                                              _commandDispatch;


     ~Customer() noexcept override;

     private:
        std::string email;
        std::string name;
        int creditCardNum;
        int creditCardPin;
        std::string billingAdd;
        
        
  }; // class Customer


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  //inline Customer::~Customer() noexcept
  //{}

  //struct CustomerSession      : Customer{ CustomerSession     ( const UserCredentials & credentials ); };

}  // namespace Domain::Library
