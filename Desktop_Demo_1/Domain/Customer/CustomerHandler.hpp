#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::Customer
{

  using TechnicalServices::Persistence::UserCredentials;


  // Library Package within the Domain Layer Abstract class
  //Look up using sessionhandler, then run through customerhandler
  //Pass string to Session, Session wants to mapthat string to a function.
  //Function lives in customers component.
  class CustomerHandler
  {
    public:
      // Operations
      //   Work in progress ...
      //Customer will implement CustomerHandler. CustomerHandler is the interface
      //Add the virtual functions
      //virtual std::vector<std::string> searchFlight(std::string origin, std::string dest, std::string startDate, std::string endDate)  = 0;
      //virtual std::vector<std::string> bookFlight(int flightNum, int seats, int meals, int bags) = 0; //respond with flight number, and cost
      //virtual std::vector<std::string> payCreditCard(int number, int pin, std::string name, std::string billingAdd, int cost) = 0; //flight info, receipt, ticket, email etc
      
      virtual std::any searchFlight(std::string origin, std::string dest, std::string startDate, std::string endDate)  = 0;
      virtual std::any bookFlight(int flightNum, int seats, int meals, int bags) = 0; //respond with flight number, and cost
      virtual std::any payCreditCard(int number, int pin, std::string name, std::string billingAdd, int cost) = 0; //flight info, receipt, ticket, email etc
      
      
      //Exceptions
      struct SessionException : std::runtime_error {using runtime_error   ::runtime_error;   };
      struct   BadCommand     : SessionException   {using SessionException::SessionException;};

      // Object Factory returning a specialized object specific to the specified user and role
      static std::unique_ptr<CustomerHandler> createSession( const UserCredentials & credentials );

      //Operations
      virtual std::vector<std::string> getCommands   ()                                                                     = 0; // retrieves the list of actions (commands)
      virtual std::any                 executeCommand( const std::string & command, const std::vector<std::string> & args ) = 0; // Throws BadCommand

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~CustomerHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      CustomerHandler& operator=( const CustomerHandler&  rhs ) = default;  // copy assignment
      CustomerHandler & operator=(       CustomerHandler && rhs ) = default;  // move assignment


  };    // class CustomerHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  //inline CustomerHandler::~CustomerHandler() noexcept = default;


} // namespace Domain::Library
