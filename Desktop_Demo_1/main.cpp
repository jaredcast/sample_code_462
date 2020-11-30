#include <exception>    // exception
#include <iostream>
#include <locale>       // touuper(), locale()
#include <new>          // bad_alloc
#include <typeinfo>     // typeinfo.name()

#include "UI/UserInterfaceHandler.hpp"

//cd C:\Users\jared\Documents\GitHub\sample_code_462\Desktop_Demo_1
// /g++ -o main.exe main.cpp -I. UI/*.cpp Domain/Customer/*.cpp Domain/Session/*.cpp TechnicalServices/Logging/*.cpp TechnicalServices/Persistence/*.cpp -std=c++17

int main( /*int argc, char argv[] */ )
{
  try
  {
    std::cout << "\nThe Tuffy Flights system is initializing .!!!\n\n";

    // Smart pointer (for proper, exception safe memory management) to interface set to new instance of a configurable
    // implementation of the interface.
    auto userInterface = UI::UserInterfaceHandler::createUI();

    std::cout << "\nInitialization completed successfully\n";

    char response;
    do
    {
      std::cout << "Ready to transition into Operational State? (Q/Y/N) ";
      std::cin >> response;
      response = std::toupper( response, std::locale() );
    } while( response != 'Y' && response != 'Q' );

    if( response == 'Y' ) userInterface->launch();


    std::cout << "\nProgram complete, initiating shutdown\n";
  }



  catch( const std::bad_alloc & ex )
  {
    std::cerr << "Fatal:  Uncaught memory allocation exception\n\n"
              << ex.what() << '\n';
  }

  catch( const std::exception & ex )
  {
    std::cerr << "Fatal:  Uncaught standard exception\n"
              << typeid( ex ).name() << '\n'
              << ex.what() << '\n';
  }

  catch( ... )
  {
    std::cerr << "Fatal:  Uncaught (unknown type) exception\n";
  }
}
