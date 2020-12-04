#pragma once
#include <iostream>
#include <string>
#include <set>

namespace
{
    /*******************************************************************************
    **  Abstract Class  (Generalization)
    *******************************************************************************/
    class Meal
    {
    public:
        virtual std::string getDetails() const = 0;
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

        std::string getDetails() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return "\n\tSalad, ";
        }

        std::string drinkType() const override
        {
            return "Water, ";
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

        std::string getDetails() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return "\n\tChicken Nuggets, ";
        }

        std::string drinkType() const override
        {
            return "Orange Juice, ";
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

        std::string getDetails() const override
        {
            return _name + foodType() + drinkType();
        }

        std::string foodType() const override
        {
            return "\nFood: Salmon";
        }

        std::string drinkType() const override
        {
            return "\tDrink: nWater";
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
    std::string displayMeal(const Meal& meal)
    {
        return meal.getDetails();
    }
}