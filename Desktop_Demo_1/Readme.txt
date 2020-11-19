Nathan Marcos	nathanmarcos@csu.fullerton.edu
Jared Castaneda jaredcast@csu.fullerton.edu
Jawad Swed		jawadswed@csu.fullerton.edu

Windows Build Instructions
1.	Open the Gitbash or Windows terminal inside the source folder. The source folder is where the three folders for the UI layer, Domain layer, and Technical Service layer are located. Make sure g++ is installed onto your computer. You can check by typing “g++ --version” into your terminal.
2.	Copy and paste this line into the terminal : “g++ -o main.exe main.cpp -I. UI/*.cpp Domain/Customer/*.cpp Domain/Session/*.cpp TechnicalServices/Logging/*.cpp TechnicalServices/Persistence/*.cpp -std=c++17”. Press enter.
3.	Type “./main” and press enter to run the code if using Gitbash, or type “main” if using the Windows terminal.

Linux Build Instructions
1.	Open the Bash console window inside the source folder. The source folder is where the three folders for the UI layer, Domain layer, and Technical Service layer are located. Make sure g++ is installed onto your computer. You can check by typing “g++ --version” into your terminal.
2.	Copy and paste this line into the terminal : “g++ main.cpp -o main -I. UI/*.cpp Domain/Customer/*.cpp Domain/Session/*.cpp TechnicalServices/Logging/*.cpp TechnicalServices/Persistence/*.cpp -std=c++17”
3.	Type ./main and press enter to run the code.
