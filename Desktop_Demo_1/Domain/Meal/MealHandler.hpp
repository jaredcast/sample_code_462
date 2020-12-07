#pragma once

#include <any>
#include <memory>      // unique_ptr
#include <stdexcept>   // runtime_error
#include <string>
#include <vector>
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "Domain/Session/SessionHandler.hpp"
#include "Domain/Meal/Meal.hpp"


//interface
namespace Domain::Meal
{

    using TechnicalServices::Persistence::UserCredentials;

    class MealHandler
    {
    public:

        //All virtual functions, temporarily std::any. virtual function - 
        //virtual std::any displayMeal(Domain::Session::SessionHandler& session, const std::vector<std::string>& args) = 0;
        virtual std::string displayMeal(const std::string& meal) = 0;

        //Exceptions
        struct SessionException : std::runtime_error { using runtime_error::runtime_error; };
        struct   BadCommand : SessionException { using SessionException::SessionException; };

        // Destructor
        // Pure virtual destructor helps force the class to be abstract, but must still be implemented
        virtual ~MealHandler() noexcept = 0;

    protected:
        // Copy assignment operators, protected to prevent mix derived-type assignments
        MealHandler& operator=(const MealHandler& rhs) = default;  // copy assignment
        MealHandler& operator=(MealHandler&& rhs) = default;  // move assignment


    };    // class MealHandler

    /*****************************************************************************
    ** Inline implementations
    ******************************************************************************/
    //inline PaymentHandler::~PaymentHandler() noexcept = default;


} // namespace Domain::Library