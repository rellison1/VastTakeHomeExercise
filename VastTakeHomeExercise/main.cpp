// Main/entry file for running the Operation program
// Integer input is taken twice. Once for number of stations for the Operation simulation
// and a second for the number of trucks used.
#include <iostream>
#include "Operation.h"

void ignoreUserInputLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntegerInput(const char* const prompt)
{
    // Loop until valid input is provided
    while(true)
    {
        std::cout << prompt;
        int input{0};
        std::cin >> input;
        // Check if extraction failed
        if (!std::cin)
        {
            // Exit if cin stream closed
            if(std::cin.eof())
                exit(0);

            // Reset/clear cin
            std::cin.clear();
            ignoreUserInputLine();

            std::cout << "Invalid input provided. Please try again." << std::endl;
        }
        else
        {
            // Received good input, remove extraneous data and return
            ignoreUserInputLine();
            return input;
        }
    }
}

int main(int argc, char** argv)
{
    // Take inputs and run simulation
    OperationConfig opConfig {getIntegerInput("Enter Number Of Stations: "),
                              getIntegerInput("Enter Number of Trucks: ")};
    Operation op{opConfig};
    op.RunSimulation();

    return 0;
}
