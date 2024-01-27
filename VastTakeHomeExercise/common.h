#pragma once
#include <string>

// Aliases
using minutes = int;
using tag     = int;

// Global Constants
extern const minutes truckUnloadTime;
extern const minutes truckTransitionTime;
extern const minutes simulationTotalRuntime;

// Enum
enum TruckStatus
{
    mining = 0,
    moving,
    unloading,
    queuing,
    unset
};

// Utility Functions
// Converts TruckStatus enum to string for printing
const char* const getTruckStatusString(TruckStatus status);
