#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "Domain/Session/SessionHandler.hpp"


//interface
namespace Domain::Meal
{

    using TechnicalServices::Persistence::UserCredentials;

    class MealHandler
    {
    public:

        //All virtual functions, temporarily std::any. virtual function - 
        virtual std::any displayMeal(Domain::Session::SessionHandler& session, const std::vector<std::string>& args) = 0;

        //Exceptions
        struct SessionException : std::runtime_error { using runtime_error::runtime_error; };
        struct   BadCommand : SessionException { using SessionException::SessionException; };

        // Object Factory returning a specialized object specific to the specified user and role
        static std::unique_ptr<MealHandler> createSession(const UserCredentials& credentials);

        //Operations
        virtual std::vector<std::string> getCommands() = 0; // retrieves the list of actions (commands)
        virtual std::any                 executeCommand(const std::string& command, const std::vector<std::string>& args) = 0; // Throws BadCommand


        // Destructor
        // Pure virtual destructor helps force the class to be abstract, but must still be implemented
        virtual ~MealHandler() noexcept = 0;

    protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
        MealHandler& operator=(const MealHandler& rhs) = default;  // copy assignment
        MealHandler& operator=(MealHandler&& rhs) = default;  // move assignment


    };    // class CustomerHandler





    /*****************************************************************************
    ** Inline implementations
    ******************************************************************************/
    //inline CustomerHandler::~CustomerHandler() noexcept = default;


} // namespace Domain::Library