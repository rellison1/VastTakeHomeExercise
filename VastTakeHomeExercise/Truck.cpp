#include "Truck.h"
#include <iostream>
#include <random>

void Truck::update(minutes currentTimeOfSimulation)
{
    lastUpdate = currentTimeOfSimulation;
}

// Change the status/action of the truck
void Truck::setStatus(int currentTimeOfSimulation,TruckStatus status)
{ 
    currentStatus = status; 
    
    // When status is changed, update time of latest change
    update(currentTimeOfSimulation);
    
    // When a truck is set to mining, get new mining duration
    if(status == TruckStatus::mining)
        setCurrentMiningSessionDuration();

    // When a truck is set to moving, let observer/station know
    if(status == TruckStatus::moving)
        notifyObserver(currentTimeOfSimulation);

    // Status was changed so a new log entry can be recorded
    log.push_back(TruckLogEntry{status,currentTimeOfSimulation});
}

// Print current info of the truck
void Truck::print() const
{
    std::string statusInfo{};
    // Depending on state, add additional info
    switch(currentStatus)
    {
        case TruckStatus::mining:
            statusInfo += ": Mining session takes " + std::to_string(currentMiningSessionDuration);
            break;
        case TruckStatus::moving:
            statusInfo += ": Moving takes " + std::to_string(truckTransitionTime);
            break;
        case TruckStatus::unloading:
            statusInfo += ": Unloading takes " + std::to_string(truckUnloadTime);
            break;
    }
    std::cout << "Truck #" << getID() << " is " << getTruckStatusString(currentStatus) << statusInfo << std::endl;
}

// Print accumulated statistics of the truck at the current time
void Truck::printTotalStatistics()
{
    std::cout << "Truck #" << getID() << ":" << std::endl;
    for (auto& x : totalStatistics)
    {
        std::cout << "\t";
        std::cout << "Spent " << x.second << " minutes " << getTruckStatusString(x.first) << std::endl;
    }
}

void Truck::updateStatistics()
{
    totalStatistics.at(currentStatus)++;
}


bool Truck::shouldUpdateObserver()
{
    return isStatus(TruckStatus::moving);
}

void Truck::subjectUpdate(int currentTimeOfSimulation)
{
    if(currentStatus == TruckStatus::queuing)
        setStatus(currentTimeOfSimulation, TruckStatus::mining);
}

// Uses Mersenne Twister PRNG (best performance & quality of C++ built-in generators)
// to return a number between 60 and 300 which represents the range of 60 minutes to 300
// minutes which is equivalent to 1 to 5 hours. Used to acquire random variable mining time.
minutes Truck::generateRandomMiningDuration() const
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distr(60, 300);
    return distr(gen);
}

void Truck::setCurrentMiningSessionDuration() 
{ 
    currentMiningSessionDuration = generateRandomMiningDuration(); 
}
