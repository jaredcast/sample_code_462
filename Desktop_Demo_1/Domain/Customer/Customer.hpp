#pragma once
//possibly dont need
#include "Domain/Customer/CustomerHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include <string>
#include <vector>


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

        //std::vector<std::string> searchFlight(std::string origin, std::string dest, std::string startDate, std::string endDate) override; //return list of flights?
        //std::vector<std::string> bookFlight(int flightNum, int seats, int meals, int bags) override; //respond with flight number, and cost
        //std::vector<std::string> payCreditCard(int number, int pin, std::string name, std::string billingAdd, int cost) override; //flight info, receipt, ticket, email etc

        //std::any searchFlight(std::string origin, std::string dest, std::string startDate, std::string endDate) override; //return list of flights?
        //std::any bookFlight(int flightNum, int seats, int meals, int bags) override; //respond with flight number, and cost
        //std::any payCreditCard(int number, int pin, std::string name, std::string billingAdd, int cost) override; //flight info, receipt, ticket, email etc

        //std::any searchFlight(Domain::Session::SessionBase & session, const std::vector<std::string> & args) override; //return list of flights?
        std::any bookFlight(Domain::Session::SessionBase & session, const std::vector<std::string> & args) override; //respond with flight number, and cost
        std::any payCreditCard(Domain::Session::SessionBase & session, const std::vector<std::string> & args) override; //flight info, receipt, ticket, email etc
        std::any hello(Domain::Session::SessionBase & session, const std::vector<std::string> & args) override;
        std::any showTickets(Domain::Session::SessionBase& session, const std::vector <std::string > & args) override;
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
