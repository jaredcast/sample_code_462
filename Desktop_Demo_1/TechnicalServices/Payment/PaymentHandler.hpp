#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "TechnicalServices/Payment/Payment.hpp"
#include "Domain/Session/SessionHandler.hpp"


//interface
namespace TechnicalServices::Payment
{

    using TechnicalServices::Persistence::UserCredentials;

    class PaymentHandler
    {
    public:

        //All virtual functions, temporarily std::any. virtual function - 
        //virtual std::any displayPaymentType(Domain::Session::SessionHandler& session, const std::vector<std::string>& args) = 0;

        //Exceptions
        struct SessionException : std::runtime_error { using runtime_error::runtime_error; };
        struct   BadCommand : SessionException { using SessionException::SessionException; };

        // Object Factory returning a specialized object specific to the specified user and role
        static std::unique_ptr<PaymentHandler> createPayment(const UserCredentials& credentials); //stubbed for now

        //Operations
        //virtual std::any                 executeCommand(const std::string& command, const std::vector<std::string>& args) = 0; // Throws BadCommand


        // Destructor
        // Pure virtual destructor helps force the class to be abstract, but must still be implemented
        virtual ~PaymentHandler() noexcept = 0;

    protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
        PaymentHandler& operator=(const PaymentHandler& rhs) = default;  // copy assignment
        PaymentHandler& operator=(PaymentHandler&& rhs) = default;  // move assignment


    };    // class Payment

    /*****************************************************************************
    ** Inline implementations
    ******************************************************************************/
    //inline Payment::~Payment() noexcept = default;


} // namespace Domain::Library