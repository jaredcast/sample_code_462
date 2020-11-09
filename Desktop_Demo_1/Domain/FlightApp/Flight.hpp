#pragma once

#include "Domain/FlightApp/FlightHandler.hpp"
#include <string>

namespace Domain::FlightApp
{
  class Flight : public FlightHandler
  {
    public:
      // Constructors
      using FlightHandler::FlightHandler;  // inherit constructors

      // Operations

     ~Flight() noexcept override;


    //Class has not been properly included in the code - this is currently a placeholder 
    private:
      std::string origin;
      std::string destination;
      std::string dept;
      std::string ret;
      int stops;
      double price;
      std::string trip;
      std::string weather;
      std::string status;
      int flightNum;

  }; // class Flights
  


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Flight::~Flight() noexcept
  {}


}  // namespace Domain::Flight
