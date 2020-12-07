#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "Domain/Session/SessionHandler.hpp"
#include "Domain/Ticket/Ticket.hpp"


//interface
namespace Domain::Ticket
{

    using TechnicalServices::Persistence::UserCredentials;

    class TicketHandler
    {
    public:

        //All virtual functions, temporarily std::any. virtual function - 
        virtual std::string displayClass(const std::string& ticket) = 0;

        //Exceptions
        struct SessionException : std::runtime_error { using runtime_error::runtime_error; };
        struct   BadCommand : SessionException { using SessionException::SessionException; };

        //Operations

        // Destructor
        // Pure virtual destructor helps force the class to be abstract, but must still be implemented
        virtual ~TicketHandler() noexcept = 0;

    protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
        TicketHandler& operator=(const TicketHandler& rhs) = default;  // copy assignment
        TicketHandler& operator=(TicketHandler&& rhs) = default;  // move assignment


    };    // class TicketHandler

    /*****************************************************************************
    ** Inline implementations
    ******************************************************************************/
    //inline PaymentHandler::~PaymentHandler() noexcept = default;


} // namespace Domain::Library