#include "common.h"
#include <iostream>
#include <random>

extern const minutes truckUnloadTime{ 5 };
extern const minutes truckTransitionTime{ 30 };
extern const minutes simulationTotalRuntime{ 72 * 60 };

const char* const getTruckStatusString(TruckStatus status)
{
    if (status == TruckStatus::mining)
        return "Mining   ";
    else if (status == TruckStatus::moving)
        return "Moving   ";
    else if (status == TruckStatus::unloading)
        return "Unloading";
    else if (status == TruckStatus::queuing)
        return "Queuing  ";
    else
        return "Unset    ";
}
