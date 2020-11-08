#pragma once

namespace Domain::FlightApp
{
  // Library Package within the Domain Layer Abstract class
  class FlightHandler
  {
    public:
      // Operations
      //   Work in progress ...
      

      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~FlightHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      FlightHandler& operator=( const FlightHandler&  rhs ) = default;  // copy assignment
      FlightHandler & operator=(       FlightHandler && rhs ) = default;  // move assignment

  };    // class MaintainFlightsHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline FlightHandler::~FlightHandler() noexcept = default;


} // namespace Domain::Library
