#pragma once
#include "Domain/Ticket/TicketHandler.hpp"
#include "Domain/Session/SessionBase.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include <iostream>
#include <string>
#include <set>
#include <any>
namespace
{
    /*******************************************************************************
    **  Abstract Class  (Generalization)
    *******************************************************************************/
    class Meal
    {
    public:
        virtual std::string getMeal() const = 0;
        virtual std::string foodType() const = 0;
        virtual std::string drinkType()       const = 0;

        static std::set<Meal*>& entirePopulation()
        {
            return meals;
        }

        virtual ~Meal() = 0;

    protected:
        // Enable derived classes to register themselves into a collection of people
        Meal(Meal* meal)
        {
            meals.insert(meal);
        }

        inline static std::set<Meal*> meals;
    };

    inline Meal::~Meal()
    {
        meals.erase(this);
    }


    /*******************************************************************************
    **  Concrete Class  (Specialization)
    *******************************************************************************/
    class Vegetarian : public Meal
    {
    public:
        Vegetarian(const std::string& name = "Vegetarian:")
            : Meal(this), _name(name)
        {}

        std::string getMeal() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return "\tSalad";
        }

        std::string drinkType() const override
        {
            return "\tWater";
        }

        virtual ~Vegetarian()
        {}

    private:
        std::string _name;
    };

    class Kids : public Meal
    {
    public:
        Kids(const std::string& name = "\n\nKids Meal:")
            : Meal(this), _name(name)
        {}

        std::string getMeal() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return "\tChicken Nuggets";
        }

        std::string drinkType() const override
        {
            return "\tOrange Juice";
        }

        virtual ~Kids()
        {}

    private:
        std::string _name;
    };

    /*class Pescatarian : public Meal
    {
    public:
        Pescatarian(const std::string& name = "Pescatarian:")
            : Meal(this), _name(name)
        {}

        std::string getMeal() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return "\tSalmon";
        }

        std::string drinkType() const override
        {
            return "\tWater";
        }

        virtual ~Pescatarian()
        {}

    private:
        std::string _name;
    };*/

    /*******************************************************************************
    **  Code to the Interface
    *******************************************************************************/
    // Passing by reference (vice value) is imperative!!  Pass by reference either by reference (&) or by pointer (*)
    std::any displayMeal(Domain::Session::SessionHandler& session, const std::vector<std::string>& args)
    {
        Vegetarian v;
        Kids km;
        //Pescatarian p;
        std::string results = "";
        const std::string classType = args[0];
        if (classType == "Vegetarian") {
            results = v.getMeal();
        }
        else if (classType == "Kids Meal") {
            results = km.getMeal();
        }
        //else if (classType == "Pescatarian") {
        //    results = p.getMeal();
        //}

        return results;
    }
}