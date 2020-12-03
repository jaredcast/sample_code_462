#pragma once

#include <any>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Session/SessionHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

/*
//SessionBase IS A SESSION HANDLER
//need a PAYMENT SERVICE INTERFACE inside TechnicalServices
//PaymentHandler , look similar to CustomerHandler
//Factory function to get instance of payment. Operation to makePayment  or startTransaction
//TechincalServices wont be able to understand domainlayer. cant know about domain
//Create interface in technicalservices, create what we need to support it, use interface inside domain
//Domain does not reach into technical services. All it can see is interfaces to technical services layer
//makePayment() - credit card or debit card - implementation detail
//Make a payment. dont care how its paid for
//Inside technicalservices - create stub to implement interface. Create a creditcardhandler
//DomainLayer knows about the payment handler interface
//creditcard to apple pay --- protected variations. instead of creating creditcard obj, create applepay obj.
//In domain layer, call createPayment factory function inside paymentHandler interface/ like UI layer calling createSession
*/
namespace Domain::Session
{
  class SessionBase : public SessionHandler //SessionBase IS A SESSION HANDLER
  {
    public:
      SessionBase( const std::string & description,  const UserCredentials & credentials );

      // Operations
      std::vector<std::string> getCommands   ()                                                                     override;    // retrieves the list of actions (commands)
      std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) override;    // executes one of the actions retrieved
      UserCredentials getCredentials() override;
      void logOff() override;


      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      ~SessionBase() noexcept override = 0;

  protected: 
  public:  // Dispatched functions need access to these attributes, so for now make these public instead of protected
    // Types
    using DispatchTable = std::map<std::string, std::any (*)( Domain::Session::SessionHandler &, const std::vector<std::string> & )>; 
    //Returns an any object that takes a vector of strings and then a reference to SessionHandler
    friend class Policy;

    // Instance Attributes
    std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr = TechnicalServices::Logging::LoggerHandler::create();
    TechnicalServices::Logging::LoggerHandler &                _logger    = *_loggerPtr;

    UserCredentials const                                      _credentials; 
    std::string     const                                      _name      = "Undefined";
    DispatchTable                                              _commandDispatch;
  };    // class SessionBase


  struct ITManagerSession : SessionBase{ ITManagerSession( const UserCredentials & credentials ); }; //remove?
  struct CustomerSession      : SessionBase{ CustomerSession     ( const UserCredentials & credentials ); }; //remove

} // namespace Domain::Session
