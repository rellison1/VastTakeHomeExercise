#pragma once
// This file contains the class and data for a Truck representation
#include "Component.h"
#include <unordered_map>
#include <vector>

// Lightweight struct to represent a truck's state and timestamp 
// that it was set for logging history
struct TruckLogEntry
{
    TruckStatus truckState{ TruckStatus::unset };
    minutes     timeStamp{ 0 };
};

class Truck : public Component
{
private:

    // Unique ID of each truck
    tag id{ 0 };

    // Truck's current status/action
    TruckStatus                currentStatus{ TruckStatus::unset };

    // Timestamp for latest change to Truck's status
    minutes                    lastUpdate{ 0 };

    // When a truck is mining, it will have a random duration for the mining session
    // The current duration is saved here
    minutes                    currentMiningSessionDuration{ 0 };
    
    // History log of this Truck's states and corresponding time stamps when updated
    std::vector<TruckLogEntry> log;

    // Collection of truck status to running count of total time in that state
    std::unordered_map<TruckStatus, int> totalStatistics{ {TruckStatus::mining,0},
                                                          {TruckStatus::unloading,0},
                                                          {TruckStatus::moving,0},
                                                          {TruckStatus::queuing,0} };
public:
    Truck()
    {
        // Uniquely identify each created truck
        static tag ID{ 0 };
        id = ID++;
    }
    virtual ~Truck()=default;

    // Return truck's current activity
    TruckStatus getCurrentStatus() const { return currentStatus; }

    // Get the total time that this mining session will take (different for each Minning session)
    minutes getCurrentMiningSessionDuration() const { return currentMiningSessionDuration; }

    // Latest time that the truck's activity changed.
    minutes getLastUpdatedTime() { return lastUpdate; }
    
    // Override of Component method which will update Truck based on the time of simulation
    virtual void update(minutes currentTimeOfSimulation);

    // Check/update the Truck's status
    bool isStatus(TruckStatus status) const { return currentStatus == status; }
    void setStatus(int currentTimeOfSimulation, TruckStatus status);
    
    // Print the Truck's current information
    virtual void print() const;

    // Print the Truck's accumulated statistics
    void printTotalStatistics();
    
    // Update accumulated statistics
    void updateStatistics();

    virtual bool shouldUpdateObserver();

    virtual void subjectUpdate(int currentTimeOfSimulation);

    // Get member variables for testing to be able to validate
    const std::vector<TruckLogEntry>& getLog() { return log; }
    const std::unordered_map<TruckStatus, int>& getTotalStatistics() { return totalStatistics; }

private:
    tag getID() const { return id; }
    // Returns a randomly generated value falling within the range of possible time amounts
    // it will take to mine
    minutes generateRandomMiningDuration() const;
    // Acquire duration for mining session
    void    setCurrentMiningSessionDuration();
};