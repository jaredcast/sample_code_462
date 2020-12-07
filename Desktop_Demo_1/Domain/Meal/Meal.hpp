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

        std::string _name = "";

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
        Vegetarian(const std::string& name = "Vegetarian")
            : Meal(this), _name(name)
        {}

        std::string getMeal() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return " [salad and ";
        }

        std::string drinkType() const override
        {
            return "water]";
        }

        virtual ~Vegetarian()
        {}

    private:
        std::string _name;
    };

    class Kids : public Meal
    {
    public:
        Kids(const std::string& name = "Kids")
            : Meal(this), _name(name)
        {}

        std::string getMeal() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return " [chicken nuggets and ";
        }

        std::string drinkType() const override
        {
            return "orange juice]";
        }

        virtual ~Kids()
        {}

    private:
        std::string _name;
    };

    /*class NoMeal : public Meal
    {
    public:
        Pescatarian(const std::string& name = "no meal")
            : Meal(this), _name(name)
        {}

        std::string getMeal() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return "";
        }

        std::string drinkType() const override
        {
            return "";
        }

        virtual ~NoMeal()
        {}

    private:
        std::string _name;
    };*/

    /*******************************************************************************
    **  Code to the Interface
    *******************************************************************************/
    // Passing by reference (vice value) is imperative!!  Pass by reference either by reference (&) or by pointer (*)
    std::string displayMeal(const std::string& meal)
    {
        Vegetarian v;
        Kids km;
        //Pescatarian p;
        if (meal == "Vegetarian")
        {
            return v.getMeal();
        }
        else if (meal == "Kids")
        {
            return km.getMeal();
        }
        else return "Error";
        //else if (meal == "Pescatarian")
        //{
        //    return p.getMeal();
        //}
    }
    /*std::any displayMeal(Domain::Session::SessionHandler& session, const std::vector<std::string>& args)
    {
        Vegetarian v;
        Kids km;
        //Pescatarian p;
        std::string results = "";
        const std::string mealType = args[0];
        if (mealType == "Vegetarian") {
            results = v.getMeal();
        }
        else if (mealType == "Kids Meal") {
            results = km.getMeal();
        }
        //else if (mealType == "Pescatarian") {
        //    results = p.getMeal();
        //}

        return results;
    }
    */
}