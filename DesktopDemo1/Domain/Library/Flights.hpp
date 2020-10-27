#pragma once

#include "Domain/Library/MaintainFlightsHandler.hpp"

namespace Domain::Library
{
  class Flights : public Domain::Flights::MaintainFlightsHandler
  {
    public:
      // Constructors
      using MaintainFlightsHandler::MaintainFlightsHandler;  // inherit constructors

      // Operations

     ~Flights() noexcept override;
  }; // class Flights
  //testssad


  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline Flights::~Flights() noexcept
  {}


}  // namespace Domain::Library
