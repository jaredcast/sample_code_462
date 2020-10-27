#pragma once

namespace Domain::Flights
{
  // Library Package within the Domain Layer Abstract class
  class MaintainFlightsHandler
  {
    public:
      // Operations
      //   Work in progress ...


      // Destructor
      // Pure virtual destructor helps force the class to be abstract, but must still be implemented
      virtual ~MaintainFlightsHandler() noexcept = 0;

    protected:
      // Copy assignment operators, protected to prevent mix derived-type assignments
      MaintainFlightsHandler& operator=( const MaintainFlightsHandler&  rhs ) = default;  // copy assignment
      MaintainFlightsHandler & operator=(       MaintainFlightsHandler && rhs ) = default;  // move assignment

  };    // class MaintainFlightsHandler





  /*****************************************************************************
  ** Inline implementations
  ******************************************************************************/
  inline MaintainFlightsHandler::~MaintainFlightsHandler() noexcept = default;


} // namespace Domain::Library
