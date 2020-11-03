#pragma once

#include "Domain/FlightApp/FlightHandler.hpp"

namespace Domain::FlightApp
{
  class Flight : public FlightHandler
  {
    public:
      // Constructors
      //using FlightHandler::FlightHandler;  // inherit constructors
      Flight() {}
      // Operations

     ~Flight() noexcept override;
  }; // class Flights
  //testssad


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Flight::~Flight() noexcept
  {}


}  // namespace Domain::Flight
